#pragma once
#include <PathTracer/Shape/Shape.hpp>
#include <PathTracer/Shape/TriangleMesh.hpp>
namespace APT {
	class Triangle :public Shape {
	public:
		Triangle(const Transform* objectToWorld, const std::shared_ptr<TriangleMesh>& mesh, int num);


	private:
		std::shared_ptr<TriangleMesh> mMesh;

	};
}
