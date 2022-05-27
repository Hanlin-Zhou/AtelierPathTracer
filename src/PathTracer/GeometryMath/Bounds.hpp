#pragma once
#include "Vector.hpp"
#include "MathHelper.hpp"
#include <PathTracer/Ray/Ray.hpp>

namespace Math {
	template <typename T> class Bounds2 {
	public:
		Bounds2() {
			T minNum = std::numeric_limits<T>::lowest();
			T maxNum = std::numeric_limits<T>::max();
			pMin = Vec2<T>(maxNum, maxNum);
			pMax = Vec2<T>(minNum, minNum);
		}

		Bounds2(const Vec2<T>& p) : pMin(p), pMax(p) {}

		Bounds2(const Vec2<T>& p1, const Vec2<T>& p2) {
			pMin = Vec2<T>(std::min(p1.x, p2.x), std::min(p1.y, p2.y));
			pMax = Vec2<T>(std::max(p1.x, p2.x), std::max(p1.y, p2.y));
		}

		Vec2<T> Diagonal() const {
			return pMax - pMin;
		}

		T Area() const {
			Vec2<T> d = pMax - pMin;
			return (d.x * d.y);
		}

		int MaximumExtent() const {
			Vec2<T> diag = Diagonal();
			if (diag.x > diag.y)
				return 0;
			else
				return 1;
		}

		const Vec2<T>& operator[](int i) const {
			assert(i == 0 || i == 1);
			return (i == 0) ? pMin : pMax;
		}

		Vec2<T>& operator[](int i) {
			assert(i == 0 || i == 1);
			return (i == 0) ? pMin : pMax;
		}

		bool operator==(const Bounds2<T>& b) const {
			return b.pMin == pMin && b.pMax == pMax;
		}

		Vec2<T> Lerp(const Vec2f& t) const {
			return Vec2<T>(Math::Lerp(t.x, pMin.x, pMax.x), Math::Lerp(t.y, pMin.y, pMax.y));
		}

		Vec2<T> Offset(const Vec2<T>& p) const {
			Vec2<T> o = p - pMin;
			if (pMax.x > pMin.x) o.x /= pMax.x - pMin.x;
			if (pMax.y > pMin.y) o.y /= pMax.y - pMin.y;
			return o;
		}

		// Members
		Vec2<T> pMin;
		Vec2<T> pMax;
	};
	

	template <typename T> class Bounds3 {
	public:
		Bounds3() {
			T minNum = std::numeric_limits<T>::lowest();
			T maxNum = std::numeric_limits<T>::max();
			pMin = Vec3<T>(maxNum, maxNum, maxNum);
			pMax = Vec3<T>(minNum, minNum, minNum);
		}

		Bounds3(const Vec3<T>& p) : pMin(p), pMax(p) {}

		Bounds3(const Vec3<T>& p1, const Vec3<T>& p2) :
			pMin(std::min(p1.x, p2.x), std::min(p1.y, p2.y),
				std::min(p1.z, p2.z)),
			pMax(std::max(p1.x, p2.x), std::max(p1.y, p2.y),
				std::max(p1.z, p2.z)) {}

		Vec3<T> Diagonal() const {
			return pMax - pMin;
		}

		T SurfaceArea() const {
			Vec3<T> d = Diagonal();
			return 2 * (d.x * d.y + d.x * d.z + d.y * d.z);
		}

		T Volume() const {
			Vec3<T> d = Diagonal();
			return d.x * d.y * d.z;
		}

		int MaximumExtent() const {
			Vec3<T> d = Diagonal();
			if (d.x > d.y && d.x > d.z)
				return 0;
			else if (d.y > d.z)
				return 1;
			else
				return 2;
		}

		const Vec3<T>& operator[](int i) const {
			assert(i == 0 || i == 1);
			return (i == 0) ? pMin : pMax;
		}

		Vec3<T>& operator[](int i) {
			assert(i == 0 || i == 1);
			return (i == 0) ? pMin : pMax;
		}

		bool operator==(const Bounds3<T>& b) const {
			return b.pMin == pMin && b.pMax == pMax;
		}

		Vec3<T> Lerp(const Vec3f& t) const {
			return Vec3<T>(Math::Lerp(t.x, pMin.x, pMax.x),
				Math::Lerp(t.y, pMin.y, pMax.y),
				Math::Lerp(t.z, pMin.z, pMax.z));
		}

		Vec3<T> Offset(const Vec3<T>& p) const {
			Vec3<T> o = p - pMin;
			if (pMax.x > pMin.x) o.x /= pMax.x - pMin.x;
			if (pMax.y > pMin.y) o.y /= pMax.y - pMin.y;
			if (pMax.z > pMin.z) o.z /= pMax.z - pMin.z;
			return o;
		}

		inline bool IntersectP(const APT::Ray& ray, float* hitt0 = nullptr, float* hitt1 = nullptr) const;

		inline bool IntersectP(const APT::Ray& ray, const Vec3f& inv, const int negative[3]) const;
		// Members
		Vec3<T> pMin;
		Vec3<T> pMax;
	};
	
	template <typename T>
	inline bool Bounds3<T>::IntersectP(const APT::Ray& ray, float* hitt0, float* hitt1) const {
		float t0 = 0.0, t1 = ray.mMaxTime;
		for (int i = 0; i < 3; i++)
		{
			float inv = 1.0 / ray.d[i];
			float tNear = (pMin[i] - ray.o[i]) * inv;
			float tFar = (pMax[i] - ray.o[i]) * inv;
			if (tNear > tFar) std::swap(tNear, tFar);
			t0 = tNear > t0 ? tNear : t0;
			t1 = tFar < t1 ? tFar : t1;
			if (t0 > t1) return false;
		}
		if (hitt0) *hitt0 = t0;
		if (hitt1) *hitt1 = t1;
		return true;
	}

	/*template<typename T>
	inline bool Bounds3<T>::IntersectP(const APT::Ray& ray, const Vec3f& inv, const int negative[3]) const
	{
		const Bounds3f& bounds = *this;
		float txMin = (bounds[negative[0]].x - ray.o.x) * inv.x;
		float txMax = (bounds[1 - negative[0]].x - ray.o.x) * inv.x;
		float tyMin = (bounds[negative[1]].y - ray.o.y) * inv.y;
		float tyMax = (bounds[1 - negative[1]].y - ray.o.y) * inv.y;
		if (txMin > tyMax || tyMin > txMax)
			return false;
		if (tyMin > tMin) tMin = tyMin;
		if (tyMax < tMax) tMax = tyMax;

		float tzMin = (bounds[negative[2]].z - ray.o.z) * inv.z;
		float tzMax = (bounds[1 - negative[2]].z - ray.o.z) * inv.z;
		if (txMin > tzMax || tzMin > txMax)
			return false;
		if (tzMin > txMin)
			txMin = tzMin;
		if (tzMax < tMax)
			txMax = tzMax;

		return (txMin < ray.tMax) && (txMax > 0);
	}*/


	typedef Bounds2<float> Bounds2f;
	typedef Bounds2<int>   Bounds2i;
	typedef Bounds3<float> Bounds3f;
	typedef Bounds3<int>   Bounds3i;
}