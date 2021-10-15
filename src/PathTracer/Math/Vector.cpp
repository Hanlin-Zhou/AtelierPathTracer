#include "Vector.hpp"

namespace Math {
	// Vec2
	template<typename T>
	Vec2<T>::Vec2(T xx, T yy) : x(xx), y(yy)
	{
		assert(!HasNaNs());
	}


	template<typename T>
	bool Vec2<T>::HasNaNs() const
	{
		return std::isnan(x) || std::isnan(y);
	}


	template<typename T>
	Vec2<T> Vec2<T>::operator+(const Vec2<T>& v) const
	{
		return Vec2(x + v.x, y + v.y);
	}

	template<typename T>
	Vec2<T>& Vec2<T>::operator+=(const Vec2<T>& v)
	{
		x += v.x; y += v.y;
		return *this;
	}

	template<typename T>
	Vec2<T> Vec2<T>::operator-(const Vec2<T>& v) const
	{
		return Vec2(x - v.x, y - v.y);
	}

	template<typename T>
	Vec2<T>& Vec2<T>::operator-=(const Vec2<T>& v)
	{
		x -= v.x; y -= v.y;
		return *this;
	}

	template<typename T>
	bool Vec2<T>::operator==(const Vec2<T>& v) const
	{
		return x == v.x && y == v.y;
	}

	template<typename T>
	bool Vec2<T>::operator!=(const Vec2<T>& v) const
	{
		return x != v.x || y != v.y;
	}

	template<typename T>
	Vec2<T> Vec2<T>::operator*(T f) const
	{
		return Vec2<T>(f * x, f * y);
	}

	template<typename T>
	Vec2<T>& Vec2<T>::operator*=(T f)
	{
		x *= f; y *= f;
		return *this;
	}

	template<typename T>
	Vec2<T> Vec2<T>::operator/(T f) const
	{
		Float inv = (float)1 / f;
		return Vec2<T>(x * inv, y * inv);
	}

	template<typename T>
	Vec2<T>& Vec2<T>::operator/=(T f)
	{
		float inv = (float)1 / f;
		x *= inv; y *= inv;
		return *this;
	}

	template<typename T>
	Vec2<T> Vec2<T>::operator-() const
	{
		return Vec2<T>(-x, -y);
	}

	template<typename T>
	T Vec2<T>::operator[](int i) const
	{
		assert(i >= 0 && i <= 1);
		if (i == 0) return x;
		return y;
	}

	template<typename T>
	T& Vec2<T>::operator[](int i)
	{
		assert(i >= 0 && i <= 1);
		if (i == 0) return x;
		return y;
	}

	template<typename T>
	float Vec2<T>::Norm() const
	{
		return std::sqrt(x * x + y * y);
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const Vec2<T>& v)
	{
		os << "[" << v.x << ", " << v.y << "]";
		return os;
	}

	// Vec3
	template<typename T>
	Vec3<T>::Vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz)
	{
		assert(!HasNaNs());
	}


	template<typename T>
	bool Vec3<T>::HasNaNs() const
	{
		return std::isnan(x) || std::isnan(y);
	}


	template<typename T>
	Vec3<T> Vec3<T>::operator+(const Vec3<T>& v) const
	{
		return Vec3(x + v.x, y + v.y, z + v.z);
	}

	template<typename T>
	Vec3<T>& Vec3<T>::operator+=(const Vec3<T>& v)
	{
		x += v.x; 
		y += v.y;
		z += v.z;
		return *this;
	}

	template<typename T>
	Vec3<T> Vec3<T>::operator-(const Vec3<T>& v) const
	{
		return Vec2(x - v.x, y - v.y, z - v.z);
	}

	template<typename T>
	Vec3<T>& Vec3<T>::operator-=(const Vec3<T>& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	template<typename T>
	bool Vec3<T>::operator==(const Vec3<T>& v) const
	{
		return x == v.x && y == v.y && z == v.z;
	}

	template<typename T>
	bool Vec3<T>::operator!=(const Vec3<T>& v) const
	{
		return x != v.x || y != v.y || z != v.z;
	}

	template<typename T>
	Vec3<T> Vec3<T>::operator*(T f) const
	{
		return Vec3<T>(f * x, f * y, f * z);
	}

	template<typename T>
	Vec3<T>& Vec3<T>::operator*=(T f)
	{
		x *= f; 
		y *= f;
		z *= f;
		return *this;
	}

	template<typename T>
	Vec3<T> Vec3<T>::operator/(T f) const
	{
		Float inv = (float)1 / f;
		return Vec2<T>(x * inv, y * inv, z * inv);
	}

	template<typename T>
	Vec3<T>& Vec3<T>::operator/=(T f)
	{
		float inv = (float)1 / f;
		x *= inv; 
		y *= inv;
		z *= inv;
		return *this;
	}

	template<typename T>
	Vec3<T> Vec3<T>::operator-() const
	{
		return Vec3<T>(-x, -y, -z);
	}

	template<typename T>
	T Vec3<T>::operator[](int i) const
	{
		assert(i >= 0 && i <= 2);
		if (i == 0) return x;
		if (i == 1) return y;
		return z;
	}

	template<typename T>
	T& Vec3<T>::operator[](int i)
	{
		assert(i >= 0 && i <= 2);
		if (i == 0) return x;
		if (i == 1) return y;
		return z;
	}

	template<typename T>
	float Vec3<T>::Norm() const
	{
		return std::sqrt(x * x + y * y + z * z);
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const Vec3<T>& v)
	{
		os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
		return os;
	}

	template<typename T>
	Vec2<T> operator*(T s, const Vec2<T>& v)
	{
		return v * s;
	}

	template<typename T>
	Vec3<T> operator*(T s, const Vec3<T>& v)
	{
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
}