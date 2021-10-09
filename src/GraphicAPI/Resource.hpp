#pragma once
#include <wrl.h>
#include <DirectX12/d3d12.h>


using namespace Microsoft::WRL;

namespace DX {
	class Resource {
	public:
		Resource(const ComPtr<ID3D12Resource> &resource);

		void Reset();

		ID3D12Resource* GetResource() const;

		ComPtr<ID3D12Resource> GetComPtr();

	protected:
		ComPtr<ID3D12Resource> mResource;

	};
}