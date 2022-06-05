#pragma once
#include "Matrix.hpp"
#include "MathHelper.hpp"
#include <PathTracer/GeometryMath/Bounds.hpp>

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
		bool SwapsHandedness() const;
		Vec3f TransformNormal(const Vec3f& n) const;
		Vec3f TransformPoint(const Vec3f& p) const;
		Vec3f TransformVector(const Vec3f& v) const;
		static Transform Translate(const Vec3f& delta);
		static Transform Scale(const Vec3f& delta);
		static Transform Scale(float x, float y, float z);
		static Transform RotateAroundX(float theta);
		static Transform RotateAroundY(float theta);
		static Transform RotateAroundZ(float theta);
		static Transform RotateAround(const Vec3f& axis, float theta);
		static Transform Rotate(float Xtheta, float Ytheta, float Ztheta);
		static Transform Rotate(const Vec3f& theta);

		static Transform LookAt(const Vec3f& position, const Vec3f& target, const Vec3f& up);
		static Transform Perspective(float fov, float n, float f);

		static Transform Inverse(const Transform& t);
		static Transform Transpose(const Transform& t);

		Transform operator*(const Transform& t2) const;
		Transform& operator*= (const Transform& t2) ;

		/*template <typename T>
		Vec3<T> operator()(const Vec3<T>& v) const {
			T x = v.x, y = v.y, z = v.z;
			return Vec3<T>(m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z,
				m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z,
				m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z);
		}*/

		Bounds3f operator()(const Bounds3f& b) const {
			const Transform& M = *this;
			Bounds3f ret(M(Vec3f(b.pMin.x, b.pMin.y, b.pMin.z)));
			ret = Union(ret, M(Vec3f(b.pMax.x, b.pMin.y, b.pMin.z)));
			ret = Union(ret, M(Vec3f(b.pMin.x, b.pMax.y, b.pMin.z)));
			ret = Union(ret, M(Vec3f(b.pMin.x, b.pMin.y, b.pMax.z)));
			ret = Union(ret, M(Vec3f(b.pMin.x, b.pMax.y, b.pMax.z)));
			ret = Union(ret, M(Vec3f(b.pMax.x, b.pMax.y, b.pMin.z)));
			ret = Union(ret, M(Vec3f(b.pMax.x, b.pMin.y, b.pMax.z)));
			ret = Union(ret, M(Vec3f(b.pMax.x, b.pMax.y, b.pMax.z)));
			return ret;
		}

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