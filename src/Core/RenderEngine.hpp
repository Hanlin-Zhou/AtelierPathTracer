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
#include <GraphicAPI/PipelineState.hpp>
#include <GraphicAPI/RootSignature.hpp>
#include <GraphicAPI/ResourceInfo.hpp>
#include <DirectXMath.h>

namespace APT {
	class RenderEngine {
	public:
		RenderEngine(HWND hwnd, uint32_t width, uint32_t height);
		~RenderEngine();
		bool HandleMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
		void ClearScreen();
		void Present();
		void ShutDown();
		void UpdateSubresources(const DX::Resource &dest, const DX::Resource &intermediate, void* data, UINT size) const;
		void ClearDepth(DX::DSVDescriptorHeap dsv);
		void Record();
		void ExcecuteAndWait();
		UINT GetCurrentBufferIndex();


		DX::Device* Device() const;
		DX::CommandList* CommandList() const;
		DX::DescriptorHeap* DescriptorHeap() const;
		friend class UIRenderer;

		HWND mHWND;
		uint32_t mClientWidth;
		uint32_t mClientHeight;
		const uint8_t mNumFrames = 3;

		uint32_t GetHeight() const;
		uint32_t GetWidth() const;
		HWND GetHWND() const;
	private:
		
		UINT mCurrentBuffer;
		bool mInited = false;
		std::unique_ptr <DX::Adapter> mAdapter;
		std::unique_ptr <DX::Device> mDevice;
		std::unique_ptr <DX::GraphicsCommandQueue> mCommandQueue;
		std::unique_ptr <DX::SwapChain> mSwapChain;
		std::unique_ptr <DX::RTVDescriptorHeap> mDescriptorHeap;
		std::unique_ptr <DX::GraphicsCommandList> mCommandList;
		std::unique_ptr <DX::Fence> mFence;
		std::vector<std::unique_ptr<DX::GraphicsCommandAllocator>> mCommandAllocators;

		void Flush();
		void Resize();
	};
}