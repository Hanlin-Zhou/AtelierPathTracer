#pragma once
#include <GraphicAPI/Device.hpp>
#include <GraphicAPI/Resource.hpp>
#include <DirectX12/d3dx12.h>


namespace DX {
	class DescriptorHeap {
	public:
		DescriptorHeap(const Device& device, D3D12_DESCRIPTOR_HEAP_TYPE type, uint32_t numDescriptors, D3D12_DESCRIPTOR_HEAP_FLAGS flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE);

		ID3D12DescriptorHeap* GetDescriptorHeap()  const;

		UINT GetDesriptorHeapSize() const;

		CD3DX12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandleStart();

		CD3DX12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(int index);

		void CreateRenderTargetView(const Resource& resource, const Device& device, int index);

	protected:
		ComPtr<ID3D12DescriptorHeap> mDescriptorHeap;

		UINT mSize;
	};
}
