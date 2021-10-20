#include "ProjectiveCamera.hpp"
namespace APT {
	ProjectiveCamera::ProjectiveCamera(Vec3f position, Vec3f target, Vec3f up, Transform camToScreen, const Bounds2f& screenBounds, float open, float close, Film* film, const Medium* medium, CameraType type, float lenRadius, float focalDist):
		Camera(position, target, up, open, close, film, medium, type)
	{
		mLensRadius = lenRadius;
		mFocalDist = focalDist;
		mCamToScreen = camToScreen;
	}
}