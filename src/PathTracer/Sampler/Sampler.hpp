#pragma once
#ifdef PBRT_FLOAT_IS_DOUBLE
static const float OneMinusEpsilon = 0x1.fffffffffffffp-1;
#else
static const float OneMinusEpsilon = 0x1.fffffep-1;
#endif

#include <PathTracer/GeometryMath/Vector.hpp>
#include <vector>
using namespace Math;

namespace APT {
	class Sampler {
	public:
		Sampler(unsigned int SPP);

		virtual void StartPixel(const Vec2i& p);
		virtual float Get1D() = 0;
		virtual Vec2f Get2D() = 0;

		// Member
		const unsigned int mSPP;
	protected:
		Vec2i mCurrentPixel;
		unsigned int mCurrentPixelSamplerIndex;
		std::vector<int> m1DArraySize, m2DArraySize;
		std::vector<std::vector<float>> mArray1D;
		std::vector<std::vector<Vec2f>> mArray2D;

	private:
		size_t mOffset1D, mOffset2D;

	};
}