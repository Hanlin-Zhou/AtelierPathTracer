#pragma once
#include <DirectX12/d3d12.h>

namespace DX {
	enum class RootSignatureFlag {
		None				= D3D12_ROOT_SIGNATURE_FLAG_NONE,
		AllowInputLayout	= D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT,
		DenyVertex			= D3D12_ROOT_SIGNATURE_FLAG_DENY_VERTEX_SHADER_ROOT_ACCESS,
		DenyHull			= D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS,
		DenyDomain			= D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS,
		DenyGeometry		= D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS,
		DenyPixel			= D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS,
		AllowStreamOutput	= D3D12_ROOT_SIGNATURE_FLAG_ALLOW_STREAM_OUTPUT,
		Local				= D3D12_ROOT_SIGNATURE_FLAG_LOCAL_ROOT_SIGNATURE,
		DenyAmplification	= D3D12_ROOT_SIGNATURE_FLAG_DENY_AMPLIFICATION_SHADER_ROOT_ACCESS,
		DenyMesh			= D3D12_ROOT_SIGNATURE_FLAG_DENY_MESH_SHADER_ROOT_ACCESS,
		ViewIndexed			= D3D12_ROOT_SIGNATURE_FLAG_CBV_SRV_UAV_HEAP_DIRECTLY_INDEXED,
		SamplerIndexed		= D3D12_ROOT_SIGNATURE_FLAG_SAMPLER_HEAP_DIRECTLY_INDEXED,

	};

	inline RootSignatureFlag operator|(RootSignatureFlag a, RootSignatureFlag b)
	{
		return static_cast<RootSignatureFlag>(static_cast<int>(a) | static_cast<int>(b));
	}
}
