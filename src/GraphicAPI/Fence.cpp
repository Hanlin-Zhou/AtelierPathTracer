#include "Fence.hpp"

namespace DX {
	Fence::Fence(const Device& device)
	{
		ThrowIfFailed(device.GetDevice()->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&mFence)));
		mFenceEvent = CreateEventHandle();
		mFenceValue = 0;
	}


	HANDLE Fence::GetFenceEvent()
	{
		return mFenceEvent;
	}


	uint64_t Fence::GetFenceValue() const
	{
		return mFenceValue;
	}


	uint64_t Fence::FenceValueIncrement() 
	{
		mFenceValue++;
		return mFenceValue;
	}


	void Fence::Wait(uint64_t value, std::chrono::milliseconds duration)
	{
		if (mFence->GetCompletedValue() < value)
		{
			ThrowIfFailed(mFence->SetEventOnCompletion(value, mFenceEvent));
			::WaitForSingleObject(mFenceEvent, static_cast<DWORD>(duration.count()));
		}
	}


	void Fence::CloseHandle()
	{
		::CloseHandle(mFenceEvent);
	}


	ID3D12Fence* Fence::GetFence()
	{
		return mFence.Get();
	}
}