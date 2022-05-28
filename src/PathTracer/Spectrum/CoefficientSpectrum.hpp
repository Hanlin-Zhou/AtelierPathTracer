#pragma once
#include <limits>
#include <cmath>
#include <PathTracer/GeometryMath/MathHelper.hpp>

namespace APT {
	template <int nSamples> class CoefficientSpectrum {
	public:
		CoefficientSpectrum(float v = 0.f) {
			for (int i = 0; i < nSamples; ++i) 
			{
				c[i] = v;
			}
		}


		CoefficientSpectrum& operator=(const CoefficientSpectrum& s) {
			if (this == &s) {
				return *this;
			}
			for (int i = 0; i < nSamples; ++i)
			{
				c[i] = s.c[i];
			}
		}

		CoefficientSpectrum& operator+=(const CoefficientSpectrum& s) {
			for (int i = 0; i < nSamples; ++i)
			{
				c[i] += s.c[i];
			}
			return *this;
		}


		CoefficientSpectrum& operator-=(const CoefficientSpectrum& s) {
			for (int i = 0; i < nSamples; ++i)
			{
				c[i] -= s.c[i];
			}
			return *this;
		}


		CoefficientSpectrum& operator*=(const CoefficientSpectrum& s) {
			for (int i = 0; i < nSamples; ++i)
			{
				c[i] *= s.c[i];
			}
			return *this;
		}


		CoefficientSpectrum& operator/=(const CoefficientSpectrum& s) {
			for (int i = 0; i < nSamples; ++i)
			{
				c[i] /= s.c[i];
			}
			return *this;
		}


		CoefficientSpectrum operator+(const CoefficientSpectrum& s) const{
			CoefficientSpectrum result = *this;
			for (int i = 0; i < nSamples; ++i)
			{
				result.c[i] += s.c[i];
			}
			return result;
		}


		CoefficientSpectrum operator-(const CoefficientSpectrum& s) const{
			CoefficientSpectrum result = *this;
			for (int i = 0; i < nSamples; ++i)
			{
				result.c[i] -= s.c[i];
			}
			return result;
		}


		CoefficientSpectrum operator*(const CoefficientSpectrum& s) const{
			CoefficientSpectrum result = *this;
			for (int i = 0; i < nSamples; ++i)
			{
				result.c[i] *= s.c[i];
			}
			return result;
		}


		CoefficientSpectrum operator/(const CoefficientSpectrum& s) const{
			CoefficientSpectrum result = *this;
			for (int i = 0; i < nSamples; ++i)
			{
				result.c[i] /= s.c[i];
			}
			return result;
		}


		CoefficientSpectrum operator*(float f) const{
			CoefficientSpectrum result = *this;
			for (int i = 0; i < nSamples; ++i)
			{
				result.c[i] *= f;
			}
			return result;
		}


		CoefficientSpectrum& operator*=(float f) {
			for (int i = 0; i < nSamples; ++i)
			{
				c[i] *= f;
			}
			return *this;
		}


		CoefficientSpectrum operator/(float f) const{
			CoefficientSpectrum result = *this;
			for (int i = 0; i < nSamples; ++i)
			{
				result.c[i] /= f;
			}
			return result;
		}


		bool operator==(const CoefficientSpectrum& s) const {
			for (int i = 0; i < nSamples; ++i)
			{
				if (c[i] != s.c[i]) {
					return false;
				}
			}
			return true;
		}


		bool operator!=(const CoefficientSpectrum& s) const {
			return !(*this == s);
		}


		bool IsBlack() const{
			for (int i = 0; i < nSamples; ++i)
			{
				if (c[i] != 0.0) {
					return false;
				}
			}
			return true;
		}


		friend CoefficientSpectrum Sqrt(const CoefficientSpectrum& s) {
			CoefficientSpectrum result;
			for (int i = 0; i < nSamples; ++i)
				result.c[i] = std::sqrt(s.c[i]);
			return result;
		}

		friend inline CoefficientSpectrum operator*(float a, const CoefficientSpectrum& s) {
			return s * a;
		}

		CoefficientSpectrum Clamp(float low = 0, float high = std::numeric_limits<float>::max()) const {
			CoefficientSpectrum result;
			for (int i = 0; i < nSamples; ++i)
				result.c[i] = Math::Clamp(c[i], low, high);
			return result;
		}

		static const int Sample = nSamples;
		float& operator[](int i) {
			return c[i];
		}
	protected:
		float c[nSamples];
	};
}