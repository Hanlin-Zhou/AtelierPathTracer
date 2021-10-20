#pragma once
#include <PathTracer/GeometryMath/Transform.hpp>
#include <PathTracer/Camera/Film.hpp>
#include <PathTracer/Camera/CameraType.hpp>
#include <PathTracer/Media/Medium.hpp>


namespace APT {
	class Camera {
	public:
		// Camera();
		Camera(Vec3f position, Vec3f target, Vec3f up, float open, float close, Film *film, const Medium * medium, CameraType type);

		Vec3f GetPosition() const;
		Vec3f GetTarget() const;
		Vec3f GetUp() const;
		CameraType GetType() const;
		
	protected:
		Transform mWorldToCam;
		Vec3f mPostion;
		Vec3f mTarget;
		Vec3f mUp;
		const float mShutterOpen;
		const float mShutterClose;
		Film* mFilm;
		const Medium* mMedium;
		CameraType mType;
	};

}