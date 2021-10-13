#pragma once
#include <DirectX12/d3d12.h>

namespace DX {
	enum class HeapType {
		Default		= D3D12_HEAP_TYPE_DEFAULT,
		Upload		= D3D12_HEAP_TYPE_UPLOAD,
		Readback	= D3D12_HEAP_TYPE_READBACK

	};
}