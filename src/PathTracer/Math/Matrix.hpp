#pragma once
#include <cmath>
#include <cassert>
#include <iostream>
#include "Vector.hpp"

namespace Math {
	class Mat4 {
	public:
		Mat4();
		Mat4(float mat[4][4]);
		Mat4(float t00, float t01, float t02, float t03,
			float t10, float t11, float t12, float t13,
			float t20, float t21, float t22, float t23,
			float t30, float t31, float t32, float t33);


		// Member
		float m[4][4];
	};
}
