#include "SceneLoader.hpp"
namespace APT {
	SceneLoader::SceneLoader(std::shared_ptr<Scene> scene, std::shared_ptr<PreviewRenderer> previewRenderer)
	{
		mScene = scene;
		mPreviewRenderer = previewRenderer;
	}

	void SceneLoader::LoadModelFromFile(std::string path)
	{
		Assimp::Importer import;
		const aiScene* model = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph | aiProcess_JoinIdenticalVertices);

		if (!model || model->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !model->mRootNode) {
			DebugOut("ASSIMP LOAD FAILED");
			return;
		}

		std::string directory = path.substr(0, path.find_last_of("\\"));
		if (directory.length() == path.length()) {
			directory = path.substr(0, path.find_last_of("/"));
		}

		std::unique_ptr<Model> new_model = std::make_unique<Model>(path, path, directory);

		ProcessModel(model->mRootNode, model, *new_model);
		mPreviewRenderer->UploadModel(*new_model);
		mScene->aggregate->mModels.push_back(std::move(new_model));

	}

	void SceneLoader::ProcessModel(aiNode* node, const aiScene* scene, Model &model)
	{
		std::vector<std::unique_ptr<Mesh>> meshes;
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			ProcessMesh(mesh, scene, model);
		}

		for (unsigned i = 0; i < node->mNumChildren; i++)
		{ 
			ProcessModel(node->mChildren[i], scene, model);
		}
	}

	void SceneLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene, Model& model)
	{
		std::vector<unsigned int> index;
		std::vector<Vec3f> position;
		std::vector<Vec3f> tangent;
		std::vector<Vec3f> normal;
		std::vector<Vec2f> uv;
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			Vec3f positionVector;
			positionVector.x = mesh->mVertices[i].x;
			positionVector.y = mesh->mVertices[i].y;
			positionVector.z = mesh->mVertices[i].z;
			position.push_back(positionVector);

			Vec3f normalVector;
			normalVector.x = mesh->mNormals[i].x;
			normalVector.y = mesh->mNormals[i].y;
			normalVector.z = mesh->mNormals[i].z;
			normal.push_back(normalVector);
		}
		
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				index.push_back((unsigned int)face.mIndices[j]);
		}

		std::unique_ptr<Mesh> myMesh = std::make_unique<Mesh>(Transform(), 0, index, position.size(), position, tangent, normal, uv);
		model.mMeshes.push_back(std::move(myMesh));
	}
}