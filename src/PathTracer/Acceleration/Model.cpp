#include "Model.hpp"
namespace APT {
	Model::Model(std::string name, std::string path, std::string directory)
	{
		mName = name;
		mPath = path;
		mDirectory = directory;
	}
}