#pragma once
#include <Pathtracer/Spectrum/SampledSpectrum.hpp>

namespace APT {
	float InterpolateSpectrumSamples(const float* lambda, const float* vals, int n, float l) {
		if (l <= lambda[0])     return vals[0];
		if (l >= lambda[n - 1]) return vals[n - 1];
		int offset = Math::FindInterval(n, [&](int index) { return lambda[index] <= l; });
		float t = (l - lambda[offset]) / (lambda[offset + 1] - lambda[offset]);
		return Math::Lerp(t, vals[offset], vals[offset + 1]);
	}

	class RGBSpectrum : public CoefficientSpectrum<3> {
	public:
		RGBSpectrum(float v = 0.f) : CoefficientSpectrum<3>(v) {}

		RGBSpectrum(const CoefficientSpectrum<3>& v) : CoefficientSpectrum<3>(v) {}

		RGBSpectrum(const RGBSpectrum& s, SpectrumType type = SpectrumType::Reflectance) {
			*this = s;
		}

		static RGBSpectrum FromRGB(const float rgb[3],
			SpectrumType type = SpectrumType::Reflectance) {
			RGBSpectrum s;
			s.c[0] = rgb[0];
			s.c[1] = rgb[1];
			s.c[2] = rgb[2];
			return s;
		}

		void ToRGB(float* rgb) const {
			rgb[0] = c[0];
			rgb[1] = c[1];
			rgb[2] = c[2];
		}

		const RGBSpectrum& ToRGBSpectrum() const {
			return *this;
		}

		void ToXYZ(float xyz[3]) const {
			RGBToXYZ(c, xyz);
		}

		static RGBSpectrum FromXYZ(const float xyz[3],
			SpectrumType type = SpectrumType::Reflectance) {
			RGBSpectrum r;
			XYZToRGB(xyz, r.c);
			return r;
		}

		float y() const {
			const float YWeight[3] = { 0.212671f, 0.715160f, 0.072169f };
			return YWeight[0] * c[0] + YWeight[1] * c[1] + YWeight[2] * c[2];
		}



		static RGBSpectrum FromSampled(const float* lambda, const float* v,
			int n)
		{
			if (!SpectrumSamplesSorted(lambda, v, n)) {
				std::vector<float> slambda(&lambda[0], &lambda[n]);
				std::vector<float> sv(&v[0], &v[n]);
				SortSpectrumSamples(&slambda[0], &sv[0], n);
				return FromSampled(&slambda[0], &sv[0], n);
			}

			float xyz[3] = { 0, 0, 0 };
			for (int i = 0; i < nCIESamples; ++i) {
				float val = InterpolateSpectrumSamples(lambda, v, n, CIE_lambda[i]);
				xyz[0] += val * CIE_X[i];
				xyz[1] += val * CIE_Y[i];
				xyz[2] += val * CIE_Z[i];
			}
			float scale = float(CIE_lambda[nCIESamples - 1] - CIE_lambda[0]) /
				float(CIE_Y_integral * nCIESamples);
			xyz[0] *= scale;
			xyz[1] *= scale;
			xyz[2] *= scale;
			return FromXYZ(xyz);
		}
	};
}