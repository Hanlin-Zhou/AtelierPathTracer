#pragma once
#include  <PathTracer/Camera/Camera.hpp>
#include  <PathTracer/GeometryMath/Bounds.hpp>
namespace APT {
	class ProjectiveCamera : public Camera {
	public:
		ProjectiveCamera(Vec3f position, Vec3f target, Vec3f up, Transform camToScreen, const Bounds2f &screenBounds, float open, float close, Film* film, const Medium* medium, CameraType type, float lenRadius, float focalDist);
	protected:
		Transform mCamToScreen;
		Transform mScreenToRaster;
		float mLensRadius;
		float mFocalDist;

	};
}