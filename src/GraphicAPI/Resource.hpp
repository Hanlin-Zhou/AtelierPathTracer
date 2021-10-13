#pragma once
#include <wrl.h>
#include <DirectX12/d3d12.h>


using namespace Microsoft::WRL;

namespace DX {
	class Resource {
	public:
		Resource();

		Resource(const ComPtr<ID3D12Resource> &resource);

		void Reset();

		void Set(ComPtr<ID3D12Resource> resource);

		ID3D12Resource* GetResource() const;

		bool IsCompleted();

		D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress();
	protected:
		ComPtr<ID3D12Resource> mResource;

		D3D12_RESOURCE_DESC mDescriptor;

		bool mCompleted = false;
	};
}