#include "PerspectiveCamera.hpp"

namespace APT {
	PerspectiveCamera::PerspectiveCamera():
		ProjectiveCamera(Vec3f(0.f, 0.f, -10.f), Vec3f(0.f, 0.f, 0.f), Vec3f(0.f, 1.f, 0.f), Transform::Perspective(45.f, 0.1f, 100.f), Bounds2f(), 0.f, 0.f, nullptr, nullptr, CameraType::Perspective, 0.f, 0.f)
	{
		mFov = 45.f;
		mNear = 0.1f;
		mFar = 100.f;
	}
	PerspectiveCamera::PerspectiveCamera(Vec3f position, Vec3f target, Vec3f up, const Bounds2f& screenBounds, float open, float close, Film* film, const Medium* medium, float lenRadius, float focalDist, float fov, float n, float f):
		ProjectiveCamera(position, target, up, Transform::Perspective(fov, n, f), screenBounds, open, close, film, medium, CameraType::Perspective, lenRadius, focalDist)
	{
		mFov = fov;
		mNear = n;
		mFar = f;
	}
	float PerspectiveCamera::GetFov() const
	{
		return mFov;
	}
	float PerspectiveCamera::GetNear() const
	{
		return mNear;
	}
	float PerspectiveCamera::GetFar() const
	{
		return mFar;
	}
}