#include "Adapter.hpp"

namespace DX {
    Adapter::Adapter(bool warp) {
        ComPtr<IDXGIFactory4> Factory;
        UINT createFactoryFlags = 0;
#if defined(_DEBUG)
        createFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;
#endif

        ThrowIfFailed(CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&Factory)));

        ComPtr<IDXGIAdapter1> Adapter1;

        if (warp)
        {
            ThrowIfFailed(Factory->EnumWarpAdapter(IID_PPV_ARGS(&Adapter1)));
            ThrowIfFailed(Adapter1.As(&mAdapter));
        }
        else
        {
            SIZE_T maxDedicatedVideoMemory = 0;
            for (UINT i = 0; Factory->EnumAdapters1(i, &Adapter1) != DXGI_ERROR_NOT_FOUND; ++i)
            {
                DXGI_ADAPTER_DESC1 AdapterDesc1;
                Adapter1->GetDesc1(&AdapterDesc1);
                if ((AdapterDesc1.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) == 0 &&
                    SUCCEEDED(D3D12CreateDevice(Adapter1.Get(),
                        D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), nullptr)) &&
                    AdapterDesc1.DedicatedVideoMemory > maxDedicatedVideoMemory)
                {
                    maxDedicatedVideoMemory = AdapterDesc1.DedicatedVideoMemory;
                    ThrowIfFailed(Adapter1.As(&mAdapter));
                }
            }
        }

    }

    IDXGIAdapter4* Adapter::GetAdapter() const
    {
        return mAdapter.Get();
    }


}

