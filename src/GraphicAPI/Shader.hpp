#pragma once
#include <DirectX12/d3dx12.h>
#include <d3dcompiler.h>
#include <GraphicAPI/GraphicAPIUtility.hpp>
#include <wrl.h>
using namespace Microsoft::WRL;

namespace DX {
	enum class ShaderStage {
		Vertex,
		Geometry,
		Stream,
		Hull,
		Domain,
		Pixel,
		Compute
	};

	class Shader {
	public:
		CD3DX12_PIPELINE_STATE_STREAM_VS GetBytecode() const;

	protected:
		Shader(ShaderStage stage, LPCWSTR filename);
		
		ComPtr<ID3DBlob> mShaderBlob;
		ShaderStage mStage;
	};


	class VertexShader :public Shader {
	public:
		VertexShader(LPCWSTR filename);
	};


	class PixelShader :public Shader {
	public:
		PixelShader(LPCWSTR filename);
	};
}
