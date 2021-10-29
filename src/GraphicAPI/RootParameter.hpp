#pragma once
#include <DirectX12/d3d12.h>
#include <GraphicAPI/ShaderVisibilityFlag.hpp>
namespace DX {
	class RootParameter {
	public:
		RootParameter(UINT size, UINT shaderRegister, UINT shaderSpace, ShaderVisibilityFlag flag);
		CD3DX12_ROOT_PARAMETER1 GetRootParameter() const;

	private:
		CD3DX12_ROOT_PARAMETER1 mRootParameter;
		UINT mSize;
		UINT mShaderRegister;
		UINT mShaderSpace;
		D3D12_SHADER_VISIBILITY mFlag;

	};
}