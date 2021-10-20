#include "Camera.hpp"
namespace APT {
	// Camera::Camera() :Camera(Vec3f(0, 0, -10), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 0, 0, nullptr, nullptr) {}

	Camera::Camera(Vec3f position, Vec3f target, Vec3f up, float open, float close, Film* film, const Medium* medium, CameraType type):
		mPostion(position), mTarget(target), mUp(up), mShutterOpen(open), mShutterClose(close), mFilm(film), mMedium(medium), mType(type)
	{
		mWorldToCam = Transform::LookAt(mPostion, mTarget, mUp);
	}
	Vec3f Camera::GetPosition() const
	{
		return mPostion;
	}
	Vec3f Camera::GetTarget() const
	{
		return mTarget;
	}
	Vec3f Camera::GetUp() const
	{
		return mUp;
	}
	CameraType Camera::GetType() const
	{
		return mType;
	}
}