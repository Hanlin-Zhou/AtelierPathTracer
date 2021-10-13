#include "CommandAllocator.hpp"

namespace DX {
	CommandAllocator::CommandAllocator(const Device& device, D3D12_COMMAND_LIST_TYPE type)
	{
		ThrowIfFailed(device.GetDevice()->CreateCommandAllocator(type, IID_PPV_ARGS(&mCommandAllocator)));
	}

	ID3D12CommandAllocator* CommandAllocator::GetCommandAllocator() const
	{
		return mCommandAllocator.Get();
	}

	void CommandAllocator::Reset()
	{
		mCommandAllocator->Reset();
	}

	GraphicsCommandAllocator::GraphicsCommandAllocator(const Device& device) :CommandAllocator(device, D3D12_COMMAND_LIST_TYPE_DIRECT) {}

	CopyCommandAllocator::CopyCommandAllocator(const Device& device) : CommandAllocator(device, D3D12_COMMAND_LIST_TYPE_COPY) {}

	ComputeCommandAllocator::ComputeCommandAllocator(const Device& device) : CommandAllocator(device, D3D12_COMMAND_LIST_TYPE_COMPUTE) {}

	BundleCommandAllocator::BundleCommandAllocator(const Device& device) : CommandAllocator(device, D3D12_COMMAND_LIST_TYPE_BUNDLE) {}

}
