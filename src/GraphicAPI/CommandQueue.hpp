#pragma once

#include <DirectX12/d3d12.h>
#include <wrl.h>
#include <GraphicAPI/Fence.hpp>
#include <GraphicAPI/Device.hpp>
#include <GraphicAPI/CommandList.hpp>
#include <GraphicAPI/GraphicAPIUtility.hpp>

using namespace Microsoft::WRL;

namespace DX {
	class CommandQueue {
	public:
		ID3D12CommandQueue* getQueue() const;

		void ExecuteCommandList(const CommandList &commandlist);

		uint64_t SignalFence(Fence& fence);

		void waitFence();

	protected:
		CommandQueue(const Device& device, D3D12_COMMAND_LIST_TYPE type);

		ComPtr<ID3D12CommandQueue> mCommandQueue;
	};


	class GraphicsCommandQueue : public CommandQueue {
	public:
		GraphicsCommandQueue(const Device& device);
	};


	class CopyCommandQueue : public CommandQueue {
	public:
		CopyCommandQueue(const Device& device);
	};


	class ComputeCommandQueue : public CommandQueue {
	public:
		ComputeCommandQueue(const Device& device);
	};


	class BundleCommandQueue : public CommandQueue {
	public:
		BundleCommandQueue(const Device& device);
	};
}