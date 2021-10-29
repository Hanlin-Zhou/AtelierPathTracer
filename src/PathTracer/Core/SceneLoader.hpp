#pragma once
#include <PathTracer/Scene/Scene.hpp>
#include <PathTracer/Core/PreviewRenderer.hpp>
#include <memory>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Utility/OutputDebug.hpp>

namespace APT {
	class SceneLoader {
	public:
		SceneLoader(std::shared_ptr<Scene> scene, std::shared_ptr<PreviewRenderer> previewRenderer);
		void LoadModelFromFile(std::string path);

	private:
		void ProcessModel(aiNode* node, const aiScene* scene, Model &model);
		void ProcessMesh(aiMesh* mesh, const aiScene* scene, Model& model);


		bool mLoaded = false;
		std::shared_ptr<Scene> mScene;
		std::shared_ptr<PreviewRenderer> mPreviewRenderer;

	};
}