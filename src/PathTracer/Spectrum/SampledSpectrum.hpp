#pragma once
#include <PathTracer/Spectrum/CoefficientSpectrum.hpp>
#include <PathTracer/GeometryMath/MathHelper.hpp>
#include <algorithm>
#include <vector>



namespace APT {
	float AverageSpectrumSamples(const float* lambda, const float* vals,
		int n, float lambdaStart, float lambdaEnd);
	bool SpectrumSamplesSorted(const float* lambda, const float* vals, int n);
	void SortSpectrumSamples(float* lambda, float* vals, int n);

	static const int sampledLambdaStart = 400;
	static const int sampledLambdaEnd = 700;
	static const int nSpectralSamples = 60;

	static const float CIE_Y_integral = 106.856895;
	static const int nCIESamples = 471;
	extern const float CIE_X[nCIESamples];
	extern const float CIE_Y[nCIESamples];
	extern const float CIE_Z[nCIESamples];
	extern const float CIE_lambda[nCIESamples];

	enum class SpectrumType { Reflectance, Illuminant };
	static const int nRGB2SpectSamples = 32;
	extern const float RGB2SpectLambda[nRGB2SpectSamples];
	extern const float RGBRefl2SpectWhite[nRGB2SpectSamples];
	extern const float RGBRefl2SpectCyan[nRGB2SpectSamples];
	extern const float RGBRefl2SpectMagenta[nRGB2SpectSamples];
	extern const float RGBRefl2SpectYellow[nRGB2SpectSamples];
	extern const float RGBRefl2SpectRed[nRGB2SpectSamples];
	extern const float RGBRefl2SpectGreen[nRGB2SpectSamples];
	extern const float RGBRefl2SpectBlue[nRGB2SpectSamples];

	extern const float RGBIllum2SpectWhite[nRGB2SpectSamples];
	extern const float RGBIllum2SpectCyan[nRGB2SpectSamples];
	extern const float RGBIllum2SpectMagenta[nRGB2SpectSamples];
	extern const float RGBIllum2SpectYellow[nRGB2SpectSamples];
	extern const float RGBIllum2SpectRed[nRGB2SpectSamples];
	extern const float RGBIllum2SpectGreen[nRGB2SpectSamples];
	extern const float RGBIllum2SpectBlue[nRGB2SpectSamples];

	inline void XYZToRGB(const float xyz[3], float rgb[3]) {
		rgb[0] = 3.240479f * xyz[0] - 1.537150f * xyz[1] - 0.498535f * xyz[2];
		rgb[1] = -0.969256f * xyz[0] + 1.875991f * xyz[1] + 0.041556f * xyz[2];
		rgb[2] = 0.055648f * xyz[0] - 0.204043f * xyz[1] + 1.057311f * xyz[2];
	}

	inline void RGBToXYZ(const float rgb[3], float xyz[3]) {
		xyz[0] = 0.412453f * rgb[0] + 0.357580f * rgb[1] + 0.180423f * rgb[2];
		xyz[1] = 0.212671f * rgb[0] + 0.715160f * rgb[1] + 0.072169f * rgb[2];
		xyz[2] = 0.019334f * rgb[0] + 0.119193f * rgb[1] + 0.950227f * rgb[2];
	}
	
	class RGBSpectrum;

	class SampledSpectrum : public CoefficientSpectrum<nSpectralSamples> {
	public:
		SampledSpectrum(float v = 0.f) : CoefficientSpectrum(v) {}

		SampledSpectrum(const CoefficientSpectrum<nSpectralSamples>& v) :
			CoefficientSpectrum<nSpectralSamples>(v) {};

		SampledSpectrum(const RGBSpectrum& r, SpectrumType t);

		static SampledSpectrum FromSampled(const float* lambda, const float* v, int n)
		{
			if (!SpectrumSamplesSorted(lambda, v, n)) {
				std::vector<float> slambda(&lambda[0], &lambda[n]);
				std::vector<float> sv(&v[0], &v[n]);
				SortSpectrumSamples(&slambda[0], &sv[0], n);
				return FromSampled(&slambda[0], &sv[0], n);
			}
			SampledSpectrum r;
			for (int i = 0; i < nSpectralSamples; ++i) {
				float lambda0 = Math::Lerp(float(i) / float(nSpectralSamples),
					sampledLambdaStart, sampledLambdaEnd);
				float lambda1 = Math::Lerp(float(i + 1) / float(nSpectralSamples),
					sampledLambdaStart, sampledLambdaEnd);
				r.c[i] = AverageSpectrumSamples(lambda, v, n, lambda0, lambda1);

			}
			return r;
		}

		void ToXYZ(float xyz[3]) const {
			xyz[0] = xyz[1] = xyz[2] = 0.f;
			for (int i = 0; i < nSpectralSamples; ++i) {
				xyz[0] += X.c[i] * c[i];
				xyz[1] += Y.c[i] * c[i];
				xyz[2] += Z.c[i] * c[i];
			}
			float scale = float(sampledLambdaEnd - sampledLambdaStart) /
				float(CIE_Y_integral * nSpectralSamples);
			xyz[0] *= scale;
			xyz[1] *= scale;
			xyz[2] *= scale;
		}

		void ToRGB(float rgb[3]) const {
			float xyz[3];
			ToXYZ(xyz);
			XYZToRGB(xyz, rgb);
		}

		float y() const {
			float yy = 0.f;
			for (int i = 0; i < nSpectralSamples; ++i)
				yy += Y.c[i] * c[i];
			return yy * float(sampledLambdaEnd - sampledLambdaStart) /
				float(nSpectralSamples);
		}

		static SampledSpectrum FromXYZ(const float xyz[3],
			SpectrumType type = SpectrumType::Reflectance) {
			float rgb[3];
			XYZToRGB(xyz, rgb);
			return FromRGB(rgb, type);
		}

		static SampledSpectrum FromRGB(const float rgb[3], SpectrumType type = SpectrumType::Illuminant) {
			SampledSpectrum r;
			if (type == SpectrumType::Reflectance) {
				// Convert reflectance spectrum to RGB
				if (rgb[0] <= rgb[1] && rgb[0] <= rgb[2]) {
					// Compute reflectance _SampledSpectrum_ with _rgb[0]_ as minimum
					r += rgb[0] * rgbRefl2SpectWhite;
					if (rgb[1] <= rgb[2]) {
						r += (rgb[1] - rgb[0]) * rgbRefl2SpectCyan;
						r += (rgb[2] - rgb[1]) * rgbRefl2SpectBlue;
					}
					else {
						r += (rgb[2] - rgb[0]) * rgbRefl2SpectCyan;
						r += (rgb[1] - rgb[2]) * rgbRefl2SpectGreen;
					}
				}
				else if (rgb[1] <= rgb[0] && rgb[1] <= rgb[2]) {
					// Compute reflectance _SampledSpectrum_ with _rgb[1]_ as minimum
					r += rgb[1] * rgbRefl2SpectWhite;
					if (rgb[0] <= rgb[2]) {
						r += (rgb[0] - rgb[1]) * rgbRefl2SpectMagenta;
						r += (rgb[2] - rgb[0]) * rgbRefl2SpectBlue;
					}
					else {
						r += (rgb[2] - rgb[1]) * rgbRefl2SpectMagenta;
						r += (rgb[0] - rgb[2]) * rgbRefl2SpectRed;
					}
				}
				else {
					// Compute reflectance _SampledSpectrum_ with _rgb[2]_ as minimum
					r += rgb[2] * rgbRefl2SpectWhite;
					if (rgb[0] <= rgb[1]) {
						r += (rgb[0] - rgb[2]) * rgbRefl2SpectYellow;
						r += (rgb[1] - rgb[0]) * rgbRefl2SpectGreen;
					}
					else {
						r += (rgb[1] - rgb[2]) * rgbRefl2SpectYellow;
						r += (rgb[0] - rgb[1]) * rgbRefl2SpectRed;
					}
				}
				r *= .94;
			}
			else {
				// Convert illuminant spectrum to RGB
				if (rgb[0] <= rgb[1] && rgb[0] <= rgb[2]) {
					// Compute illuminant _SampledSpectrum_ with _rgb[0]_ as minimum
					r += rgb[0] * rgbIllum2SpectWhite;
					if (rgb[1] <= rgb[2]) {
						r += (rgb[1] - rgb[0]) * rgbIllum2SpectCyan;
						r += (rgb[2] - rgb[1]) * rgbIllum2SpectBlue;
					}
					else {
						r += (rgb[2] - rgb[0]) * rgbIllum2SpectCyan;
						r += (rgb[1] - rgb[2]) * rgbIllum2SpectGreen;
					}
				}
				else if (rgb[1] <= rgb[0] && rgb[1] <= rgb[2]) {
					// Compute illuminant _SampledSpectrum_ with _rgb[1]_ as minimum
					r += rgb[1] * rgbIllum2SpectWhite;
					if (rgb[0] <= rgb[2]) {
						r += (rgb[0] - rgb[1]) * rgbIllum2SpectMagenta;
						r += (rgb[2] - rgb[0]) * rgbIllum2SpectBlue;
					}
					else {
						r += (rgb[2] - rgb[1]) * rgbIllum2SpectMagenta;
						r += (rgb[0] - rgb[2]) * rgbIllum2SpectRed;
					}
				}
				else {
					// Compute illuminant _SampledSpectrum_ with _rgb[2]_ as minimum
					r += rgb[2] * rgbIllum2SpectWhite;
					if (rgb[0] <= rgb[1]) {
						r += (rgb[0] - rgb[2]) * rgbIllum2SpectYellow;
						r += (rgb[1] - rgb[0]) * rgbIllum2SpectGreen;
					}
					else {
						r += (rgb[1] - rgb[2]) * rgbIllum2SpectYellow;
						r += (rgb[0] - rgb[1]) * rgbIllum2SpectRed;
					}
				}
				r *= .86445f;
			}
			return r.Clamp();
		}

		static void init() {
			// precompute spectrum data
			// XYZ
			for (int i = 0; i < nSpectralSamples; i++) {
				float wl0 = Math::Lerp(float(i) / float(nSpectralSamples),
					sampledLambdaStart, sampledLambdaEnd);
				float wl1 = Math::Lerp(float(i + 1) / float(nSpectralSamples),
					sampledLambdaStart, sampledLambdaEnd);
				X.c[i] = AverageSpectrumSamples(CIE_lambda, CIE_X, nCIESamples,
					wl0, wl1);
				Y.c[i] = AverageSpectrumSamples(CIE_lambda, CIE_Y, nCIESamples,
					wl0, wl1);
				Z.c[i] = AverageSpectrumSamples(CIE_lambda, CIE_Z, nCIESamples,
					wl0, wl1);
			}

			// Init RGB conversion SPDs
			for (int i = 0; i < nSpectralSamples; ++i) {
				float wl0 = Math::Lerp(float(i) / float(nSpectralSamples),
					sampledLambdaStart, sampledLambdaEnd);
				float wl1 = Math::Lerp(float(i + 1) / float(nSpectralSamples),
					sampledLambdaStart, sampledLambdaEnd);
				rgbRefl2SpectWhite.c[i] = AverageSpectrumSamples(RGB2SpectLambda, RGBRefl2SpectWhite,
					nRGB2SpectSamples, wl0, wl1);
				rgbRefl2SpectCyan.c[i] = AverageSpectrumSamples(RGB2SpectLambda, RGBRefl2SpectCyan,
					nRGB2SpectSamples, wl0, wl1);
				rgbRefl2SpectMagenta.c[i] = AverageSpectrumSamples(RGB2SpectLambda, RGBRefl2SpectMagenta,
					nRGB2SpectSamples, wl0, wl1);
				rgbRefl2SpectYellow.c[i] = AverageSpectrumSamples(RGB2SpectLambda, RGBRefl2SpectYellow,
					nRGB2SpectSamples, wl0, wl1);
				rgbRefl2SpectRed.c[i] = AverageSpectrumSamples(RGB2SpectLambda, RGBRefl2SpectRed,
					nRGB2SpectSamples, wl0, wl1);
				rgbRefl2SpectGreen.c[i] = AverageSpectrumSamples(RGB2SpectLambda, RGBRefl2SpectGreen,
					nRGB2SpectSamples, wl0, wl1);
				rgbRefl2SpectBlue.c[i] = AverageSpectrumSamples(RGB2SpectLambda, RGBRefl2SpectBlue,
					nRGB2SpectSamples, wl0, wl1);

				rgbIllum2SpectWhite.c[i] = AverageSpectrumSamples(RGB2SpectLambda, RGBIllum2SpectWhite,
					nRGB2SpectSamples, wl0, wl1);
				rgbIllum2SpectCyan.c[i] = AverageSpectrumSamples(RGB2SpectLambda, RGBIllum2SpectCyan,
					nRGB2SpectSamples, wl0, wl1);
				rgbIllum2SpectMagenta.c[i] = AverageSpectrumSamples(RGB2SpectLambda, RGBIllum2SpectMagenta,
					nRGB2SpectSamples, wl0, wl1);
				rgbIllum2SpectYellow.c[i] = AverageSpectrumSamples(RGB2SpectLambda, RGBIllum2SpectYellow,
					nRGB2SpectSamples, wl0, wl1);
				rgbIllum2SpectRed.c[i] = AverageSpectrumSamples(RGB2SpectLambda, RGBIllum2SpectRed,
					nRGB2SpectSamples, wl0, wl1);
				rgbIllum2SpectGreen.c[i] = AverageSpectrumSamples(RGB2SpectLambda, RGBIllum2SpectGreen,
					nRGB2SpectSamples, wl0, wl1);
				rgbIllum2SpectBlue.c[i] = AverageSpectrumSamples(RGB2SpectLambda, RGBIllum2SpectBlue,
					nRGB2SpectSamples, wl0, wl1);
			}
		}

	private:
		static SampledSpectrum X, Y, Z;
		static SampledSpectrum rgbRefl2SpectWhite, rgbRefl2SpectCyan,
			rgbRefl2SpectMagenta, rgbRefl2SpectYellow,
			rgbRefl2SpectRed, rgbRefl2SpectGreen,
			rgbRefl2SpectBlue;
		static SampledSpectrum rgbIllum2SpectWhite, rgbIllum2SpectCyan,
			rgbIllum2SpectMagenta, rgbIllum2SpectYellow,
			rgbIllum2SpectRed, rgbIllum2SpectGreen,
			rgbIllum2SpectBlue;
	};

}