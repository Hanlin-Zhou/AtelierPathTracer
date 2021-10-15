#include "Shader.hpp"
namespace DX {
	Shader::Shader(ShaderStage stage, LPCWSTR filename)
	{
		mStage = stage;
		DX::ThrowIfFailed(D3DReadFileToBlob(filename, &mShaderBlob));
	}


	VertexShader::VertexShader(LPCWSTR filename) : Shader(ShaderStage::Vertex, filename) {}


	CD3DX12_PIPELINE_STATE_STREAM_VS Shader::GetBytecode() const
	{
		return CD3DX12_SHADER_BYTECODE(mShaderBlob.Get());
	}


	PixelShader::PixelShader(LPCWSTR filename) : Shader(ShaderStage::Pixel, filename) {}
}