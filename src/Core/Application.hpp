#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <shellapi.h>
#include <memory>
#include <chrono>
#include <iostream>
#include <Core/RenderEngine.hpp>
#include <Core/UIRenderer.hpp>
#include <PathTracer/PathTracer.hpp>

namespace APT {
	class Application {
	public:
		Application(HINSTANCE hInstance);
		~Application();
		bool HandleMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
		void Run();
		void ShutDown();
		bool IsInitialized();

	private:
		HWND mHWND;
		HINSTANCE mHINSTANCE;
		uint32_t mDefaultClientWidth = 1280;
		uint32_t mDefaultClientHeight = 720;

		bool mInited = false;
		std::shared_ptr <RenderEngine>  mRenderEngine;
		std::unique_ptr <UIRenderer>  mUIRenderer;
		std::unique_ptr <PathTracer>  mPathTracer;
		

		void CreateApplicationWindow();
		void Update();
		void Render();
		
		//-----------------------------------------------------------//
		
	};
}

