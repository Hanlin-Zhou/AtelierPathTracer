#pragma once
#include <DirectX12/d3d12.h>
#include <directxmath.h>

namespace DX {
	struct VertexInput
	{
		DirectX::XMFLOAT3 Position;
	};

	inline constexpr D3D12_INPUT_ELEMENT_DESC InputLayout[2] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 1, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	};

	inline constexpr UINT InputLayoutSize = _countof(InputLayout);
}