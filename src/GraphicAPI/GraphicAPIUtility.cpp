#include "GraphicAPIUtility.hpp"

namespace DX {
	void EnableDebugLayer()
	{
#if defined(_DEBUG)
		Microsoft::WRL::ComPtr<ID3D12Debug> debugInterface;
		ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&debugInterface)));
		debugInterface->EnableDebugLayer();
#endif
	}

	bool CheckTearingSupport()
	{
        BOOL allowTearing = FALSE;
		Microsoft::WRL::ComPtr<IDXGIFactory4> factory4;
        if (SUCCEEDED(CreateDXGIFactory1(IID_PPV_ARGS(&factory4))))
        {
			Microsoft::WRL::ComPtr<IDXGIFactory5> factory5;
            if (SUCCEEDED(factory4.As(&factory5)))
            {
                if (FAILED(factory5->CheckFeatureSupport(
                    DXGI_FEATURE_PRESENT_ALLOW_TEARING,
                    &allowTearing, sizeof(allowTearing))))
                {
                    allowTearing = FALSE;
                }
            }
        }
        return allowTearing == TRUE;
	}

	HANDLE CreateEventHandle()
	{
		HANDLE Event;

		Event = ::CreateEvent(NULL, FALSE, FALSE, NULL);
		assert(Event && "Failed to create fence event.");

		return Event;
	}


}
