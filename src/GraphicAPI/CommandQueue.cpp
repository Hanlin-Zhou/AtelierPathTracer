#include "CommandQueue.hpp"

namespace DX {
    CommandQueue::CommandQueue(const Device& device, D3D12_COMMAND_LIST_TYPE type) {
        D3D12_COMMAND_QUEUE_DESC desc = {};
        desc.Type = type;
        desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
        desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
        desc.NodeMask = 0;
        ThrowIfFailed(device.GetDevice()->CreateCommandQueue(&desc, IID_PPV_ARGS(&mCommandQueue)));
    }


    ID3D12CommandQueue* CommandQueue::getQueue() const
    {
        return mCommandQueue.Get();
    }


    void CommandQueue::ExecuteCommandList(const CommandList& commandlist)
    {
        ID3D12CommandList* const list[] = {commandlist.GetCommandList()};
        mCommandQueue->ExecuteCommandLists(1, list);
    }


    uint64_t CommandQueue::SignalFence(Fence& fence)
    {
        uint64_t value = fence.FenceValueIncrement();
        ThrowIfFailed(mCommandQueue->Signal(fence.GetFence(), value));
        return value;
    }
}

