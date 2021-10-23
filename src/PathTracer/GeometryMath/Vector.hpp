#pragma once
#include <cmath>
#include <cassert>
#include <iostream>


namespace Math {
	template <typename T> class Vec2 {
	public:
		Vec2() { x = y = 0; }
		Vec2(T xx, T yy) : x(xx), y(yy)
		{
			// assert(!HasNaNs());
		}

		bool HasNaNs() const {
			return std::isnan(x) || std::isnan(y);
		}

		friend std::ostream& operator <<(std::ostream& os, const Vec2<T>& v) {
			os << "[" << v.x << ", " << v.y << "]";
			return os;
		}

		Vec2<T> operator+(const Vec2<T>& v) const {
			return Vec2(x + v.x, y + v.y);
		}

		Vec2<T>& operator+=(const Vec2<T>& v) {
			x += v.x; y += v.y;
			return *this;
		}
		Vec2<T> operator-(const Vec2<T>& v) const {
			return Vec2(x - v.x, y - v.y);
		}

		Vec2<T>& operator-=(const Vec2<T>& v) {
			x -= v.x; y -= v.y;
			return *this;
		}

		bool operator==(const Vec2<T>& v) const {
			return x == v.x && y == v.y;
		}

		bool operator!=(const Vec2<T>& v) const {
			return x != v.x || y != v.y;
		}

		Vec2<T> operator*(T f) const {
			return Vec2<T>(f * x, f * y);
		}

		Vec2<T>& operator*=(T f) {
			x *= f; y *= f;
			return *this;
		}

		Vec2<T> operator/(T f) const {
			float inv = (float)1 / f;
			return Vec2<T>(x * inv, y * inv);
		}

		Vec2<T>& operator/=(T f) {
			float inv = (float)1 / f;
			x *= inv; y *= inv;
			return *this;
		}

		Vec2<T> operator-() const {
			return Vec2<T>(-x, -y);
		}

		T operator[](int i) const {
			assert(i >= 0 && i <= 1);
			if (i == 0) return x;
			return y;
		}

		T& operator[](int i) {
			assert(i >= 0 && i <= 1);
			if (i == 0) return x;
			return y;
		}

		float Norm() const {
			return std::sqrt(x * x + y * y);
		}

		// Member
		T x;
		T y;
	};
	
	template <typename T> class Vec3 {
	public:
		Vec3() { x = y = z = 0; }

		Vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz)
		{
			assert(!HasNaNs());
		}

		bool HasNaNs() const {
			return std::isnan(x) || std::isnan(y) || std::isnan(z);
		}

		friend std::ostream& operator <<(std::ostream& os, const Vec3<T>& v) {
			os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
			return os;
		}

		Vec3<T> operator+(const Vec3<T>& v) const {
			return Vec3(x + v.x, y + v.y, z + v.z);
		}

		Vec3<T>& operator+=(const Vec3<T>& v) {
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}

		Vec3<T> operator-(const Vec3<T>& v) const {
			return Vec3<T>(x - v.x, y - v.y, z - v.z);
		}
		Vec3<T>& operator-=(const Vec3<T>& v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}

		bool operator==(const Vec3<T>& v) const {
			return x == v.x && y == v.y && z == v.z;
		}

		bool operator!=(const Vec3<T>& v) const {
			return x != v.x || y != v.y || z != v.z;
		}

		Vec3<T> operator*(T f) const {
			return Vec3<T>(f * x, f * y, f * z);
		}

		Vec3<T>& operator*=(T f) {
			x *= f;
			y *= f;
			z *= f;
			return *this;
		}

		Vec3<T> operator/(T f) const {
			float inv = (float)1 / f;
			return Vec3<T>(x * inv, y * inv, z * inv);
		}

		Vec3<T>& operator/=(T f) {
			float inv = (float)1 / f;
			x *= inv;
			y *= inv;
			z *= inv;
			return *this;
		}

		Vec3<T> operator-() const {
			return Vec3<T>(-x, -y, -z);
		}

		T operator[](int i) const {
			assert(i >= 0 && i <= 2);
			if (i == 0) return x;
			if (i == 1) return y;
			return z;
		}

		T& operator[](int i) {
			assert(i >= 0 && i <= 2);
			if (i == 0) return x;
			if (i == 1) return y;
			return z;
		}

		float Norm() const {
			return std::sqrt(x * x + y * y + z * z);
		};

		// Member
		T x;
		T y;
		T z;
	};

	template <typename T>
	Vec2<T> operator*(T s, const Vec2<T>& v) {
		return v * s;
	}

	template <typename T>
	Vec3<T> operator*(T s, const Vec3<T>& v) {
		return v * s;
	}

	template <typename T>
	Vec2<T> Abs(const Vec2<T>& v) {
		return Vec2<T>(std::abs(v.x), std::abs(v.y));
	}

	template <typename T>
	Vec3<T> Abs(const Vec3<T>& v) {
		return Vec2<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
	}

	template <typename T>
	T Dot(const Vec3<T>& v1, const Vec3<T>& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	template <typename T>
	T AbsDot(const Vec3<T>& v1, const Vec3<T>& v2) {
		return std::abs(Dot(v1, v2));
	}

	template <typename T>
	Vec3<T> Cross(const Vec3<T>& v1, const Vec3<T>& v2) {
		return Vec3<T>((v1.y * v2.z) - (v1.z * v2.y),
			(v1.z * v2.x) - (v1.x * v2.z),
			(v1.x * v2.y) - (v1.y * v2.x));
	}

	template <typename T>
	Vec3<T> Normalize(const Vec3<T>& v) {
		return v / v.Norm();
	}

	typedef Vec2<double>   Vec2d;
	typedef Vec2<float> Vec2f;
	typedef Vec2<int>   Vec2i;

	typedef Vec3<double> Vec3d;
	typedef Vec3<float> Vec3f;
	typedef Vec3<int>   Vec3i;
	
}
