#pragma once
#include "Matrix.hpp"
#include "MathHelper.hpp"
#include "Vector.hpp"

using namespace Math;

namespace APT {
	class Transform {
	public:
		Transform();
		Transform(const float mat[4][4]);
		Transform(const Mat4& _m);
		Transform(const Mat4& _m, const Mat4& _mInv);

		const Mat4 GetMat() const;
		const Mat4 GetMatInv() const;

		static Transform Translate(const Vec3f& delta);
		static Transform Scale(const Vec3f& delta);
		static Transform Scale(float x, float y, float z);
		static Transform RotateAroundX(float theta);
		static Transform RotateAroundY(float theta);
		static Transform RotateAroundZ(float theta);
		static Transform Rotate(float Xtheta, float Ytheta, float Ztheta);
		static Transform Rotate(const Vec3f& theta);

		static Transform LookAt(const Vec3f& position, const Vec3f& target, const Vec3f& up);
		static Transform Perspective(float fov, float n, float f);

		static Transform Inverse(const Transform& t);
		static Transform Transpose(const Transform& t);

		Transform operator*(const Transform& t2) const;

		template <typename T>
		Vec3<T> operator()(const Vec3<T>& v) const;

		// friend Transform Inverse(const Transform& t);
		// friend Transform Transpose(const Transform& t);
	private:
		Mat4 m;
		Mat4 mInv;
	};

	// Transform LookAt(const Vec3f& position, const Vec3f& target, const Vec3f& up);

	/*Transform Translate(const Vec3f& delta);
	Transform Scale(const Vec3f& delta);
	Transform Scale(float x, float y, float z);
	Transform RotateAroundX(float theta);
	Transform RotateAroundY(float theta);
	Transform RotateAroundZ(float theta);
	Transform Rotate(float Xtheta, float Ytheta, float Ztheta);
	Transform Rotate(const Vec3f& theta);

	Transform LookAt(const Vec3f& position, const Vec3f& target, const Vec3f& up);
	Transform Perspective(float fov, float n, float f);

	Transform Inverse(const Transform& t);
	Transform Transpose(const Transform& t);*/
}