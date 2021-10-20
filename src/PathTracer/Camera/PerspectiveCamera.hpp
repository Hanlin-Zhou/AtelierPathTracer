#pragma once
#include <PathTracer/Camera/ProjectiveCamera.hpp>

namespace APT {
	class PerspectiveCamera : public ProjectiveCamera {
	public:
		PerspectiveCamera();
		PerspectiveCamera(Vec3f position, Vec3f target, Vec3f up, const Bounds2f& screenBounds, float open, float close, Film* film, const Medium* medium, float lenRadius, float focalDist, float fov, float n, float f);
		float GetFov() const;
		float GetNear() const;
		float GetFar() const;
	protected:
		float mFov;
		float mNear;
		float mFar;
	};

}