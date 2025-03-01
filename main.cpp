#include "includes.h"
#include "ImGuiTail.h"




int main() {
	InfoSpace* ultimateData = new InfoSpace;
	Window* mainWindow = new Window(standart_wide, standart_hight, ultimateData);

	cout << "New project" << endl;

	while (ultimateData->mainLoop) {
		mainWindow->NewFrame();

		mainWindow->EndFrame();
	}

	
	delete mainWindow;

	return 0;
}