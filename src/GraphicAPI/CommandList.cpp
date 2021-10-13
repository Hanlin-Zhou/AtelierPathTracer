#include "CommandList.hpp"

namespace DX {
	CommandList::CommandList(const Device& device, const CommandAllocator& allocator, D3D12_COMMAND_LIST_TYPE type)
	{
		ThrowIfFailed(device.GetDevice()->CreateCommandList(0, type, allocator.GetCommandAllocator(), nullptr, IID_PPV_ARGS(&mCommandList)));
		ThrowIfFailed(mCommandList->Close());
	}


	ID3D12GraphicsCommandList* CommandList::GetCommandList() const
	{
		return mCommandList.Get();
	}


	void CommandList::SetResourceBarrier(ResourceBarrier& resourcebarrier)
	{
		CD3DX12_RESOURCE_BARRIER const barrier = resourcebarrier.GetBarrier();
		mCommandList->ResourceBarrier(1, &barrier);
	}


	void CommandList::Reset(const CommandAllocator& commandallocator)
	{
		mCommandList->Reset(commandallocator.GetCommandAllocator(), nullptr);
	}


	void CommandList::ClearRenderTargetView(CD3DX12_CPU_DESCRIPTOR_HANDLE rtv, const FLOAT* color)
	{
		mCommandList->ClearRenderTargetView(rtv, color, 0, nullptr);
	}


	void CommandList::Close()
	{
		ThrowIfFailed(mCommandList->Close());
	}


	GraphicsCommandList::GraphicsCommandList(const Device& device, const CommandAllocator& allocator) : CommandList(device, allocator, D3D12_COMMAND_LIST_TYPE_DIRECT) {}

	CopyCommandList::CopyCommandList(const Device& device, const CommandAllocator& allocator) : CommandList(device, allocator, D3D12_COMMAND_LIST_TYPE_COPY) {}

	ComputeCommandList::ComputeCommandList(const Device& device, const CommandAllocator& allocator) : CommandList(device, allocator, D3D12_COMMAND_LIST_TYPE_COMPUTE) {}

	BundleCommandList::BundleCommandList(const Device& device, const CommandAllocator& allocator) : CommandList(device, allocator, D3D12_COMMAND_LIST_TYPE_BUNDLE) {}
}