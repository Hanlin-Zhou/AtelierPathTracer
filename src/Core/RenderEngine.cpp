#include "RenderEngine.hpp"


namespace APT {
	RenderEngine::RenderEngine(HWND hwnd, uint32_t width, uint32_t height)
	{
        mHWND = hwnd;
        mClientWidth = width;
        mClientHeight = height;
        DX::EnableDebugLayer();
        mAdapter = std::make_unique<DX::Adapter>(false);
        mDevice = std::make_unique<DX::Device>(*mAdapter.get());
        mCommandQueue = std::make_unique<DX::CommandQueue>(*mDevice.get(), D3D12_COMMAND_LIST_TYPE_DIRECT);
        mSwapChain = std::make_unique<DX::SwapChain>(mHWND, *mCommandQueue.get(), mClientWidth, mClientHeight, mNumFrames);
        mDescriptorHeap = std::make_unique<DX::DescriptorHeap>(*mDevice.get(), D3D12_DESCRIPTOR_HEAP_TYPE_RTV, mNumFrames);
        mCurrentBuffer = mSwapChain.get()->GetCurrentBackBufferIndex();
        for (int i = 0; i < mNumFrames; i++)
        {
            mCommandAllocators.push_back(std::make_unique<DX::CommandAllocator>(*mDevice.get(), D3D12_COMMAND_LIST_TYPE_DIRECT));
        }
        mCommandList = std::make_unique<DX::CommandList>(*mDevice.get(), *mCommandAllocators[mCurrentBuffer].get(), D3D12_COMMAND_LIST_TYPE_DIRECT);
        mFence = std::make_unique<DX::Fence>(*mDevice.get());
        mCurrentBuffer = mSwapChain.get()->GetCurrentBackBufferIndex();
        mSwapChain.get()->UpdateRenderTargetViews(*mDescriptorHeap.get(), *mDevice.get());
        mInited = true;
	}

    RenderEngine::~RenderEngine()
    {
        OutputDebugString(L"Destroying RenderEngine---\n");
    }


    bool RenderEngine::HandleMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message) {
        case WM_EXITSIZEMOVE:
            Resize();
        }
        return false;
    }


    void RenderEngine::ClearScreen()
    {
        mCommandAllocators[mCurrentBuffer].get()->Reset();
        mCommandList.get()->Reset(*mCommandAllocators[mCurrentBuffer].get());
        DX::ResourceBarrier barrier(*mSwapChain.get()->GetBackBuffer(mCurrentBuffer), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
        mCommandList.get()->SetResourceBarrier(barrier);
        FLOAT clearColor[] = { 0.4f, 0.6f, 0.9f, 1.0f };
        CD3DX12_CPU_DESCRIPTOR_HANDLE rtv = mDescriptorHeap.get()->GetCPUDescriptorHandle(mCurrentBuffer);
        mCommandList.get()->ClearRenderTargetView(rtv, clearColor);
    }


    void RenderEngine::Present()
    {
        DX::ResourceBarrier barrier(*mSwapChain.get()->GetBackBuffer(mCurrentBuffer), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
        mCommandList->SetResourceBarrier(barrier);
        mCommandList->Close();
        mCommandQueue.get()->ExecuteCommandList(*mCommandList.get());
        UINT sync = 1;
        UINT flag = 0;
        mSwapChain.get()->Present(sync, flag);
        mSwapChain.get()->SetFenceValue(mCurrentBuffer, mCommandQueue.get()->SignalFence(*mFence.get()));
        mCurrentBuffer = mSwapChain.get()->GetCurrentBackBufferIndex();
        mFence.get()->Wait(mSwapChain.get()->GetFenceValue(mCurrentBuffer));
    }

    void RenderEngine::ShutDown()
    {
        Flush();
        mFence.get()->CloseHandle();
    }


    void RenderEngine::Flush()
    {
        uint64_t value = mCommandQueue.get()->SignalFence(*mFence.get());
        mFence.get()->Wait(value);
    }


    void RenderEngine::Resize()
    {
        RECT newRect = {};
        ::GetClientRect(mHWND, &newRect);
        int width = newRect.right - newRect.left;
        int height = newRect.bottom - newRect.top;
        if (mClientWidth == width && mClientHeight == height)
        {
            return;
        }
        mClientWidth = std::max(1u, (uint32_t)width);
        mClientHeight = std::max(1u, (uint32_t)height);
        Flush();
        mSwapChain.get()->Resize(mClientWidth, mClientHeight, *mFence.get());
        mCurrentBuffer = mSwapChain.get()->GetCurrentBackBufferIndex();
        mSwapChain.get()->UpdateRenderTargetViews(*mDescriptorHeap.get(), *mDevice.get());
    }
}