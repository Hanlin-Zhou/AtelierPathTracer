#include "RootSignature.hpp"
namespace DX {
	RootSignature::RootSignature()
	{
		mInited = false;
	}

	void RootSignature::AddParameter(RootParameter parameter)
	{
		mRootParameters.push_back(parameter.GetRootParameter());
	}

	void RootSignature::Init(Device device, RootSignatureFlag flag)
	{
		if (mInited == true) return;
		D3D12_FEATURE_DATA_ROOT_SIGNATURE featureData = {};
		featureData.HighestVersion = D3D_ROOT_SIGNATURE_VERSION_1_1;
		D3D12_ROOT_SIGNATURE_FLAGS rootSignatureFlags = (D3D12_ROOT_SIGNATURE_FLAGS)flag;
		const int paramSize = mRootParameters.size();
		CD3DX12_ROOT_PARAMETER1* params = &mRootParameters[0];
		CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDescription;
		rootSignatureDescription.Init_1_1(mRootParameters.size(), params, 0, nullptr, rootSignatureFlags);
		ComPtr<ID3DBlob> rootSignatureBlob;
		ComPtr<ID3DBlob> errorBlob;
		DX::ThrowIfFailed(D3DX12SerializeVersionedRootSignature(&rootSignatureDescription, featureData.HighestVersion, &rootSignatureBlob, &errorBlob));
		DX::ThrowIfFailed(device.GetDevice()->CreateRootSignature(0, rootSignatureBlob->GetBufferPointer(), 
			rootSignatureBlob->GetBufferSize(), IID_PPV_ARGS(&mRootSignature)));
		mInited = true;
	}
	ComPtr<ID3D12RootSignature> RootSignature::GetRootSignature() const
	{
		return mRootSignature;
	}
}