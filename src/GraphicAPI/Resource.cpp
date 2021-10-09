#include "Resource.hpp"

namespace DX {
	


	Resource::Resource(const ComPtr<ID3D12Resource>& resource)
	{
		mResource = resource;
	}


	void Resource::Reset()
	{
		mResource.Reset();
	}


	ID3D12Resource* Resource::GetResource() const
	{
		return mResource.Get();
	}


	ComPtr<ID3D12Resource> Resource::GetComPtr()
	{
		return mResource;
	}

}

