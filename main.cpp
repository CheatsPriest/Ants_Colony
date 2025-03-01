#include "includes.h"
#include "ImGuiTail.h"



int main() {
	
	Window* mainWindow = new Window(standart_wide, standart_hight);

	cout << "New project" << endl;

	while (0) {
		mainWindow->NewFrame();

		mainWindow->EndFrame();
	}


	mainWindow->Cleanup();

	return 0;
}