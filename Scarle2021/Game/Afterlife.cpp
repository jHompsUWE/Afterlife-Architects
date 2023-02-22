//
// AFTERLIFE ARCHITECTS 
//

#include "pch.h"
#include "Afterlife.h"
#include <time.h>

//Scarle headers
#include "GameData.h"
#include "GameState.h"
#include "DrawData.h"
#include "DrawData2D.h"
#include "ObjectList.h"

//Scarle pointers singleton
#include "DataManager.h"

extern void ExitGame() noexcept;
using namespace DirectX;
using Microsoft::WRL::ComPtr;

Afterlife::Afterlife() noexcept :
    main_window(nullptr),
    output_width(800),
    output_height(600),
    feature_level(D3D_FEATURE_LEVEL_11_0)
{
}

void Afterlife::Initialize(HWND _window, int _width, int _height)
{
    main_window = _window;
    output_width = std::max(_width, 1);
    output_height = std::max(_height, 1);
    
    //Aspect ratio
    float AR = (float)_width / (float)_height;

    //Sets up directX stuff
    CreateDevice();
    CreateResources();

    //TODO: Uncomment this for fixed 60FPS
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */
    
    // Seed random gen
    srand((UINT)time(NULL));

    // Set up keyboard and mouse system
    // Documentation here: https://github.com/microsoft/DirectXTK/wiki/Mouse-and-keyboard-input
    keyboard = std::make_unique<Keyboard>();
    mouse = std::make_unique<Mouse>();
    mouse->SetWindow(_window);
    
    //ABSOLUTE: px position of the screen
    //RELATIVE: Movement vector of the cursor
    mouse->SetMode(Mouse::MODE_ABSOLUTE);
    // Mouse Pointer visible?
    ShowCursor(true);
    
    // GameData
    game_data = new GameData;
    game_data->current_game_state = gs_main_menu;

    // 2D rendering data
    draw_data2D = new DrawData2D();
    draw_data2D->sprites_batch.reset(new SpriteBatch(d3d_context.Get()));
    // More fonts can be added by they have to be sprite-fonts 
    draw_data2D->main_font.reset(new SpriteFont(d3d_device.Get(), L"..\\Assets\\italic.spritefont"));
    common_states = new CommonStates(d3d_device.Get());

    // Set up DirectXTK Effects system
    effect_factory = new EffectFactory(d3d_device.Get());
    // Tell the effect_factory to look to the correct build directory to pull stuff in from
    ((EffectFactory*)effect_factory)->SetDirectory(L"..\\Assets");
    // Init render system for VBGOs
    VBGO::Init(d3d_device.Get());

    // Creates a starting light
    light = new Light(Vector3(0.0f, 100.0f, 160.0f), Color(1.0f, 1.0f, 1.0f, 1.0f),
        Color(0.4f, 0.1f, 0.1f, 1.0f));

    //Ortho camera
    //values passed are left, right, bottom, top, near clippin plane and far clipping plane respectively
    //ortho_cam = new OrthographicCamera(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);

    //this is needed for the follow cam
    debug_player = new Player("BirdModelV1", d3d_device.Get(), effect_factory);
    //Just a tps cam for plane debugging
    debug_cam = new TPSCamera(0.25f * XM_PI, AR, 1.0f, 10000.0f,
        debug_player, Vector3::UnitY, Vector3(0.0f, 10.0f, 50.0f));

    // Create DrawData struct and populate its pointers
    draw_data = new DrawData;
    draw_data->pd3d_immediate_context = nullptr;
    draw_data->common_states = common_states;
    //draw_data->main_camera = ortho_cam;
    draw_data->main_camera = debug_cam;
    draw_data->main_light = light;

    //Sets up the data manager, a singleton that makes all those pointers accessible everywhere
    DataManager::Get().PopulatePointers(AR, &main_window, game_data, draw_data, draw_data2D,
        d3d_device.Get(),d3d_context.Get(), effect_factory);

    //Inits the finite state machine
    finite_state_machine = std::make_unique<FSM>(game_data->current_game_state);
    finite_state_machine->init();
}

// Executes the basic game loop
void Afterlife::Tick()
{
    //Update cycle tied to a DirectX timer
    timer.Tick([&]()
    {
        MainUpdate(timer);
        ReadInput();
    });
    Render();
}

void Afterlife::MainUpdate(DX::StepTimer const& timer)
{
    const float delta_time = float(timer.GetElapsedSeconds());
    game_data->delta_time = delta_time;
   
    finite_state_machine->Update(game_data);
    
    //ortho_cam->Tick(game_data);
    light->Tick(game_data);

    //debug
    debug_player->Tick(game_data);
    debug_cam->Tick(game_data);
}

void Afterlife::ReadInput()
{
    //Updates states in GameData
    game_data->keyboard_state = keyboard->GetState();
    game_data->keyboard_state_tracker.Update(game_data->keyboard_state);
    game_data->mouse_state = mouse->GetState();
    
    //Clears the event list if it not empty
    EventManager::GetEventList().clear();
    //Reads the input and generates events accordingly
    EventManager::ReadInput(game_data);
    
    //Closes the game. Defined here so it is not dependant on the FSM
    if (game_data->keyboard_state.Escape)
    {
        ExitGame();
    }
    
    //TODO: UNCOMMENT THIS TO LOCK CURSOR TO THE CENTRE OF THE WINDOW
    /*
    RECT _window;
    GetWindowRect(main_window, &_window);
    SetCursorPos((_window.left + _window.right) >> 1, (_window.bottom + _window.top) >> 1);
    */
}

void Afterlife::Render()
{
    // Don't try to render anything before the first Update.
    if (timer.GetFrameCount() == 0)
    {
        return;
    }

    // Clear the main_window 
    Clear();

    //set immediate context of the graphics device, has to be done every single frame
    draw_data->pd3d_immediate_context = d3d_context.Get();

    //update the constant buffer for the rendering of VBGOs
    VBGO::UpdateConstantBuffer(draw_data);

    //Debug
    debug_player->Draw(draw_data);
    debug_cam->Draw(draw_data);
    
    //Renders basic scene elements
    //ortho_cam->Draw(draw_data);
    light->Draw(draw_data);
    
    //Draws 3D GOs
    finite_state_machine->Render3D(draw_data);
    
    //Begins sprite batching stuff
    draw_data2D->sprites_batch->Begin(SpriteSortMode_Deferred, common_states->NonPremultiplied());
    //Draws the 2D GOs
    finite_state_machine->Render2D(draw_data2D);
    //Stops sprite batching
    draw_data2D->sprites_batch->End();
    
    //drawing text screws up the Depth Stencil State, this puts it back again!
    d3d_context->OMSetDepthStencilState(common_states->DepthDefault(), 0);

    Present();
}

// Helper method to clear the back buffers.
void Afterlife::Clear()
{
    // Clear the views.
    d3d_context->ClearRenderTargetView(render_target_view.Get(), Colors::CornflowerBlue);
    d3d_context->ClearDepthStencilView(depth_stencil_view.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    d3d_context->OMSetRenderTargets(1, render_target_view.GetAddressOf(), depth_stencil_view.Get());

    // Set the viewport.
    CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(output_width), static_cast<float>(output_height));
    d3d_context->RSSetViewports(1, &viewport);
}

// Presents the back buffer contents to the screen.
void Afterlife::Present()
{
    // The first argument instructs DXGI to block until VSync, putting the application
    // to sleep until the next VSync. This ensures we don't waste any cycles rendering
    // frames that will never be displayed to the screen.
    HRESULT hr = swap_chain->Present(1, 0);

    // If the device was reset we must completely reinitialize the renderer.
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
    {
        OnDeviceLost();
    }
    else
    {
        DX::ThrowIfFailed(hr);
    }
}

// Message handlers
void Afterlife::OnActivated()
{
    // TODO: Game is becoming active main_window.
}

void Afterlife::OnDeactivated()
{
    // TODO: Game is becoming background main_window.
}

void Afterlife::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Afterlife::OnResuming()
{
    timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Afterlife::OnWindowSizeChanged(int _width, int _height)
{
    output_width = std::max(_width, 1);
    output_height = std::max(_height, 1);

    CreateResources();

    // TODO: Game main_window is being resized.
}

// Properties
void Afterlife::GetDefaultSize(int& _width, int& _height) const noexcept
{
    // TODO: Change to desired default main_window size (note minimum size is 320x200).
    _width = 1080;
    _height = 720;
}

// These are the resources that depend on the device.
void Afterlife::CreateDevice()
{
    UINT creationFlags = 0;

#ifdef _DEBUG
    //creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
    //something missing on the machines in 2Q28
    //this should work!
#endif

    static const D3D_FEATURE_LEVEL featureLevels [] =
    {
        // TODO: Modify for supported Direct3D feature levels
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1,
    };

    // Create the DX11 API device object, and get a corresponding context.
    ComPtr<ID3D11Device> device;
    ComPtr<ID3D11DeviceContext> context;
    DX::ThrowIfFailed(D3D11CreateDevice(
        nullptr,                            // specify nullptr to use the default adapter
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        creationFlags,
        featureLevels,
        static_cast<UINT>(std::size(featureLevels)),
        D3D11_SDK_VERSION,
        device.ReleaseAndGetAddressOf(),    // returns the Direct3D device created
        &feature_level,                     // returns feature level of device created
        context.ReleaseAndGetAddressOf()    // returns the device immediate context
        ));

#ifndef NDEBUG
    ComPtr<ID3D11Debug> d3dDebug;
    if (SUCCEEDED(device.As(&d3dDebug)))
    {
        ComPtr<ID3D11InfoQueue> d3dInfoQueue;
        if (SUCCEEDED(d3dDebug.As(&d3dInfoQueue)))
        {
#ifdef _DEBUG
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
#endif
            D3D11_MESSAGE_ID hide [] =
            {
                D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
                // TODO: Add more message IDs here as needed.
            };
            D3D11_INFO_QUEUE_FILTER filter = {};
            filter.DenyList.NumIDs = static_cast<UINT>(std::size(hide));
            filter.DenyList.pIDList = hide;
            d3dInfoQueue->AddStorageFilterEntries(&filter);
        }
    }
#endif

    DX::ThrowIfFailed(device.As(&d3d_device));
    DX::ThrowIfFailed(context.As(&d3d_context));

    // TODO: Initialize device dependent objects here (independent of main_window size).
}

// Allocate all memory resources that change on a main_window SizeChanged event.
void Afterlife::CreateResources()
{
    // Clear the previous main_window size specific context.
    ID3D11RenderTargetView* nullViews [] = { nullptr };
    d3d_context->OMSetRenderTargets(static_cast<UINT>(std::size(nullViews)), nullViews, nullptr);
    render_target_view.Reset();
    depth_stencil_view.Reset();
    d3d_context->Flush();

    const UINT backBufferWidth = static_cast<UINT>(output_width);
    const UINT backBufferHeight = static_cast<UINT>(output_height);
    const DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
    const DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
    constexpr UINT backBufferCount = 2;

    // If the swap chain already exists, resize it, otherwise create one.
    if (swap_chain)
    {
        HRESULT hr = swap_chain->ResizeBuffers(backBufferCount, backBufferWidth, backBufferHeight, backBufferFormat, 0);

        if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
        {
            // If the device was removed for any reason, a new device and swap chain will need to be created.
            OnDeviceLost();

            // Everything is set up now. Do not continue execution of this method. OnDeviceLost will reenter this method 
            // and correctly set up the new device.
            return;
        }
        else
        {
            DX::ThrowIfFailed(hr);
        }
    }
    else
    {
        // First, retrieve the underlying DXGI Device from the D3D Device.
        ComPtr<IDXGIDevice1> dxgiDevice;
        DX::ThrowIfFailed(d3d_device.As(&dxgiDevice));

        // Identify the physical adapter (GPU or card) this device is running on.
        ComPtr<IDXGIAdapter> dxgiAdapter;
        DX::ThrowIfFailed(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));

        // And obtain the factory object that created it.
        ComPtr<IDXGIFactory2> dxgiFactory;
        DX::ThrowIfFailed(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf())));

        // Create a descriptor for the swap chain.
        DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
        swapChainDesc.Width = backBufferWidth;
        swapChainDesc.Height = backBufferHeight;
        swapChainDesc.Format = backBufferFormat;
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferCount = backBufferCount;

        DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = {};
        fsSwapChainDesc.Windowed = TRUE;

        // Create a SwapChain from a Win32 main_window.
        DX::ThrowIfFailed(dxgiFactory->CreateSwapChainForHwnd(
            d3d_device.Get(),
            main_window,
            &swapChainDesc,
            &fsSwapChainDesc,
            nullptr,
            swap_chain.ReleaseAndGetAddressOf()
            ));

        // This template does not support exclusive fullscreen mode and prevents DXGI from responding to the ALT+ENTER shortcut.
        DX::ThrowIfFailed(dxgiFactory->MakeWindowAssociation(main_window, DXGI_MWA_NO_ALT_ENTER));
    }

    // Obtain the backbuffer for this main_window which will be the final 3D rendertarget.
    ComPtr<ID3D11Texture2D> backBuffer;
    DX::ThrowIfFailed(swap_chain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));

    // Create a view interface on the rendertarget to use on bind.
    DX::ThrowIfFailed(d3d_device->CreateRenderTargetView(backBuffer.Get(), nullptr, render_target_view.ReleaseAndGetAddressOf()));

    // Allocate a 2-D surface as the depth/stencil buffer and
    // create a DepthStencil view on this surface to use on bind.
    CD3D11_TEXTURE2D_DESC depthStencilDesc(depthBufferFormat, backBufferWidth, backBufferHeight, 1, 1, D3D11_BIND_DEPTH_STENCIL);

    ComPtr<ID3D11Texture2D> depthStencil;
    DX::ThrowIfFailed(d3d_device->CreateTexture2D(&depthStencilDesc, nullptr, depthStencil.GetAddressOf()));

    CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
    DX::ThrowIfFailed(d3d_device->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, depth_stencil_view.ReleaseAndGetAddressOf()));

    // TODO: Initialize windows-size dependent objects here.
}

void Afterlife::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.
    depth_stencil_view.Reset();
    render_target_view.Reset();
    swap_chain.Reset();
    d3d_context.Reset();
    d3d_device.Reset();

    CreateDevice();
    CreateResources();
}






