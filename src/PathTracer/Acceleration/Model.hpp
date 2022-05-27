#pragma once
#include <PathTracer/Acceleration/Primitive.hpp>
#include <PathTracer/Acceleration/Mesh.hpp>
#include <vector>
#include <string>

namespace APT {
	class Model : public Primitive {
	public:
		Model(std::string name, std::string path, std::string directory);

		/*virtual Bounds3f WorldBound() const;
		virtual bool Intersect(const Ray& r, SurfaceInteraction*) const;
		virtual bool IntersectP(const Ray& r) const;*/

		std::vector<std::unique_ptr<Mesh>> mMeshes;
		std::string mName;
		std::string mPath;
		std::string mDirectory;
	};
}