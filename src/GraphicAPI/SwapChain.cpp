#include "SwapChain.hpp"

namespace DX {
	SwapChain::SwapChain(HWND hWnd, const CommandQueue& commandqueue, uint32_t width, uint32_t height, uint32_t bufferCount)
	{
		ComPtr<IDXGIFactory4> Factory4;
		UINT FactoryFlags = 0;
#if defined(_DEBUG)
		FactoryFlags = DXGI_CREATE_FACTORY_DEBUG;
#endif
		ThrowIfFailed(CreateDXGIFactory2(FactoryFlags, IID_PPV_ARGS(&Factory4)));

        DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
        swapChainDesc.Width = width;
        swapChainDesc.Height = height;
        swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDesc.Stereo = FALSE;
        swapChainDesc.SampleDesc = { 1, 0 };
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferCount = bufferCount;
        swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
        swapChainDesc.Flags = CheckTearingSupport() ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0;

        ComPtr<IDXGISwapChain1> swapChain1;
        ThrowIfFailed(Factory4->CreateSwapChainForHwnd(commandqueue.getQueue(), hWnd, &swapChainDesc, nullptr, nullptr, &swapChain1));
        ThrowIfFailed(Factory4->MakeWindowAssociation(hWnd, DXGI_MWA_NO_ALT_ENTER));
        ThrowIfFailed(swapChain1.As(&mSwapChain));

        for (int i = 0; i < bufferCount; i++)
        {
            ComPtr<ID3D12Resource> resource;
            mSwapChain->GetBuffer(i, IID_PPV_ARGS(&resource));
            mBackBuffers.push_back(Resource(resource));
            mFenceValues.push_back(0);
        }

        mNumFrame = bufferCount;
	}

    UINT SwapChain::GetCurrentBackBufferIndex() const
    {
        return mSwapChain->GetCurrentBackBufferIndex();
    }


    void SwapChain::Present(UINT sync, UINT flag)
    {
        ThrowIfFailed(mSwapChain->Present(sync, flag));
    }


    void SwapChain::Resize(uint32_t width, uint32_t height, const Fence& fence)
    {
        for (int i = 0; i < mNumFrame; i++)
        {
            mBackBuffers[i].Reset();
            mFenceValues[i] = 0;
        }
        DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
        ThrowIfFailed(mSwapChain->GetDesc(&swapChainDesc));
        ThrowIfFailed(mSwapChain->ResizeBuffers(mNumFrame, width, height, swapChainDesc.BufferDesc.Format, swapChainDesc.Flags));
        for (int i = 0; i < mNumFrame; i++)
        {
            ComPtr<ID3D12Resource> resource;
            mSwapChain->GetBuffer(i, IID_PPV_ARGS(&resource));
            mBackBuffers[i] = (Resource(resource));
            mFenceValues[i] = 0;
        }
    }


    void SwapChain::SetFenceValue(int index, uint64_t fencevalue)
    {
        mFenceValues[index] = fencevalue;
    }


    void SwapChain::UpdateRenderTargetViews(DescriptorHeap& descriptorheap, const Device& device)
    {
        for (int i = 0; i < mNumFrame; ++i)
        {
            descriptorheap.CreateRenderTargetView(*GetBackBuffer(i), device, i);
        }
    }


    uint64_t SwapChain::GetFenceValue(int index)
    {
        return mFenceValues[index];
    }


    IDXGISwapChain4* SwapChain::GetSwapChain() const
    {
        return mSwapChain.Get();
    }


    Resource* SwapChain::GetBackBuffer(int index)
    {
        return &mBackBuffers[index];
    }


}