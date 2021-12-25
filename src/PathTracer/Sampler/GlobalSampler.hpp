#pragma once
#include <PathTracer/Sampler/Sampler.hpp>

namespace APT {
	class GlobalSampler : public Sampler {
	public:
        GlobalSampler(unsigned int SPP);
        bool StartNextSample();
        void StartPixel(const Vec2i &p);
        bool SetSampleNumber(unsigned int sampleNum);
        float Get1D();
        Vec2f Get2D();
        
        virtual unsigned int GetIndexForSample(unsigned int sampleNum) const = 0;
        virtual float SampleDimension(unsigned int index, int dimension) const = 0;
    private:
        int mDimension;
        unsigned int mIntervalSampleIndex;
        static const int mArrayStartDim = 5;
        int mArrayEndDim;
	};
}