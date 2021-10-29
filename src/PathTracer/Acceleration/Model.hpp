#pragma once
#include <PathTracer/Acceleration/Primitive.hpp>
#include <PathTracer/Acceleration/Mesh.hpp>
#include <vector>
#include <string>

namespace APT {
	class Model : public Primitive {
	public:
		Model(std::string name, std::string path, std::string directory);


		std::vector<std::unique_ptr<Mesh>> mMeshes;
		std::string mName;
		std::string mPath;
		std::string mDirectory;
	};
}