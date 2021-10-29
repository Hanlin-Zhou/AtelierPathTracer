#include "UIFileMenu.hpp"
namespace APT {
	namespace UI {
		void FileMenu(std::shared_ptr<PathTracer> pathtracer)
		{
			if (ImGui::BeginMenu("File")) {
				tinyfd_assumeGraphicDisplay = 1;
				if (ImGui::MenuItem("Open", NULL)) {
				
				}
				if (ImGui::MenuItem("Import", NULL)) {
					char const* lFilterPatterns[1] = { "*.obj" };
					std::string path = tinyfd_openFileDialog("Open Your OBJ Model", "./", 1, lFilterPatterns, "OBJ File", 0);
					pathtracer->mSceneLoader->LoadModelFromFile(path);
				}
				if (ImGui::MenuItem("Save File", NULL)) {

				}
				if (ImGui::MenuItem("Save Render", NULL)) {

				}
				ImGui::EndMenu();
			}
		}
	}
}