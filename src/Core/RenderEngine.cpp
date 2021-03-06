#include "RenderEngine.hpp"


namespace APT {
	RenderEngine::RenderEngine(HWND hwnd, uint32_t width, uint32_t height)
	{
        mHWND = hwnd;
        mClientWidth = width;
        mClientHeight = height;
        DX::EnableDebugLayer();
        mAdapter = std::make_unique<DX::Adapter>(false);
        mDevice = std::make_unique<DX::Device>(*mAdapter);
        mCommandQueue = std::make_unique<DX::GraphicsCommandQueue>(*mDevice);
        mSwapChain = std::make_unique<DX::SwapChain>(mHWND, *mCommandQueue, mClientWidth, mClientHeight, mNumFrames);
        mDescriptorHeap = std::make_unique<DX::RTVDescriptorHeap>(*mDevice, mNumFrames);
        mCurrentBuffer = mSwapChain->GetCurrentBackBufferIndex();
        for (int i = 0; i < mNumFrames; i++)
        {
            mCommandAllocators.push_back(std::make_unique<DX::GraphicsCommandAllocator>(*mDevice));
        }
        mCommandList = std::make_unique<DX::GraphicsCommandList>(*mDevice, *mCommandAllocators[mCurrentBuffer]);
        mFence = std::make_unique<DX::Fence>(*mDevice);
        mCurrentBuffer = mSwapChain->GetCurrentBackBufferIndex();
        mSwapChain->UpdateRenderTargetViews(*mDescriptorHeap, *mDevice);
        mInited = true;
	}

    RenderEngine::~RenderEngine()
    {
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
        mCommandAllocators[mCurrentBuffer]->Reset();
        mCommandList->Reset(*mCommandAllocators[mCurrentBuffer]);
        DX::ResourceBarrier barrier(*mSwapChain->GetBackBuffer(mCurrentBuffer), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
        mCommandList->SetResourceBarrier(barrier);
        FLOAT clearColor[] = { 0.4f, 0.6f, 0.9f, 1.0f };
        CD3DX12_CPU_DESCRIPTOR_HANDLE rtv = mDescriptorHeap->GetCPUDescriptorHandle(mCurrentBuffer);
        mCommandList->ClearRenderTargetView(rtv, clearColor);
    }


    void RenderEngine::Present()
    {
        DX::ResourceBarrier barrier(*mSwapChain->GetBackBuffer(mCurrentBuffer), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
        mCommandList->SetResourceBarrier(barrier);
        mCommandList->Close();
        mCommandQueue->ExecuteCommandList(*mCommandList);
        UINT sync = 1;
        UINT flag = 0;
        mSwapChain->Present(sync, flag);
        mSwapChain->SetFenceValue(mCurrentBuffer, mCommandQueue->SignalFence(*mFence));
        mCurrentBuffer = mSwapChain->GetCurrentBackBufferIndex();
        mFence->Wait(mSwapChain->GetFenceValue(mCurrentBuffer));
    }

    void RenderEngine::ShutDown()
    {
        Flush();
        mFence->CloseHandle();
    }


    void RenderEngine::UpdateSubresources(const DX::Resource& dest, const DX::Resource& intermediate, void* dataPtr, UINT size) const
    {
        D3D12_SUBRESOURCE_DATA data = {};
        data.pData = dataPtr;
        data.RowPitch = size;
        data.SlicePitch = data.RowPitch;
        ::UpdateSubresources(mCommandList->GetCommandList(),
            dest.GetResource(), intermediate.GetResource(),
            0, 0, 1, &data);
    }

    void RenderEngine::ClearDepth(DX::DSVDescriptorHeap dsv)
    {
        mCommandList->ClearDepthStencilView(dsv.GetCPUDescriptorHandleStart());
    }

    void RenderEngine::Record()
    {
        mCommandAllocators[mCurrentBuffer]->Reset();
        mCommandList->Reset(*mCommandAllocators[mCurrentBuffer]);
    }

    DX::Device* RenderEngine::Device() const
    {
        return mDevice.get();
    }

    DX::CommandList* RenderEngine::CommandList() const
    {
        return mCommandList.get();
    }

    DX::DescriptorHeap* RenderEngine::DescriptorHeap() const
    {
        return mDescriptorHeap.get();
    }

    uint32_t RenderEngine::GetHeight() const
    {
        return mClientHeight;
    }

    uint32_t RenderEngine::GetWidth() const
    {
        return mClientWidth;
    }

    HWND RenderEngine::GetHWND() const
    {
        return mHWND;
    }


    void RenderEngine::Flush()
    {
        uint64_t value = mCommandQueue->SignalFence(*mFence);
        mFence->Wait(value);
    }

    void RenderEngine::ExcecuteAndWait() {
        mCommandList->Close();
        mCommandQueue->ExecuteCommandList(*mCommandList);
        Flush();
    }

    UINT RenderEngine::GetCurrentBufferIndex()
    {
        return mCurrentBuffer;
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
        mSwapChain->Resize(mClientWidth, mClientHeight, *mFence);
        mCurrentBuffer = mSwapChain->GetCurrentBackBufferIndex();
        mSwapChain->UpdateRenderTargetViews(*mDescriptorHeap, *mDevice);
    }
}