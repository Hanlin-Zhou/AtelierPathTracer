#pragma once
#include <PathTracer/Sampler/Sampler.hpp>
#include <Utility/RNG.hpp>

namespace APT {
	class PixelSampler : public Sampler {
	public:
		PixelSampler(unsigned int SPP, int Dimension);
		bool StartNextSample();
		bool SetSampleNumber(unsigned int sampleNum);
		float Get1D();
		Vec2f Get2D();

	protected:
		std::vector<std::vector<float>> mSamples1D;
		std::vector<std::vector<Vec2f>> mSamples2D;
		int mCurrentDimension1D = 0, mCurrentDimension2D = 0;
		RNG rng;

	};
}