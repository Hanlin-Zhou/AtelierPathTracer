#include "Triangle.hpp"
#pragma once

namespace APT {
	Triangle::Triangle(const Transform* objectToWorld, const std::shared_ptr<TriangleMesh>& mesh, int num):
		Shape(objectToWorld), mMesh(mesh)
	{

	}
}
