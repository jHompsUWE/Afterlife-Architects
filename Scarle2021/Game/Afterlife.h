#pragma once

//DirectX headers
#include "StepTimer.h"
#include "CommonStates.h"
#include "../DirectXTK/Inc/Effects.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Audio.h"


// Forward declarations
struct GameData;
struct DrawData;
struct DrawData2D;

//not sure
class GameObject;
class GameObject2D;
class Camera;
class TPSCamera;
class Light;
class Sound;

//Main Game Loop
class Afterlife
{
public:
    // Constructor / Deconstructor
    Afterlife() noexcept;
    ~Afterlife() = default;

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
    //void EventManager();
    //void FixedUpdate();
    void Update(DX::StepTimer const& timer);
    //void ScaledUpdate();
    //void LateUpdate();

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
    Camera* main_cam = NULL;
    TPSCamera* tps_cam = NULL; //Follow up camera
    Light* light = NULL;

    // required for the CMO model rendering system
    DirectX::CommonStates* common_states = NULL;
    DirectX::IEffectFactory* effect_factory = NULL;

    // basic keyboard and mouse input system
    void ReadInput(); //Get current Mouse and Keyboard states
    std::unique_ptr<DirectX::Keyboard> keyboard{};
    std::unique_ptr<DirectX::Mouse> mouse{};
    
    //sound stuff
    //This uses a simple system, but a better pipeline can be used using Wave Banks
    //See here: https://github.com/Microsoft/DirectXTK/wiki/Creating-and-playing-sound_list Using wave banks Section
    std::unique_ptr<DirectX::AudioEngine> audio_engine{};

    GameObject2D* text = nullptr;
};

