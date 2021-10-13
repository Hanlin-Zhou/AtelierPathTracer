#pragma once
#include <ImGui/imgui.h>
#include <ImGui/backends/imgui_impl_dx12.h>
#include <ImGui/backends/imgui_impl_win32.h>
#include <Core/RenderEngine.hpp>
#include <d3d12.h>
#include <dxgi1_4.h>

#include <tchar.h>

#ifdef _DEBUG
#define DX12_ENABLE_DEBUG_LAYER
#endif

namespace  APT {
	class UIRenderer {
	public:
		UIRenderer(std::shared_ptr<RenderEngine> renderengine);
		~UIRenderer();
		void Render();
		void ToggleUI();
		void ShutDown();

	private:
		bool mHideUI;
		std::shared_ptr<RenderEngine>  mRenderEngine;
		std::unique_ptr<DX::ShaderDescriptorHeap> mUIDescriptorHeap;

		
	};
}