#pragma once

//DirectX headers
#include "StepTimer.h"
#include "CommonStates.h"
#include "../DirectXTK/Inc/Effects.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "GamePad.h"
#include "Audio.h"
#include "FSM.h"
#include "OrthographicCamera.h"

//Player for debug purposes
#include "EventManager.h"
#include "Player.h"

// Forward declarations
struct GameData;
struct DrawData;
struct DrawData2D;


//Main Game Loop
class Afterlife
{
public:
    // Constructor / Deconstructor
    Afterlife() noexcept;
    ~Afterlife();

    Afterlife(Afterlife&&) = default;
    Afterlife& operator= (Afterlife&&) = default;

    Afterlife(Afterlife const&) = delete;
    Afterlife& operator= (Afterlife const&) = delete;

    // Initialize
    void Initialize(HWND _window, int _width, int _height);

    // Tick update
    void Tick();

    // Window management
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);
    void GetDefaultSize( int& width, int& height ) const noexcept;

private:
    
    // Game Loop
    void MainUpdate(DX::StepTimer const& timer);
    void Render();
    
    // Device Manager
    void Clear();
    void Present();
    void CreateDevice();
    void CreateResources();
    void OnDeviceLost();

    // Device Resources
    HWND    main_window;
    int     output_width;
    int     output_height;

    D3D_FEATURE_LEVEL                               feature_level;
    Microsoft::WRL::ComPtr<ID3D11Device1>           d3d_device;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    d3d_context;

    Microsoft::WRL::ComPtr<IDXGISwapChain1>         swap_chain;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  render_target_view;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  depth_stencil_view;

    // Rendering Loop Timer
    DX::StepTimer timer{};

    // Scarle Data Containers
    GameData* game_data = NULL;
    DrawData* draw_data = NULL;
    DrawData2D* draw_data2D = NULL;

    // 3D renders
    OrthographicCamera* ortho_cam = NULL;
    Light* light = NULL;

    // Debug
    //TPSCamera* debug_cam = NULL;

    // required for the CMO model rendering system
    CommonStates* common_states = NULL;
    IEffectFactory* effect_factory = NULL;

    // basic keyboard and mouse input system
    void ReadInput(); //Get current Mouse and Keyboard states
    std::unique_ptr<Keyboard> keyboard{};
    std::unique_ptr<Mouse> mouse{};
    std::unique_ptr<GamePad> gamepad{};
    int gamepad_index = 0;

    //Instance of the FSM
    std::unique_ptr<FSM> finite_state_machine = nullptr;
    std::unique_ptr<AudioManager> audio_manager = nullptr;

    //Pointer to the Event Manager
    AL::EventManager* event_manager = nullptr;
};

