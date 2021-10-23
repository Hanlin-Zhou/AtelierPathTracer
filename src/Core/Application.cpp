#include <Core/Application.hpp>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    APT::Application* app = nullptr;
    if (message == WM_CREATE)
    {
        CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        app = reinterpret_cast<APT::Application*>(pCreate->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)app);
    }
    else
    {
        LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
        app = reinterpret_cast<APT::Application*>(ptr);
    }
    if (ImGui_ImplWin32_WndProcHandler(hwnd, message, wParam, lParam))
        return 0;
    if (app != nullptr && app->IsInitialized()) {
        if (app->HandleMessage(hwnd, message, wParam, lParam))
            return 0;
    }
    
    switch (message) {
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hwnd, message, wParam, lParam);
}

namespace APT {
    Application::Application(HINSTANCE hInstance) {
        mHINSTANCE = hInstance;
        CreateApplicationWindow();
        mRenderEngine = std::make_shared<RenderEngine>(mHWND, mDefaultClientWidth, mDefaultClientHeight);
        mPathTracer = std::make_shared<PathTracer>(mRenderEngine);
        mUIRenderer = std::make_unique<UIRenderer>(mRenderEngine, mPathTracer);
        mInited = true;
    }

    Application::~Application()
    {
    }


	void Application::Run()
	{
        bool done = false;
        while (!done) {
            MSG msg = {};
            while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
                if (msg.message == WM_QUIT)
                    done = true;
            }
            Render();
        }
        ShutDown();
	}


    void Application::ShutDown()
    {
        mUIRenderer->ShutDown();
        mRenderEngine->ShutDown();
        ::DestroyWindow(mHWND);
    }


    void Application::Update()
    {
        static uint64_t frameCounter = 0;
        static double elapsedSeconds = 0.0;
        static std::chrono::high_resolution_clock clock;
        static auto t0 = clock.now();

        frameCounter++;
        auto t1 = clock.now();
        auto deltaTime = t1 - t0;
        t0 = t1;
        elapsedSeconds += deltaTime.count() * 1e-9;
        if (elapsedSeconds > 1.0)
        {
            char buffer[500];
            auto fps = frameCounter / elapsedSeconds;
            sprintf_s(buffer, 500, "FPS: %f\n", fps);
            wchar_t wbuffer[500];
            size_t outSize;
            mbstowcs_s(&outSize, wbuffer, size_t(500), buffer, size_t(500));
            OutputDebugString(wbuffer);
            
            frameCounter = 0;
            elapsedSeconds = 0.0;
        }
    }


	void Application::CreateApplicationWindow()
	{
		SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
		const wchar_t* windowClassName = L"DX12WindowClass";
        WNDCLASSEXW windowClass = {};
        windowClass.cbSize = sizeof(WNDCLASSEX);
        windowClass.style = CS_HREDRAW | CS_VREDRAW;
        windowClass.lpfnWndProc = &WndProc;
        windowClass.cbClsExtra = 0;
        windowClass.cbWndExtra = 0;
        windowClass.hInstance = mHINSTANCE;
        windowClass.hIcon = ::LoadIcon(mHINSTANCE, NULL);
        windowClass.hCursor = ::LoadCursor(NULL, IDC_ARROW);
        windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        windowClass.lpszMenuName = NULL;
        windowClass.lpszClassName = windowClassName;
        windowClass.hIconSm = ::LoadIcon(mHINSTANCE, NULL);
        static ATOM atom = ::RegisterClassExW(&windowClass);
        assert(atom > 0);
        int screenWidth = ::GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = ::GetSystemMetrics(SM_CYSCREEN);
        RECT windowRect = { 0, 0, static_cast<LONG>(mDefaultClientWidth), static_cast<LONG>(mDefaultClientHeight) };
        ::AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);
        int windowWidth = windowRect.right - windowRect.left;
        int windowHeight = windowRect.bottom - windowRect.top;
        int windowX = std::max<int>(0, (screenWidth - windowWidth) / 2);
        int windowY = std::max<int>(0, (screenHeight - windowHeight) / 2);
        mHWND = ::CreateWindowExW(NULL, windowClassName, L"Atelier", WS_OVERLAPPEDWINDOW, windowX, windowY,
            windowWidth, windowHeight, NULL, NULL, mHINSTANCE, this
        );
        assert(mHWND && "Failed to create window");
        ::ShowWindow(mHWND, SW_SHOW);
	}


    void Application::Render()
    {
        mRenderEngine->ClearScreen();

        mPathTracer->RenderPreview();

        mUIRenderer->Render();

        mRenderEngine->Present();
    }


    bool Application::IsInitialized()
    {
        return mInited;
    }


    bool Application::HandleMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
        if (mRenderEngine->HandleMessage(hwnd, message, wParam, lParam))
            return true;
        if (mPathTracer->HandleMessage(hwnd, message, wParam, lParam))
            return true;
        return false;
    }
}