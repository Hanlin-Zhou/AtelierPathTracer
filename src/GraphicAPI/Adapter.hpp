#pragma once

#include <DirectX12/d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
//#include <cstdint>
//#include <queue>
#include <GraphicAPI/GraphicAPIUtility.hpp>

using namespace Microsoft::WRL;

namespace DX {
	class Adapter {
	public:
		Adapter(bool warp);

		IDXGIAdapter4* GetAdapter() const;

	protected:
		ComPtr<IDXGIAdapter4> mAdapter;
	};


}