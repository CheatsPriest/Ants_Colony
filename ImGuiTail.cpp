#include "ImGuiTail.h"
#include "myfont.h"
Window::Window(InfoSpace* data_p) {
    data = data_p;

    field = data->field;
    
    
    wide = data->main_window_wide;
    hight = data->main_window_hight;
    isValid = true;
    
    Create();
}
ImGuiIO& Window::Create() {
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"ImGui Example", nullptr };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"Ants colony", WS_OVERLAPPEDWINDOW, 100, 100, wide, hight, nullptr, nullptr, wc.hInstance, nullptr);
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        data->mainLoop = false;
        isValid = false;
        
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.Fonts->AddFontFromMemoryCompressedTTF(MyFont_compressed_data, MyFont_compressed_size, text_size, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    // io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Аrial.ttf", 15, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
     //io.Fonts->AddFontFromMemoryCompressedTTF(MyFont_compressed_data, MyFont_compressed_size, 15, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);
    return io;
}

void Window::NewFrame() {
    MSG msg;
    while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
    {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
        if (msg.message == WM_QUIT) {
            data->mainLoop = false;
            isValid = false;
        }

    }


    // Handle lost D3D9 device
    if (g_DeviceLost)
    {
        HRESULT hr = g_pd3dDevice->TestCooperativeLevel();
        if (hr == D3DERR_DEVICELOST)
        {
            ::Sleep(10);

        }
        if (hr == D3DERR_DEVICENOTRESET)
            ResetDevice();
        g_DeviceLost = false;
    }

    // Handle window resize (we don't resize directly in the WM_SIZE handler)
    if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
    {
        g_d3dpp.BackBufferWidth = g_ResizeWidth;
        g_d3dpp.BackBufferHeight = g_ResizeHeight;
        g_ResizeWidth = g_ResizeHeight = 0;
        ResetDevice();
    }

    // Start the Dear ImGui frame
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();



    DrawMainScene();
}

void Window::EndFrame() {
    ImGui::EndFrame();
    g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
    g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
    //D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x * clear_color.w * 255.0f), (int)(clear_color.y * clear_color.w * 255.0f), (int)(clear_color.z * clear_color.w * 255.0f), (int)(clear_color.w * 255.0f));
    g_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x0000000, 1.0f, 0);
    if (g_pd3dDevice->BeginScene() >= 0)
    {
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
        g_pd3dDevice->EndScene();
    }
    HRESULT result = g_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr);
    if (result == D3DERR_DEVICELOST) {
        g_DeviceLost = true;
    }
    if (!isValid) {
        data->mainLoop = false;
        
        //delete this;
        //exit(0);
        //Твой код выхода
    }
}
void Window::Cleanup() {
    // Cleanup
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
}
