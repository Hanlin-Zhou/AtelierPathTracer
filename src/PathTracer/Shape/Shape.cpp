#include "Shape.hpp"
namespace APT {
	Shape::Shape(const Transform* objectToWorld, const Transform* worldToObject, bool reverseOrientation)
		: mObjectToWorld(objectToWorld), mWorldToObject(worldToObject), mReverseOrientation(reverseOrientation),
		mSwapsHandedness(objectToWorld->SwapsHandedness()) {}

	Shape::~Shape()
	{
	}

	Bounds3f Shape::WorldBound() const
	{
		return (*mObjectToWorld)(ObjectBound());
	}



}