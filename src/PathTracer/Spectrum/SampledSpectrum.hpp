#pragma once
#include <PathTracer/Spectrum/CoefficientSpectrum.hpp>

static const int sampledLambdaStart = 400;
static const int sampledLambdaEnd = 700;
static const int nSpectralSamples = 60;

namespace APT {
	class SampledSpectrum : public CoefficientSpectrum<nSpectralSamples> {
	public:
		SampledSpectrum(float v = 0.f) : CoefficientSpectrum(v) {}

		SampledSpectrum(const CoefficientSpectrum<nSpectralSamples>& v) :
			CoefficientSpectrum<nSpectralSamples>(v) {}

		static SampledSpectrum FromSampled(const float* lambda, const float* v, int n)
		{
			

		}
	};

}