#include "PixelSampler.hpp"
namespace APT {
	PixelSampler::PixelSampler(unsigned int SPP, int Dimension) : Sampler(SPP)
	{
		for (int i = 0; i < Dimension; ++i) {
			mSamples1D.push_back(std::vector<float>(SPP));
			mSamples2D.push_back(std::vector<Vec2f>(SPP));
		}
	}

	bool PixelSampler::StartNextSample()
	{
		mCurrentDimension1D = mCurrentDimension2D = 0;
		return Sampler::StartNextSample();
	}

	bool PixelSampler::SetSampleNumber(unsigned int sampleNum)
	{
		mCurrentDimension1D = mCurrentDimension2D = 0;
		return Sampler::SetSampleNumber(sampleNum);
	}

	float PixelSampler::Get1D()
	{
		if (mCurrentDimension1D < mSamples1D.size())
			return mSamples1D[mCurrentDimension1D++][mCurrentPixelSamplerIndex];
		else
			return rng.UniformFloat();
	}

	Vec2f PixelSampler::Get2D()
	{
		if (mCurrentDimension1D < mSamples1D.size())
			return mSamples2D[mCurrentDimension1D++][mCurrentPixelSamplerIndex];
		else
			return Vec2f(rng.UniformFloat(), rng.UniformFloat());
	}
}