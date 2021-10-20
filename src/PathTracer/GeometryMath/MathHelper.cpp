#include "MathHelper.hpp"
namespace Math {
	float PI = 3.14159265359f;
	float PI2 = 6.28318530718f;
	float DoverR = 180.0f / 3.14159265359f;
	float RoverD = 3.14159265359f / 180.0f;

	float ToRadian(float degree)
	{
		return degree * RoverD;
	}

	float ToDegree(float radian)
	{
		return radian * DoverR;
	}

	float Lerp(float t, float v1, float v2)
	{
		return (1 - t) * v1 + t * v2;
	}
}