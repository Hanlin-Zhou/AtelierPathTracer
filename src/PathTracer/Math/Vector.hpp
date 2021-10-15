#pragma once
#include <cmath>
#include <cassert>
#include <iostream>


namespace Math {
	template <typename T> class Vec2 {
	public:
		Vec2() { x = y = 0; }
		Vec2(T xx, T yy);
		bool HasNaNs() const;
		friend std::ostream& operator <<(std::ostream& os, const Vec2<T>& v);
		Vec2<T> operator+(const Vec2<T>& v) const;
		Vec2<T>& operator+=(const Vec2<T>& v);
		Vec2<T> operator-(const Vec2<T>& v) const;
		Vec2<T>& operator-=(const Vec2<T>& v);
		bool operator==(const Vec2<T>& v) const;
		bool operator!=(const Vec2<T>& v) const;
		Vec2<T> operator*(T f) const;
		Vec2<T>& operator*=(T f);
		Vec2<T> operator/(T f) const;
		Vec2<T>& operator/=(T f);
		Vec2<T> operator-() const;
		T operator[](int i) const;
		T& operator[](int i);
		float Norm() const;

		// Member
		T x;
		T y;
	};
	
	template <typename T> class Vec3 {
	public:
		Vec3() { x = y = z = 0; }
		Vec3(T xx, T yy, T zz);
		bool HasNaNs() const;
		friend std::ostream& operator <<(std::ostream& os, const Vec3<T>& v);
		Vec3<T> operator+(const Vec3<T>& v) const;
		Vec3<T>& operator+=(const Vec3<T>& v);
		Vec3<T> operator-(const Vec3<T>& v) const;
		Vec3<T>& operator-=(const Vec3<T>& v);
		bool operator==(const Vec3<T>& v) const;
		bool operator!=(const Vec3<T>& v) const;
		Vec3<T> operator*(T f) const;
		Vec3<T>& operator*=(T f);
		Vec3<T> operator/(T f) const;
		Vec3<T>& operator/=(T f);
		Vec3<T> operator-() const;
		T operator[](int i) const;
		T& operator[](int i);
		float Norm() const;

		// Member
		T x;
		T y;
		T z;
	};

	template <typename T>
	Vec2<T> operator*(T s, const Vec2<T>& v);

	template <typename T>
	Vec3<T> operator*(T s, const Vec3<T>& v);

	template <typename T>
	Vec2<T> Abs(const Vec2<T>& v);

	template <typename T>
	Vec3<T> Abs(const Vec3<T>& v);

	template <typename T>
	T Dot(const Vec3<T>& v1, const Vec3<T>& v2);

	template <typename T>
	T AbsDot(const Vec3<T>& v1, const Vec3<T>& v2);

	template <typename T>
	Vec3<T> Cross(const Vec3<T>& v1, const Vec3<T>& v2);

	template <typename T>
	Vec3<T> Normalize(const Vec3<T>& v);

	typedef Vec2<double>   Vec2d;
	typedef Vec2<float> Vec2f;
	typedef Vec2<int>   Vec2i;

	typedef Vec3<double> Vec3d;
	typedef Vec3<float> Vec3f;
	typedef Vec3<int>   Veci;
	
}
