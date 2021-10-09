#pragma once
#include <GraphicAPI/GraphicAPIUtility.hpp>
#include <GraphicAPI/Device.hpp>
#include <GraphicAPI/CommandQueue.hpp>
#include <GraphicAPI/SwapChain.hpp>
#include <GraphicAPI/Adapter.hpp>
#include <GraphicAPI/DescriptorHeap.hpp>
#include <GraphicAPI/Resource.hpp>
#include <GraphicAPI/CommandAllocator.hpp>
#include <GraphicAPI/CommandList.hpp>

namespace APT {
	class RenderEngine {
	public:
		RenderEngine(HWND hwnd, uint32_t width, uint32_t height);
		~RenderEngine();
		bool HandleMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
		void ClearScreen();
		void Present();
		void ShutDown();
		friend class UIRenderer;
	private:
		HWND mHWND;
		uint32_t mClientWidth;
		uint32_t mClientHeight;
		const uint8_t mNumFrames = 3;
		UINT mCurrentBuffer;
		bool mInited = false;
		std::unique_ptr <DX::Adapter> mAdapter;
		std::unique_ptr <DX::Device> mDevice;
		std::unique_ptr <DX::CommandQueue> mCommandQueue;
		std::unique_ptr <DX::SwapChain> mSwapChain;
		std::unique_ptr <DX::DescriptorHeap> mDescriptorHeap;
		std::unique_ptr <DX::CommandList> mCommandList;
		std::unique_ptr <DX::Fence> mFence;
		std::vector<std::unique_ptr<DX::CommandAllocator>> mCommandAllocators;

		void Flush();
		void Resize();
	};
}