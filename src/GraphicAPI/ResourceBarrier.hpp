#pragma once
#include <DirectX12/d3dx12.h>
#include <GraphicAPI/Resource.hpp>

namespace DX {
	class ResourceBarrier {
	public:
		ResourceBarrier(const Resource &resource, D3D12_RESOURCE_STATES before, D3D12_RESOURCE_STATES after);

		CD3DX12_RESOURCE_BARRIER GetBarrier();

	protected:

		CD3DX12_RESOURCE_BARRIER mBarrier;
	};
}