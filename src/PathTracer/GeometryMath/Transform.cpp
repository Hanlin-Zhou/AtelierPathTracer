#include "Transform.hpp"

namespace APT {
	Transform::Transform()
	{
		m = Mat4();
		mInv = Mat4();
	}

	Transform::Transform(const float mat[4][4])
	{
		m = Mat4(mat);
		mInv = Mat4::Inverse(m);
	}

	Transform::Transform(const Mat4& _m)
	{
		m = _m;
		mInv = Mat4::Inverse(m);
	}

	Transform::Transform(const Mat4& _m, const Mat4& _mInv)
	{
		m = _m;
		mInv = _mInv;
	}

	const Mat4 Transform::GetMat() const
	{
		return m;
	}

	const Mat4 Transform::GetMatInv() const
	{
		return mInv;
	}

	Transform Transform::Translate(const Vec3f& delta)
	{
		Mat4 m(1, 0, 0, delta.x,
			0, 1, 0, delta.y,
			0, 0, 1, delta.z,
			0, 0, 0, 1);
		Mat4 minv(1, 0, 0, -delta.x,
			0, 1, 0, -delta.y,
			0, 0, 1, -delta.z,
			0, 0, 0, 1);
		return Transform(m, minv);
	}

	Transform Transform::Scale(const Vec3f& s)
	{
		Mat4 m(s.x, 0, 0, 0,
			0, s.y, 0, 0,
			0, 0, s.z, 0,
			0, 0, 0, 1);
		Mat4 minv(1 / s.x, 0, 0, 0,
			0, 1 / s.y, 0, 0,
			0, 0, 1 / s.z, 0,
			0, 0, 0, 1);
		return Transform(m, minv);
	}

	Transform Transform::Scale(float x, float y, float z)
	{
		Mat4 m(x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, z, 0,
			0, 0, 0, 1);
		Mat4 minv(1 / x, 0, 0, 0,
			0, 1 / y, 0, 0,
			0, 0, 1 / z, 0,
			0, 0, 0, 1);
		return Transform(m, minv);
	}

	Transform Transform::RotateAroundX(float theta)
	{
		float sinTheta = std::sin(ToRadian(theta));
		float cosTheta = std::cos(ToRadian(theta));
		Mat4 m(1, 0, 0, 0,
			0, cosTheta, -sinTheta, 0,
			0, sinTheta, cosTheta, 0,
			0, 0, 0, 1);
		return Transform(m, Mat4::Transpose(m));
	}

	Transform Transform::RotateAroundY(float theta)
	{
		float sinTheta = std::sin(ToRadian(theta));
		float cosTheta = std::cos(ToRadian(theta));
		Mat4 m(cosTheta, 0, sinTheta, 0,
			0, 1, 0, 0,
			-sinTheta, 0, cosTheta, 0,
			0, 0, 0, 1);
		return Transform(m, Mat4::Transpose(m));
	}

	Transform Transform::RotateAroundZ(float theta)
	{
		float sinTheta = std::sin(ToRadian(theta));
		float cosTheta = std::cos(ToRadian(theta));
		Mat4 m(cosTheta, -sinTheta, 0, 0,
			sinTheta, cosTheta, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
		return Transform(m, Mat4::Transpose(m));
	}

	Transform Transform::RotateAround(const Vec3f& axis, float theta)
	{
		Vec3f a = Normalize(axis);
		float sinTheta = std::sin(ToRadian(theta));
		float cosTheta = std::cos(ToRadian(theta));
		Mat4 m;
		m.m[0][0] = a.x * a.x + (1 - a.x * a.x) * cosTheta;
		m.m[0][1] = a.x * a.y * (1 - cosTheta) - a.z * sinTheta;
		m.m[0][2] = a.x * a.z * (1 - cosTheta) + a.y * sinTheta;
		m.m[0][3] = 0;
		m.m[1][0] = a.x * a.y * (1 - cosTheta) + a.z * sinTheta;
		m.m[1][1] = a.y * a.y + (1 - a.y * a.y) * cosTheta;
		m.m[1][2] = a.y * a.z * (1 - cosTheta) - a.x * sinTheta;
		m.m[1][3] = 0;
		m.m[2][0] = a.x * a.z * (1 - cosTheta) - a.y * sinTheta;
		m.m[2][1] = a.y * a.z * (1 - cosTheta) + a.x * sinTheta;
		m.m[2][2] = a.z * a.z + (1 - a.z * a.z) * cosTheta;
		m.m[2][3] = 0;
		return Transform(m, Mat4::Transpose(m));
	}

	Transform Transform::Rotate(float Xtheta, float Ytheta, float Ztheta)
	{
		// TODO
		Transform t;
		if (Xtheta != 0.f) {
			t = t * RotateAroundX(Xtheta);
		}
		if (Ytheta != 0.f) {
			t = t * RotateAroundY(Ytheta);
		}
		if (Ztheta != 0.f) {
			t = t * RotateAroundZ(Ztheta);
		}
		return t;
	}

	Transform Transform::Rotate(const Vec3f& theta)
	{
		return Rotate(theta.x, theta.y, theta.z);
	}

	Transform Transform::LookAt(const Vec3f& position, const Vec3f& target, const Vec3f& up)
	{
		Mat4 cameraToWorld;
		Mat4 worldToCam;
		Vec3f dir = Normalize(target - position);
		Vec3f right = Normalize(Cross(Normalize(up), dir));
		Vec3f newUp = Cross(dir, right);

		cameraToWorld.m[0][3] = position.x;
		cameraToWorld.m[1][3] = position.y;
		cameraToWorld.m[2][3] = position.z;
		cameraToWorld.m[3][3] = 1;
		cameraToWorld.m[0][0] = right.x;
		cameraToWorld.m[1][0] = right.y;
		cameraToWorld.m[2][0] = right.z;
		cameraToWorld.m[3][0] = 0.;
		cameraToWorld.m[0][1] = newUp.x;
		cameraToWorld.m[1][1] = newUp.y;
		cameraToWorld.m[2][1] = newUp.z;
		cameraToWorld.m[3][1] = 0.;
		cameraToWorld.m[0][2] = dir.x;
		cameraToWorld.m[1][2] = dir.y;
		cameraToWorld.m[2][2] = dir.z;
		cameraToWorld.m[3][2] = 0.;

		worldToCam.m[0][3] = -position.x;
		worldToCam.m[1][3] = -position.y;
		worldToCam.m[2][3] = -position.z;
		worldToCam.m[3][3] = 1;
		worldToCam.m[0][0] = right.x;
		worldToCam.m[1][0] = newUp.x;
		worldToCam.m[2][0] = dir.x;
		worldToCam.m[3][0] = 0.;
		worldToCam.m[0][1] = right.y;
		worldToCam.m[1][1] = newUp.y;
		worldToCam.m[2][1] = dir.y;
		worldToCam.m[3][1] = 0.;
		worldToCam.m[0][2] = right.z;
		worldToCam.m[1][2] = newUp.y;
		worldToCam.m[2][2] = dir.z;
		worldToCam.m[3][2] = 0.;
		
		return Transform(worldToCam, cameraToWorld);
	}

	Transform Transform::Perspective(float fov, float n, float f)
	{
		Mat4 persp(1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, f / (f - n), -f * n / (f - n),
			0, 0, 1, 0);
		float ita = 1.0 / std::tan(ToRadian(fov) / 2.0);
		return Scale(ita, ita, 1) * Transform(persp);
	}

	Transform Transform::Inverse(const Transform& t)
	{
		return Transform(t.mInv, t.m);
	}

	Transform Transform::Transpose(const Transform& t)
	{
		return Transform(Mat4::Transpose(t.m), Mat4::Transpose(t.mInv));
	}

	Transform Transform::operator*(const Transform& t2) const {
		return Transform(Mat4::Mul(m, t2.m),
			Mat4::Mul(t2.mInv, mInv));
	}

	Transform& Transform::operator*=(const Transform& t2) 
	{
		m = Mat4::Mul(m, t2.m);
		mInv = Mat4::Mul(t2.mInv, mInv);
		return *this;
	}

	/*template<typename T>
	Vec3<T> Transform::operator()(const Vec3<T>& v) const
	{
		T x = v.x, y = v.y, z = v.z;
		return Vec3<T>(m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z,
			m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z,
			m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z);
	}*/

}