#pragma once
#include<limits>
namespace Math {
	// constants
	/*float PI;
	float PI2;
	float DoverR;
	float RoverD;*/

	float ToRadian(float degree);
	float ToDegree(float radian);

	static constexpr float MachineEpsilon = std::numeric_limits<float>::epsilon() * 0.5;

	inline constexpr float gamma(int n) {
		return (n * MachineEpsilon) / (1 - n * MachineEpsilon);
	}

	float Lerp(float t, float v1, float v2);
	template <typename T, typename U, typename V>
	inline T Clamp(T val, U low, V high) {
		if (val < low) return low;
		else if (val > high) return high;
		else return val;
	}

	template <typename Predicate> int FindInterval(int size, const Predicate& pred) {
		int first = 0, len = size;
		while (len > 0) {
			int half = len >> 1, middle = first + half;
			if (pred(middle)) {
				first = middle + 1;
				len -= half + 1;
			}
			else
				len = half;
		}
		return Clamp(first - 1, 0, size - 2);
	}
}