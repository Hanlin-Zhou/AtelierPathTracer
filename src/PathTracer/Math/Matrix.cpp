#include "Matrix.hpp"

namespace Math {
	Mat4::Mat4() {
		m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
		m[0][1] = m[0][2] = m[0][3] = 
		m[1][0] = m[1][2] = m[1][3] = 
		m[2][0] = m[2][1] = m[2][3] =
		m[3][0] = m[3][1] = m[3][2] = 0.f;
	}

	Mat4::Mat4(float mat[4][4]) {
		
	}
}