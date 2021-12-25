#pragma once

namespace APT {
	template <int nSamples> class CoefficientSpectrum {
	public:
		CoefficientSpectrum(float v = 0.f) {
			for (int i = 0; i < nSamples; ++i)
				c[i] = v;
		}

	};
}