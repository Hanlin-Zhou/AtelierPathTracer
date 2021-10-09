#pragma once
#include <DirectX12/d3d12.h>
#include <wrl.h>
#include <Windows.h>
#include <GraphicAPI/CommandQueue.hpp>
#include <GraphicAPI/Resource.hpp>
#include <GraphicAPI/DescriptorHeap.hpp>

namespace DX {
	class SwapChain {
	public:
		SwapChain(HWND hWnd, const CommandQueue& commandqueue, uint32_t width, uint32_t height, uint32_t bufferCount);

		UINT GetCurrentBackBufferIndex() const;

		void Present(UINT sync, UINT flag);

		void Resize(uint32_t width, uint32_t height, const Fence &fence);

		void SetFenceValue(int index, uint64_t fencevalue);

		void UpdateRenderTargetViews(DescriptorHeap& descriptorheap, const Device& device);

		uint64_t GetFenceValue(int index);

		IDXGISwapChain4* GetSwapChain() const;

		Resource* GetBackBuffer(int index);

	protected:
		ComPtr<IDXGISwapChain4> mSwapChain;

		std::vector<Resource> mBackBuffers;

		std::vector<uint64_t> mFenceValues;

		uint32_t mNumFrame;
	};
}