#include "Triangle.hpp"
#pragma once

namespace APT {
	Triangle::Triangle(const Transform* objectToWorld, const Transform* worldToObject, bool reverse, const std::shared_ptr<TriangleMesh>& mesh, int num) :
		Shape(objectToWorld, worldToObject, reverse), mMesh(mesh)
	{
		mIndex = &mMesh->mVertexIndices[3 * num];
	}

	Bounds3f Triangle::ObjectBound() const
	{
		const Vec3f& p0 = mMesh->mVertex[mIndex[0]];
		const Vec3f& p1 = mMesh->mVertex[mIndex[1]];
		const Vec3f& p2 = mMesh->mVertex[mIndex[2]];

		return Union(Bounds3f((*mWorldToObject).TransformPoint(p0), (*mWorldToObject).TransformPoint(p1)),
			(*mWorldToObject).TransformPoint(p2));
	}

	Bounds3f Triangle::WorldBound() const
	{
		const Vec3f& p0 = mMesh->mVertex[mIndex[0]];
		const Vec3f& p1 = mMesh->mVertex[mIndex[1]];
		const Vec3f& p2 = mMesh->mVertex[mIndex[2]];
		return Union(Bounds3f(p0, p1), p2);
	}

	bool Triangle::Intersect(const Ray& ray, float* tHit, SurfaceInteraction* isect, bool testAlphaTexture) const
	{
		const Vec3f& p0 = mMesh->mVertex[mIndex[0]];
		const Vec3f& p1 = mMesh->mVertex[mIndex[1]];
		const Vec3f& p2 = mMesh->mVertex[mIndex[2]];
		// Translation
		Vec3f p0t = p0 - Vec3f(ray.o);
		Vec3f p1t = p1 - Vec3f(ray.o);
		Vec3f p2t = p2 - Vec3f(ray.o);
		// map largest direction to z
		int kz = MaxDimension(Abs(ray.d));
		int kx = kz + 1; if (kx == 3) kx = 0;
		int ky = kx + 1; if (ky == 3) ky = 0;
		Vec3f d = Permute(ray.d, kx, ky, kz);
		p0t = Permute(p0t, kx, ky, kz);
		p1t = Permute(p1t, kx, ky, kz);
		p2t = Permute(p2t, kx, ky, kz);
		// align ray direction with z axis
		float Sx = -d.x / d.z;
		float Sy = -d.y / d.z;
		float Sz = 1.f / d.z;
		p0t.x += Sx * p0t.z;
		p0t.y += Sy * p0t.z;
		p1t.x += Sx * p1t.z;
		p1t.y += Sy * p1t.z;
		p2t.x += Sx * p2t.z;
		p2t.y += Sy * p2t.z;
		// cross product side check
		float e0 = p1t.x * p2t.y - p1t.y * p2t.x;
		float e1 = p2t.x * p0t.y - p2t.y * p0t.x;
		float e2 = p0t.x * p1t.y - p0t.y * p1t.x;
		if ((e0 < 0 || e1 < 0 || e2 < 0) && (e0 > 0 || e1 > 0 || e2 > 0))
			return false;
		// hit on edge
		float det = e0 + e1 + e2;
		if (det == 0)
			return false;
		// barycentric test
		p0t.z *= Sz;
		p1t.z *= Sz;
		p2t.z *= Sz;
		float tScaled = e0 * p0t.z + e1 * p1t.z + e2 * p2t.z;
		if (det < 0 && (tScaled >= 0 || tScaled < ray.mMaxTime * det))
			return false;
		else if (det > 0 && (tScaled <= 0 || tScaled > ray.mMaxTime * det))
			return false;
		// barycentric compute 
		float invDet = 1 / det;
		float b0 = e0 * invDet;
		float b1 = e1 * invDet;
		float b2 = e2 * invDet;
		float t = tScaled * invDet;
		// uv 
		Vec3f dpdu, dpdv;
		Vec2f uv[3];
		GetUVs(uv);
		Vec2f duv02 = uv[0] - uv[2], duv12 = uv[1] - uv[2];
		Vec3f dp02 = p0 - p2, dp12 = p1 - p2;
		float determinant = duv02[0] * duv12[1] - duv02[1] * duv12[0];
		if (determinant == 0) {
			CoordinateSystem(Normalize(Cross(p2 - p0, p1 - p0)), &dpdu, &dpdv);
		}
		else {
			float invdet = 1 / determinant;
			dpdu = (duv12[1] * dp02 - duv02[1] * dp12) * invdet;
			dpdv = (-duv12[0] * dp02 + duv02[0] * dp12) * invdet;
		}
		// pError
		float xAbsSum = (std::abs(b0 * p0.x) + std::abs(b1 * p1.x) + std::abs(b2 * p2.x));
		float yAbsSum = (std::abs(b0 * p0.y) + std::abs(b1 * p1.y) + std::abs(b2 * p2.y));
		float zAbsSum = (std::abs(b0 * p0.z) + std::abs(b1 * p1.z) + std::abs(b2 * p2.z));
		Vec3f pError = gamma(7) * Vec3f(xAbsSum, yAbsSum, zAbsSum);
		// hit info
		Vec3f pHit = b0 * p0 + b1 * p1 + b2 * p2;
		Vec2f uvHit = b0 * uv[0] + b1 * uv[1] + b2 * uv[2];

		// interaction
		*isect = SurfaceInteraction(pHit, pError, uvHit, -ray.d, dpdu, dpdv, Vec3f(0, 0, 0), Vec3f(0, 0, 0), ray.mTime, this);

		// normal
		isect->mNormal = isect->mShading.mNormal = Vec3f(Normalize(Cross(dp02, dp12)));
		if (mMesh->mNormal)
			isect->mNormal = Faceforward(isect->mNormal, isect->mShading.mNormal);
		else if (mReverseOrientation ^ mSwapsHandedness)
			isect->mNormal = isect->mShading.mNormal = -isect->mNormal;

		// shading 
		// normal
		Vec3f normalv;
		if (mMesh->mNormal)
			normalv = Normalize(b0 * mMesh->mNormal[mIndex[0]] +
				b1 * mMesh->mNormal[mIndex[1]] +
				b2 * mMesh->mNormal[mIndex[2]]);
		else
			normalv = isect->mNormal;
		//tangent
		Vec3f tangentv;
		if (mMesh->mTangent)
			tangentv = Normalize(b0 * mMesh->mTangent[mIndex[0]] +
				b1 * mMesh->mTangent[mIndex[1]] +
				b2 * mMesh->mTangent[mIndex[2]]);
		else
			tangentv = Normalize(isect->mdPdU);
		//bitangent/tangent normalization
		Vec3f bitangentv = Cross(normalv, tangentv);
		if (bitangentv.LengthSquared() > 0.f) {
			bitangentv = Normalize(bitangentv);
			tangentv = Cross(bitangentv, normalv);
		}
		else
			CoordinateSystem((Vec3f)normalv, &tangentv, &bitangentv);
		// dndu and dndv
		Vec3f dndu, dndv;
		if (mMesh->mNormal) {
			Vec2f duv02 = uv[0] - uv[2];
			Vec2f duv12 = uv[1] - uv[2];
			Vec3f dn1 = mMesh->mNormal[mIndex[0]] - mMesh->mNormal[mIndex[2]];
			Vec3f dn2 = mMesh->mNormal[mIndex[1]] - mMesh->mNormal[mIndex[2]];
			float determinant = duv02[0] * duv12[1] - duv02[1] * duv12[0];
			if (determinant == 0)
				dndu = dndv = Vec3f(0, 0, 0);
			else {
				float invDet = 1 / determinant;
				dndu = (duv12[1] * dn1 - duv02[1] * dn2) * invDet;
				dndv = (-duv12[0] * dn1 + duv02[0] * dn2) * invDet;
			}
		}
		else
			dndu = dndv = Vec3f(0, 0, 0);

		isect->SetShadingGeometry(tangentv, bitangentv, dndu, dndv, true);
		*tHit = t;
		return true;
	}

	float Triangle::Area() const
	{
		const Vec3f& p0 = mMesh->mVertex[mIndex[0]];
		const Vec3f& p1 = mMesh->mVertex[mIndex[1]];
		const Vec3f& p2 = mMesh->mVertex[mIndex[2]];
		return 0.5 * Cross(p1 - p0, p2 - p0).Length();
	}

	void Triangle::GetUVs(Vec2f uv[3]) const {
		if (mMesh->mUV) {
			uv[0] = mMesh->mUV[mIndex[0]];
			uv[1] = mMesh->mUV[mIndex[1]];
			uv[2] = mMesh->mUV[mIndex[2]];
		}
		else {
			uv[0] = Vec2f(0, 0);
			uv[1] = Vec2f(1, 0);
			uv[2] = Vec2f(1, 1);
		}
	}
}
