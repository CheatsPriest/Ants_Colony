
#include "includes.h"
#include "ImGuiTail.h"
#include "Entity.h";
#include "Collector.h"
#include "unordered_map"
#include <thread>
#include <conio.h>
#include <Windows.h>
#include <random>

InfoSpace* ultimateData = new InfoSpace;


void processingEntities() {
	Window* mainWindow = new Window(ultimateData);


	srand(time(0));

	

	int start_x = 200;
	int start_y = 200;

	ultimateData->coloniesList[1] = new Colony(1, start_x+20, start_y+20, 0);

	//ultimateData->CreateStockpile(start_x, start_y, 0, 30, 30, 2, 1);

	ultimateData->CreateStockpile(start_x+40, start_y+40, 0, 17, 17, 3, 1);
	
	

	//ultimateData->CreateStockpile(start_x+40, start_y, 0, 17, 17, 0, 1);
	//ultimateData->CreateStockpile(start_x+30, start_y+40, 0, 17, 17, 1, 1);
	//ultimateData->CreateStockpile(start_x+30, start_y + 90, 0, 17, 17, 1, 1);


	ultimateData->CreateEntityAnt(210, 230, 0, 0, 0, 1);

	for (int i = 0; i < 100; i++) {
		ultimateData->CreateEntityAnt(210, 2 * i+200, 0, 0, 1,1);
	}
	for (int i = 0; i < 50; i++) {
		ultimateData->CreateEntityAnt(220, 2*i+200, 0, 0, 2,1);
	}
	for (int i = 0; i < 10; i++) {
		ultimateData->CreateEntityAnt(230, i+200, 0, 0, 3,1);
	}
	for (int i = 0; i < 10; i++) {
		ultimateData->CreateEntityAnt(240, i+200, 0, 0, 4, 1);
	}

	//ultimateData->CreateInsect(22, 22, 0, InsectTypes::APHID, { 0, 0 }, { 0 , 0 }, false);
	// тля внутри загона
	//for (int i = 0; i < 50; i++) {
	//	ultimateData->CreateInsect(rand() % wallWidth + wallX, rand() % wallHeight + wallY, 0, InsectTypes::APHID, { wallX, wallY }, { wallWidth , wallHeight }, true);
	//}

	//// тля вне загона(не рабы пока что)
	for (int i = 0; i < 30; i++) {
		ultimateData->CreateInsect(rand() % 50+ start_x, rand() % 50+ start_y, 0, InsectTypes::APHID, { 0, 0 }, { 0 , 0 }, false);
	}
	for (int i = 0; i < 15000; i++) {
		ultimateData->CreateEntityFood(rand() % ultimateData->field_size_x, rand() % ultimateData->field_size_y, 0, 0, 2000, 10);
		ultimateData->CreateEntityMaterial(rand() % ultimateData->field_size_x, rand() % ultimateData->field_size_y, 0, 0, 10);
	}


	//Приветствие
	for (auto el : ultimateData->entityList) {
		Entity* curr = el.second;
		if (curr->getType() == Entities::ANT) {
			Ant* currAnt = (Ant*)(curr->getPtr());
			currAnt->info();
			
			
		}
		else if (curr->getType() == Entities::FOOD) {
			Food* currFood = (Food*)(curr->getPtr());
			currFood->info();
		}
		else if (curr->getType() == Entities::INSECT) {
			Insect* currInsect = (Insect*)curr;
			//currInsect->info();
		}
	}


	while (ultimateData->mainLoop) {

		for (auto el : ultimateData->coloniesList) {

			ultimateData->BuildNewStockpile(el.second);

		}

		for (auto ent : ultimateData->entityList) {

			Entity* curr = ent.second;
			if(curr && curr->getType() == Entities::ANT) {
				
				ultimateData->MoveEntity(ent.first);

				

			}
			else if (curr and curr->getType() == Entities::INSECT) {
				Insect* insect = (Insect*)curr;
				
				ultimateData->MoveInsect(ent.first);
				
				//insect->move(ultimateData->entityList, ent.first);
			}
		}


		if (GetAsyncKeyState(VK_LEFT) & 0x8000 != 0)
		{
			ultimateData->MoveCam(-1, 0);
			for (int i = 0; i < 25; i++) {
				ultimateData->CreateEntityFood(rand() % 100 + 50, rand() % 100 + 50, 0, 0, 20000, 10);
			}
			ultimateData->ReCalculateTheColony();
			ultimateData->coloniesList[1];
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

	mainWindow->Cleanup();
	delete mainWindow;
}
int main() {

	
	//поток обработки Entity
	thread ProcessingEntity(processingEntities);
	//поток отрисовки
	//thread Drow(draw);
	


	ProcessingEntity.join();
	//Drow.join();
	return 0;
}
