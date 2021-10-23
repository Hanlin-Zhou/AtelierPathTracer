#pragma once
#include <ImGui/imgui.h>
#include <ImGui/backends/imgui_impl_dx12.h>
#include <ImGui/backends/imgui_impl_win32.h>
#include <PathTracer/Core/PathTracer.hpp>

namespace APT {
	namespace UI {
		void FileMenu(std::shared_ptr<PathTracer> pathtracer);
	}
}