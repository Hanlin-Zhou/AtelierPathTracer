#pragma once
#include <DirectX12/d3d12.h>
#include <wrl.h>
#include <Windows.h>
#include <GraphicAPI/Device.hpp>

namespace DX {
	class CommandAllocator {
	public:
		
		ID3D12CommandAllocator* GetCommandAllocator() const;
		void Reset();
	
	protected:
		CommandAllocator(const Device& device, D3D12_COMMAND_LIST_TYPE type);
		ComPtr<ID3D12CommandAllocator> mCommandAllocator;
	};


	class GraphicsCommandAllocator : public CommandAllocator {
	public:
		GraphicsCommandAllocator(const Device& device);
	};


	class CopyCommandAllocator : public CommandAllocator {
	public:
		CopyCommandAllocator(const Device& device);
	};


	class ComputeCommandAllocator : public CommandAllocator {
	public:
		ComputeCommandAllocator(const Device& device);
	};


	class BundleCommandAllocator : public CommandAllocator {
	public:
		BundleCommandAllocator(const Device& device);
	};
}

