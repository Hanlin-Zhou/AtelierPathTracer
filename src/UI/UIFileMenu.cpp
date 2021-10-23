#include "UIFileMenu.hpp"
namespace APT {
	namespace UI {
		void FileMenu(std::shared_ptr<PathTracer> pathtracer)
		{
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("Open", NULL)) {
				
				}
				if (ImGui::MenuItem("Import", NULL)) {

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