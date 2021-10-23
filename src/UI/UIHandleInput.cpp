#include "UIHandleInput.hpp"

namespace APT {
	bool UIMouseCatured()
	{
		ImGuiIO& io = ImGui::GetIO();
		return io.WantCaptureMouse;
	}
}