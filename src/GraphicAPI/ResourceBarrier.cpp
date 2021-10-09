#include "ResourceBarrier.hpp"

namespace DX {
	ResourceBarrier::ResourceBarrier(const Resource& resource, D3D12_RESOURCE_STATES before, D3D12_RESOURCE_STATES after)
	{
		mBarrier = CD3DX12_RESOURCE_BARRIER::Transition(resource.GetResource(), before, after);
	}
	CD3DX12_RESOURCE_BARRIER ResourceBarrier::GetBarrier()
	{
		return mBarrier;
	}
}

