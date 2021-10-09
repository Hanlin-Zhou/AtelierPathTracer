#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <wrl.h>
#include <DirectX12/d3dx12.h>
#include <dxgi1_6.h>
#include <exception>
#include <cassert>

namespace DX {
    inline void ThrowIfFailed(HRESULT hr)
    {
        if (FAILED(hr))
        {
            throw std::exception();
        }
    }


    void EnableDebugLayer();

    bool CheckTearingSupport();

    HANDLE CreateEventHandle();
}