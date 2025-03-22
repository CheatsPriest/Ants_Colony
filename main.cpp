#include "includes.h"
#include "ImGuiTail.h"
#include "Entity.h";
#include "Collector.h"
#include "unordered_map"
#include <thread>
#include <conio.h>
#include <Windows.h>


InfoSpace* ultimateData = new InfoSpace;

void processingEntities() {
	
	ultimateData->CreateEntityAnt(10, 2, 0, 0, 1);
	ultimateData->CreateEntityAnt(3, 5, 0, 0, 2);
	ultimateData->CreateEntityAnt(12, 6, 0, 0, 3);
	
	//ultimateData->entityList.insert({ 3, entity3 });

	for (auto el : ultimateData->entityList) {
		Entity* curr = el.second;
		if (curr->getType() == Entities::ANT) {
			Ant* currAnt = (Ant*)(curr->getPtr());
			currAnt->aim.push_back({ 10, 10 });
			currAnt->aim.push_back({ 1, 100 });
			currAnt->info();
		}
		else if (curr->getType() == Entities::FOOD) {
			Food* currFood = (Food*)(curr->getPtr());
			currFood->info();
		}
	}
}

void draw() {
	
	Window* mainWindow = new Window(ultimateData);

	


	

	while (ultimateData->mainLoop) {

		if (GetAsyncKeyState(VK_LEFT) & 0x8000 != 0)
		{
			ultimateData->MoveCam(-1, 0);
		}
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000 != 0) {
			ultimateData->MoveCam(1, 0);
		}
		else if (GetAsyncKeyState(VK_UP) & 0x8000 != 0) {
			ultimateData->MoveCam(0, -1);
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000 != 0) {
			ultimateData->MoveCam(0, 1);
		}
		
		mainWindow->NewFrame();

		mainWindow->EndFrame();
	}


	delete mainWindow;
}
int main() {
	
	//поток обработки Entity
	thread ProcessingEntity(processingEntities);
	//поток отрисовки
	thread Drow(draw);



	ProcessingEntity.join();
	Drow.join();
	return 0;
}