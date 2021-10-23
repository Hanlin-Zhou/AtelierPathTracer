#pragma once
#include <ImGui/imgui.h>
#include <ImGui/backends/imgui_impl_dx12.h>
#include <ImGui/backends/imgui_impl_win32.h>
#include <Core/RenderEngine.hpp>
#include <PathTracer/Core/PathTracer.hpp>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <tchar.h>

#include <UI/UIFileMenu.hpp>

#ifdef _DEBUG
#define DX12_ENABLE_DEBUG_LAYER
#endif

namespace  APT {
	class UIRenderer {
	public:
		UIRenderer(std::shared_ptr<RenderEngine> renderengine, std::shared_ptr<PathTracer> pathtracer);
		~UIRenderer();
		void Render();
		void ToggleUI();
		void ShutDown();

	private:
		void LoadStyle();
		void RenderMenuBar();
		bool mHideUI;
		std::shared_ptr<RenderEngine>  mRenderEngine;
		std::shared_ptr<PathTracer> mPathTracer;
		std::unique_ptr<DX::ShaderDescriptorHeap> mUIDescriptorHeap;

		
	};
}