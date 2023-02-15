//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include <time.h>

//Scarle Headers
#include "GameData.h"
#include "GameState.h"
#include "DrawData.h"
#include "DrawData2D.h"
#include "ObjectList.h"

extern void ExitGame() noexcept;

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Game::Game() noexcept :
    m_window(nullptr),
    m_outputWidth(800),
    m_outputHeight(600),
    m_featureLevel(D3D_FEATURE_LEVEL_11_0)
{
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND _window, int _width, int _height)
{
    m_window = _window;
    m_outputWidth = std::max(_width, 1);
    m_outputHeight = std::max(_height, 1);

    CreateDevice();

    CreateResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */

    //seed the random number generator
    srand((UINT)time(NULL));

    //set up keyboard and mouse system
    //documentation here: https://github.com/microsoft/DirectXTK/wiki/Mouse-and-keyboard-input
    m_keyboard = std::make_unique<Keyboard>();
    m_mouse = std::make_unique<Mouse>();
    m_mouse->SetWindow(_window);
    m_mouse->SetMode(Mouse::MODE_RELATIVE);
    //Hide the mouse pointer
    ShowCursor(false);

    //create GameData struct and populate its pointers
    m_GD = new GameData;
    m_GD->m_GS = GS_PLAY_MAIN_CAM;

    //set up systems for 2D rendering
    m_DD2D = new DrawData2D();
    m_DD2D->m_Sprites.reset(new SpriteBatch(m_d3dContext.Get()));
    m_DD2D->m_Font.reset(new SpriteFont(m_d3dDevice.Get(), L"..\\Assets\\italic.spritefont"));
    m_states = new CommonStates(m_d3dDevice.Get());

    //set up DirectXTK Effects system
    m_fxFactory = new EffectFactory(m_d3dDevice.Get());
    //Tell the fxFactory to look to the correct build directory to pull stuff in from
    ((EffectFactory*)m_fxFactory)->SetDirectory(L"..\\Assets");
    //init render system for VBGOs
    VBGO::Init(m_d3dDevice.Get());

    //set audio system
    AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG
    eflags = eflags | AudioEngine_Debug;
#endif
    m_audioEngine = std::make_unique<AudioEngine>(eflags);

    //create a set of dummy things to show off the engine

    //create a base light
    m_light = new Light(Vector3(0.0f, 100.0f, 160.0f), Color(1.0f, 1.0f, 1.0f, 1.0f), Color(0.4f, 0.1f, 0.1f, 1.0f));
    m_GameObjects.push_back(m_light);

    //find how big my window is to correctly calculate my aspect ratio
    float AR = (float)_width / (float)_height;

    //example basic 3D stuff
    Terrain* terrain = new Terrain("table", m_d3dDevice.Get(), m_fxFactory, Vector3(100.0f, 0.0f, 100.0f), 0.0f, 0.0f, 0.0f, 0.25f * Vector3::One);
    m_GameObjects.push_back(terrain);

    //L-system like tree
    m_GameObjects.push_back(new Tree(4, 4, .6f, 10.0f * Vector3::Up, XM_PI / 6.0f, "JEMINA vase -up", m_d3dDevice.Get(), m_fxFactory));

    //Vertex Buffer Game Objects
    FileVBGO* terrainBox = new FileVBGO("terrainTex", m_d3dDevice.Get());
    m_GameObjects.push_back(terrainBox);

    FileVBGO* Box = new FileVBGO("cube", m_d3dDevice.Get());
    m_GameObjects.push_back(Box);
    Box->SetPos(Vector3(0.0f, 0.0f, -100.0f));
    Box->SetPitch(XM_PIDIV4);
    Box->SetScale(20.0f);

    VBCube* cube = new VBCube();
    cube->init(11, m_d3dDevice.Get());
    cube->SetPos(Vector3(100.0f, 0.0f, 0.0f));
    cube->SetScale(4.0f);
    m_GameObjects.push_back(cube);

    VBSpike* spikes = new VBSpike();
    spikes->init(11, m_d3dDevice.Get());
    spikes->SetPos(Vector3(0.0f, 0.0f, 100.0f));
    spikes->SetScale(4.0f);
    m_GameObjects.push_back(spikes);

    VBSpiral* spiral = new VBSpiral();
    spiral->init(11, m_d3dDevice.Get());
    spiral->SetPos(Vector3(-100.0f, 0.0f, 0.0f));
    spiral->SetScale(4.0f);
    m_GameObjects.push_back(spiral);

    VBPillow* pillow = new VBPillow();
    pillow->init(11, m_d3dDevice.Get());
    pillow->SetPos(Vector3(-100.0f, 0.0f, -100.0f));
    pillow->SetScale(4.0f);
    m_GameObjects.push_back(pillow);

    VBSnail* snail = new VBSnail(m_d3dDevice.Get(), "shell", 150, 0.98f, 0.09f * XM_PI, 0.4f, Color(1.0f, 0.0f, 0.0f, 1.0f), Color(0.0f, 0.0f, 1.0f, 1.0f));
    snail->SetPos(Vector3(-100.0f, 0.0f, 100.0f));
    snail->SetScale(2.0f);
    m_GameObjects.push_back(snail);

    //Marching Cubes
    VBMarchCubes* VBMC = new VBMarchCubes();
    VBMC->init(Vector3(-8.0f, -8.0f, -17.0f), Vector3(8.0f, 8.0f, 23.0f), 60.0f * Vector3::One, 0.01, m_d3dDevice.Get());
    VBMC->SetPos(Vector3(100, 0, -100));
    VBMC->SetPitch(-XM_PIDIV2);
    VBMC->SetScale(Vector3(3, 3, 1.5));
    m_GameObjects.push_back(VBMC);

    //create a base camera
    m_cam = new Camera(0.25f * XM_PI, AR, 1.0f, 10000.0f, Vector3::UnitY, Vector3::Zero);
    m_cam->SetPos(Vector3(0.0f, 200.0f, 200.0f));
    m_GameObjects.push_back(m_cam);

    //add Player
    Player* pPlayer = new Player("BirdModelV1", m_d3dDevice.Get(), m_fxFactory);
    m_GameObjects.push_back(pPlayer);

    //add a secondary camera
    m_TPScam = new TPSCamera(0.25f * XM_PI, AR, 1.0f, 10000.0f, pPlayer, Vector3::UnitY, Vector3(0.0f, 10.0f, 50.0f));
    m_GameObjects.push_back(m_TPScam);

    //test all GPGOs
    float* params = new float[3];
    params[0] = 10.f;  params[1] = 20.0f; params[2] = 30.f;
    GPGO* pGPGO = new GPGO(m_d3dContext.Get(), GPGO_BOX, (float*)&Colors::Azure, params);
    pGPGO->SetPos(Vector3(-50.0f, 10.0f, -100.f));
    m_GameObjects.push_back(pGPGO);
    params[0] = params[1] = 20.0f; params[2] = (size_t)32;
    pGPGO = new GPGO(m_d3dContext.Get(), GPGO_CONE, (float*)&Colors::Navy,params);
    pGPGO->SetPos(Vector3(-50.0f, 10.0f, -70.f));
    m_GameObjects.push_back(pGPGO);
    params[0] = 15.0f;
    pGPGO = new GPGO(m_d3dContext.Get(), GPGO_CUBE, (float*)&Colors::SeaGreen, params);
    pGPGO->SetPos(Vector3(-50.0f, 10.0f, -40.f));
    m_GameObjects.push_back(pGPGO);
    params[0] = params[1] = 20.0f; params[2] = (size_t)32;
    pGPGO = new GPGO(m_d3dContext.Get(), GPGO_CYLINDER, (float*)&Colors::OliveDrab, params);
    pGPGO->SetPos(Vector3(-50.0f, 10.0f, -10.f));
    m_GameObjects.push_back(pGPGO);
    params[0] = 15.0f;
    pGPGO = new GPGO(m_d3dContext.Get(), GPGO_DODECAHEDRON, (float*)&Colors::OrangeRed,params);
    pGPGO->SetPos(Vector3(-50.0f, 10.0f, 20.f));
    m_GameObjects.push_back(pGPGO);
    params[0] =  15.0f; params[1] = (size_t)3;
    pGPGO = new GPGO(m_d3dContext.Get(), GPGO_GEOSPHERE, (float*)&Colors::BlueViolet, params);
    pGPGO->SetPos(Vector3(-50.0f, 10.0f, 50.f));
    m_GameObjects.push_back(pGPGO);
    params[0] = 20;
    pGPGO = new GPGO(m_d3dContext.Get(), GPGO_ICOSAHEDRON, (float*)&Colors::DodgerBlue, params);
    pGPGO->SetPos(Vector3(-50.0f, 10.0f, 80.f));
    m_GameObjects.push_back(pGPGO);
    params[0] = 20;
    pGPGO = new GPGO(m_d3dContext.Get(), GPGO_OCTAHEDRON, (float*)&Colors::PaleTurquoise, params);
    pGPGO->SetPos(Vector3(-50.0f, 10.0f, 110.f));
    m_GameObjects.push_back(pGPGO);
    params[0] = 15.0f; params[1] = (size_t)16;
    pGPGO = new GPGO(m_d3dContext.Get(), GPGO_SPHERE, (float*)&Colors::LawnGreen, params);
    pGPGO->SetPos(Vector3(-50.0f, 10.0f, 140.0));
    m_GameObjects.push_back(pGPGO);
    params[0] = 15.0f; params[1] = (size_t)8;
    pGPGO = new GPGO(m_d3dContext.Get(), GPGO_TEAPOT, (float*)&Colors::YellowGreen, params);
    pGPGO->SetPos(Vector3(-50.0f, 10.0f, 170.0f));
    m_GameObjects.push_back(pGPGO);
    params[0] = 20;
    pGPGO = new GPGO(m_d3dContext.Get(), GPGO_TETRAHEDRON, (float*)&Colors::Firebrick, params);
    pGPGO->SetPos(Vector3(-50.0f, 10.0f, 200.f));
    m_GameObjects.push_back(pGPGO);
    params[0] = 30.0f; params[1] = 10.0f; params[2] = (size_t)32;
    pGPGO = new GPGO(m_d3dContext.Get(), GPGO_TORUS, (float*)&Colors::Aquamarine, params);
    pGPGO->SetPos(Vector3(-50.0f, 10.0f, 230.f));
    m_GameObjects.push_back(pGPGO);

    //create DrawData struct and populate its pointers
    m_DD = new DrawData;
    m_DD->m_pd3dImmediateContext = nullptr;
    m_DD->m_states = m_states;
    m_DD->m_cam = m_cam;
    m_DD->m_light = m_light;

    //example basic 2D stuff
    ImageGO2D* logo = new ImageGO2D("logo_small", m_d3dDevice.Get());
    logo->SetPos(200.0f * Vector2::One);
    m_GameObjects2D.push_back(logo);
    ImageGO2D* bug_test = new ImageGO2D("bug_test", m_d3dDevice.Get());
    bug_test->SetPos(300.0f * Vector2::One);
    m_GameObjects2D.push_back(bug_test);

    TextGO2D* text = new TextGO2D("Test Text");
    text->SetPos(Vector2(100, 10));
    text->SetColour(Color((float*)&Colors::Yellow));
    m_GameObjects2D.push_back(text);

    //Test Sounds
    Loop* loop = new Loop(m_audioEngine.get(), "NightAmbienceSimple_02");
    loop->SetVolume(0.1f);
    loop->Play();
    m_Sounds.push_back(loop);

    TestSound* TS = new TestSound(m_audioEngine.get(), "Explo1");
    m_Sounds.push_back(TS);
}

// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& _timer)
{
    float elapsedTime = float(_timer.GetElapsedSeconds());
    m_GD->m_dt = elapsedTime;

    //this will update the audio engine but give us chance to do somehting else if that isn't working
    if (!m_audioEngine->Update())
    {
        if (m_audioEngine->IsCriticalError())
        {
            // We lost the audio device!
        }
    }
    else
    {
        //update sounds playing
        for (list<Sound*>::iterator it = m_Sounds.begin(); it != m_Sounds.end(); it++)
        {
            (*it)->Tick(m_GD);
        }
    }

    ReadInput();
    //upon space bar switch camera state
    //see docs here for what's going on: https://github.com/Microsoft/DirectXTK/wiki/Keyboard
    if (m_GD->m_KBS_tracker.pressed.Space)
    {
        if (m_GD->m_GS == GS_PLAY_MAIN_CAM)
        {
            m_GD->m_GS = GS_PLAY_TPS_CAM;
        }
        else
        {
            m_GD->m_GS = GS_PLAY_MAIN_CAM;
        }
    }

    //update all objects
    for (list<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
    {
        (*it)->Tick(m_GD);
    }
    for (list<GameObject2D*>::iterator it = m_GameObjects2D.begin(); it != m_GameObjects2D.end(); it++)
    {
        (*it)->Tick(m_GD);
    }
}

// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();
    
    //set immediate context of the graphics device
    m_DD->m_pd3dImmediateContext = m_d3dContext.Get();

    //set which camera to be used
    m_DD->m_cam = m_cam;
    if (m_GD->m_GS == GS_PLAY_TPS_CAM)
    {
        m_DD->m_cam = m_TPScam;
    }

    //update the constant buffer for the rendering of VBGOs
    VBGO::UpdateConstantBuffer(m_DD);

    //Draw 3D Game Obejects
    for (list<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
    {
        (*it)->Draw(m_DD);
    }

    // Draw sprite batch stuff 
    m_DD2D->m_Sprites->Begin(SpriteSortMode_Deferred, m_states->NonPremultiplied());
    for (list<GameObject2D*>::iterator it = m_GameObjects2D.begin(); it != m_GameObjects2D.end(); it++)
    {
        (*it)->Draw(m_DD2D);
    }
    m_DD2D->m_Sprites->End();

    //drawing text screws up the Depth Stencil State, this puts it back again!
    m_d3dContext->OMSetDepthStencilState(m_states->DepthDefault(), 0);

    Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    // Clear the views.
    m_d3dContext->ClearRenderTargetView(m_renderTargetView.Get(), Colors::CornflowerBlue);
    m_d3dContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    m_d3dContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());

    // Set the viewport.
    CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(m_outputWidth), static_cast<float>(m_outputHeight));
    m_d3dContext->RSSetViewports(1, &viewport);
}

// Presents the back buffer contents to the screen.
void Game::Present()
{
    // The first argument instructs DXGI to block until VSync, putting the application
    // to sleep until the next VSync. This ensures we don't waste any cycles rendering
    // frames that will never be displayed to the screen.
    HRESULT hr = m_swapChain->Present(1, 0);

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
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowSizeChanged(int _width, int _height)
{
    m_outputWidth = std::max(_width, 1);
    m_outputHeight = std::max(_height, 1);

    CreateResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& _width, int& _height) const noexcept
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    _width = 800;
    _height = 600;
}

// These are the resources that depend on the device.
void Game::CreateDevice()
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
        &m_featureLevel,                    // returns feature level of device created
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

    DX::ThrowIfFailed(device.As(&m_d3dDevice));
    DX::ThrowIfFailed(context.As(&m_d3dContext));

    // TODO: Initialize device dependent objects here (independent of window size).
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateResources()
{
    // Clear the previous window size specific context.
    ID3D11RenderTargetView* nullViews [] = { nullptr };
    m_d3dContext->OMSetRenderTargets(static_cast<UINT>(std::size(nullViews)), nullViews, nullptr);
    m_renderTargetView.Reset();
    m_depthStencilView.Reset();
    m_d3dContext->Flush();

    const UINT backBufferWidth = static_cast<UINT>(m_outputWidth);
    const UINT backBufferHeight = static_cast<UINT>(m_outputHeight);
    const DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
    const DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
    constexpr UINT backBufferCount = 2;

    // If the swap chain already exists, resize it, otherwise create one.
    if (m_swapChain)
    {
        HRESULT hr = m_swapChain->ResizeBuffers(backBufferCount, backBufferWidth, backBufferHeight, backBufferFormat, 0);

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
        DX::ThrowIfFailed(m_d3dDevice.As(&dxgiDevice));

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

        // Create a SwapChain from a Win32 window.
        DX::ThrowIfFailed(dxgiFactory->CreateSwapChainForHwnd(
            m_d3dDevice.Get(),
            m_window,
            &swapChainDesc,
            &fsSwapChainDesc,
            nullptr,
            m_swapChain.ReleaseAndGetAddressOf()
            ));

        // This template does not support exclusive fullscreen mode and prevents DXGI from responding to the ALT+ENTER shortcut.
        DX::ThrowIfFailed(dxgiFactory->MakeWindowAssociation(m_window, DXGI_MWA_NO_ALT_ENTER));
    }

    // Obtain the backbuffer for this window which will be the final 3D rendertarget.
    ComPtr<ID3D11Texture2D> backBuffer;
    DX::ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));

    // Create a view interface on the rendertarget to use on bind.
    DX::ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.ReleaseAndGetAddressOf()));

    // Allocate a 2-D surface as the depth/stencil buffer and
    // create a DepthStencil view on this surface to use on bind.
    CD3D11_TEXTURE2D_DESC depthStencilDesc(depthBufferFormat, backBufferWidth, backBufferHeight, 1, 1, D3D11_BIND_DEPTH_STENCIL);

    ComPtr<ID3D11Texture2D> depthStencil;
    DX::ThrowIfFailed(m_d3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, depthStencil.GetAddressOf()));

    CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
    DX::ThrowIfFailed(m_d3dDevice->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, m_depthStencilView.ReleaseAndGetAddressOf()));

    // TODO: Initialize windows-size dependent objects here.
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.

    m_depthStencilView.Reset();
    m_renderTargetView.Reset();
    m_swapChain.Reset();
    m_d3dContext.Reset();
    m_d3dDevice.Reset();

    CreateDevice();

    CreateResources();
}

void Game::ReadInput()
{
    m_GD->m_KBS = m_keyboard->GetState();
    m_GD->m_KBS_tracker.Update(m_GD->m_KBS);
    //quit game on hiting escape
    if (m_GD->m_KBS.Escape)
    {
        ExitGame();
    }

    m_GD->m_MS = m_mouse->GetState();

    //lock the cursor to the centre of the window
    RECT window;
    GetWindowRect(m_window, &window);
    SetCursorPos((window.left + window.right) >> 1, (window.bottom + window.top) >> 1);
}
