#include <iostream>
#include <Core/Application.hpp>

int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow) {
	std::cout << "Atelier" << std::endl;
	APT::Application app(hInstance);
	app.Run();
	return 0;
}