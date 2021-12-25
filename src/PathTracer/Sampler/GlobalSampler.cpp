#include "GlobalSampler.hpp"
#pragma once
namespace APT {
	GlobalSampler::GlobalSampler(unsigned int SPP) : Sampler(SPP) {}

	bool GlobalSampler::StartNextSample()
	{
		mDimension = 0;
		mIntervalSampleIndex = GetIndexForSample(mCurrentPixelSamplerIndex + 1);
		return Sampler::StartNextSample();
	}

	void GlobalSampler::StartPixel(const Vec2i& p)
	{
		Sampler::StartPixel(p);
		mDimension = 0;
		mIntervalSampleIndex = GetIndexForSample(0);
		mArrayEndDim = mArrayStartDim + mArray1D.size() + 2 * mArray2D.size();

		for (unsigned int i = 0; i < m1DArraySize.size(); ++i) {
			int nSamples = m1DArraySize[i] * mSPP;
			for (int j = 0; j < nSamples; ++j) {
				unsigned int index = GetIndexForSample(j);
				mArray1D[i][j] =
					SampleDimension(index, mArrayStartDim + i);
			}
		}

		int dimension = mArrayStartDim + m1DArraySize.size();
		for (unsigned int i = 0; i < m2DArraySize.size(); ++i) {
			int nSamples = m2DArraySize[i] * mSPP;
			for (int j = 0; j < nSamples; ++j) {
				unsigned int index = GetIndexForSample(j);
				mArray2D[i][j].x = SampleDimension(index, dimension);
				mArray2D[i][j].y = SampleDimension(index, dimension + 1);
			}
			dimension += 2;
		}
	}

	bool GlobalSampler::SetSampleNumber(unsigned int sampleNum)
	{
		mDimension = 0;
		mIntervalSampleIndex = GetIndexForSample(sampleNum);
		return Sampler::SetSampleNumber(sampleNum);
	}

	float GlobalSampler::Get1D()
	{
		if (mDimension >= mArrayStartDim && mDimension < mArrayEndDim)
			mDimension = mArrayEndDim;
		return SampleDimension(mIntervalSampleIndex, mDimension++);
	}

	Vec2f GlobalSampler::Get2D()
	{
		if (mDimension + 1 >= mArrayStartDim && mDimension < mArrayEndDim)
			mDimension = mArrayEndDim;
		Vec2f p(SampleDimension(mIntervalSampleIndex, mDimension),
			SampleDimension(mIntervalSampleIndex, mDimension + 1));
		mDimension += 2;
		return p;
	}


}