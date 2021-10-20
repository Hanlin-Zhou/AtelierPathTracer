#include "Matrix.hpp"

namespace Math {
	Mat4::Mat4() {
		m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
		m[0][1] = m[0][2] = m[0][3] = 
		m[1][0] = m[1][2] = m[1][3] = 
		m[2][0] = m[2][1] = m[2][3] =
		m[3][0] = m[3][1] = m[3][2] = 0.f;
	}

	Mat4::Mat4(const float mat[4][4]) {
		m[0][0] = mat[0][0];
		m[0][1] = mat[0][1];
		m[0][2] = mat[0][2];
		m[0][3] = mat[0][3];
		m[1][0] = mat[1][0];
		m[1][1] = mat[1][1];
		m[1][2] = mat[1][2];
		m[1][3] = mat[1][3];
		m[2][0] = mat[2][0];
		m[2][1] = mat[2][1];
		m[2][2] = mat[2][2];
		m[2][3] = mat[2][3];
		m[3][0] = mat[3][0];
		m[3][1] = mat[3][1];
		m[3][2] = mat[3][2];
		m[3][3] = mat[3][3];
	}

	Mat4::Mat4(float t00, float t01, float t02, float t03, float t10, float t11, float t12, float t13, float t20, float t21, float t22, float t23, float t30, float t31, float t32, float t33)
	{
		m[0][0] = t00;
		m[0][1] = t01;
		m[0][2] = t02;
		m[0][3] = t03;
		m[1][0] = t10;
		m[1][1] = t11;
		m[1][2] = t12;
		m[1][3] = t13;
		m[2][0] = t20;
		m[2][1] = t21;
		m[2][2] = t21;
		m[2][3] = t22;
		m[3][0] = t30;
		m[3][1] = t31;
		m[3][2] = t32;
		m[3][3] = t33;
		m[0][0] = t00;
	}

	Mat4 Mat4::Mul(const Mat4& m1, const Mat4& m2)
	{
		Mat4 r;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				r.m[i][j] = m1.m[i][0] * m2.m[0][j] +
				m1.m[i][1] * m2.m[1][j] +
				m1.m[i][2] * m2.m[2][j] +
				m1.m[i][3] * m2.m[3][j];
		return r;
	}

	Mat4 Mat4::Transpose(const Mat4& m)
	{
		return Mat4(m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0],
			m.m[0][1], m.m[1][1], m.m[2][1], m.m[3][1],
			m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2],
			m.m[0][3], m.m[1][3], m.m[2][3], m.m[3][3]);
	}
	Mat4 Mat4::Inverse(const Mat4& m)
	{
		return m;
	}
}