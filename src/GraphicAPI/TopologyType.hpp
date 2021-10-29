#pragma once
#include <DirectX12/d3d12.h>

namespace DX {
	enum class TopologyType {
		Undefined		= D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED,
		Point			= D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT,
		Line			= D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE,
		Triangle		= D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE,
		Patch			= D3D12_PRIMITIVE_TOPOLOGY_TYPE_PATCH
	};

}
