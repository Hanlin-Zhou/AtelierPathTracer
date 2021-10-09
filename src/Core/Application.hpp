#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <shellapi.h>
#include <DirectX12/dxgidebug.h>
#if defined(min)
#undef min
#endif
#if defined(max)
#undef max
#endif
#include <memory>
#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <GraphicAPI/GraphicAPIUtility.hpp>
#include <GraphicAPI/Device.hpp>
#include <GraphicAPI/CommandQueue.hpp>
#include <GraphicAPI/SwapChain.hpp>
#include <GraphicAPI/Adapter.hpp>
#include <GraphicAPI/DescriptorHeap.hpp>
#include <GraphicAPI/Resource.hpp>
#include <GraphicAPI/CommandAllocator.hpp>
#include <GraphicAPI/CommandList.hpp>
#include <Core/RenderEngine.hpp>
#include <Core/UIRenderer.hpp>

namespace APT {
	class Application {
	public:
		Application(HINSTANCE hInstance);
		~Application();
		bool HandleMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
		void Run();
		bool IsInitialized();

	private:
		HWND mHWND;
		HINSTANCE mHINSTANCE;
		uint32_t mDefaultClientWidth = 1280;
		uint32_t mDefaultClientHeight = 720;

		bool mInited = false;
		std::shared_ptr <RenderEngine>  mRenderEngine;
		std::unique_ptr <UIRenderer>  mUIRenderer;
		

		void CreateApplicationWindow();
		void Update();
		void Render();
		
		//-----------------------------------------------------------//
		
	};
}

