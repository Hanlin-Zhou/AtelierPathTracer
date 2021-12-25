#include "Sampler.hpp"
namespace APT {
	Sampler::Sampler(unsigned int SPP) : mSPP(SPP) {}

	CameraSample Sampler::GetCameraSample(const Vec2i& pRaster)
	{
		CameraSample cs;
		cs.mFilm = (Vec2f)pRaster + Get2D();
		cs.mTime = Get1D();
		cs.mLens = Get2D();
		return cs;
	}

	int Sampler::RoundCount(int n) const {
		return n;
	}

	void Sampler::Request1DArray(int n)
	{
		m1DArraySize.push_back(n);
		mArray1D.push_back(std::vector<float>(n * mSPP));
	}

	void Sampler::Request2DArray(int n)
	{
		m2DArraySize.push_back(n);
		mArray2D.push_back(std::vector<Vec2f>(n * mSPP));
	}

	const float* Sampler::Get1DArray(int n)
	{
		if (mOffset1D == mArray1D.size())
			return nullptr;
		return &mArray1D[mOffset1D++][mCurrentPixelSamplerIndex * n];
	}

	const Vec2f* Sampler::Get2DArray(int n)
	{
		if (mOffset2D == mArray2D.size())
			return nullptr;
		return &mArray2D[mOffset2D++][mCurrentPixelSamplerIndex * n];
	}

	void Sampler::StartPixel(const Vec2i& p)
	{
		mCurrentPixel = p;
		mCurrentPixelSamplerIndex = 0;
		mOffset1D = 0;
		mOffset2D = 0;
	}

	bool Sampler::StartNextSample()
	{
		mOffset1D = 0;
		mOffset2D = 0;
		return ++mCurrentPixelSamplerIndex < mSPP;
	}

	bool Sampler::SetSampleNumber(unsigned int sampleNum)
	{
		mOffset1D = 0;
		mOffset2D = 0;
		mCurrentPixelSamplerIndex = sampleNum;
		return mCurrentPixelSamplerIndex < mSPP;
	}
}