#include "RootParameter.hpp"
namespace DX {
	RootParameter::RootParameter(UINT size, UINT shaderRegister, UINT shaderSpace, ShaderVisibilityFlag flag)
	{
		mRootParameter.InitAsConstants(size, shaderRegister, shaderSpace, (D3D12_SHADER_VISIBILITY)flag);
		mSize = size;
		mShaderRegister = shaderRegister;
		mShaderSpace = shaderSpace;
		mFlag = (D3D12_SHADER_VISIBILITY)flag;
	}

	CD3DX12_ROOT_PARAMETER1 RootParameter::GetRootParameter() const
	{
		return mRootParameter;
	}
}