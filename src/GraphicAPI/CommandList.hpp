#pragma once
#include <DirectX12/d3d12.h>
#include <wrl.h>
#include <Windows.h>
#include <GraphicAPI/Device.hpp>
#include <GraphicAPI/CommandAllocator.hpp>
#include <GraphicAPI/ResourceBarrier.hpp>

namespace DX {
	class CommandList {
	public:
		ID3D12GraphicsCommandList* GetCommandList() const;

		void SetResourceBarrier(ResourceBarrier& resourcebarrier);

		void Reset(const CommandAllocator& commandallocator);

		void ClearRenderTargetView(CD3DX12_CPU_DESCRIPTOR_HANDLE rtv, const float* color);

		void Close();

	protected:
		CommandList(const Device& device, const CommandAllocator& allocator, D3D12_COMMAND_LIST_TYPE type);

		ComPtr<ID3D12GraphicsCommandList> mCommandList;
	};


	class GraphicsCommandList : public CommandList {
	public:
		GraphicsCommandList(const Device& device, const CommandAllocator& allocator);
	};


	class CopyCommandList : public CommandList {
	public:
		CopyCommandList(const Device& device, const CommandAllocator& allocator);
	};


	class ComputeCommandList : public CommandList {
	public:
		ComputeCommandList(const Device& device, const CommandAllocator& allocator);
	};

	class BundleCommandList : public CommandList {
	public:
		BundleCommandList(const Device& device, const CommandAllocator& allocator);
	};
}
