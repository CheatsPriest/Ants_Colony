#ifndef HHHH
#define HHHH
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
	int stockX = 60;
	int stockY = 60;
	int stockWidth = 50;
	int stockHeight = 57;

	ultimateData->CreateStockpile(60, 10, 0, 17, 17, 0);
	ultimateData->CreateStockpile(stockX, stockY, 0, stockWidth, stockHeight, 0);
	
	ultimateData->CreateEntityFood(10, 20, 0, 0, 10, 10);

	for (int i = 0; i < 100; i++) {
		ultimateData->CreateEntityAnt(15, 2 * i, 0, 0, 1);
	}
	for (int i = 0; i < 50; i++) {
		ultimateData->CreateEntityAnt(10, 2*i, 0, 0, 2);
	}
	for (int i = 0; i < 1; i++) {
		ultimateData->CreateEntityAnt(12, i, 0, 0, 3);
	}

	for (int i = 0; i < 200; i++) {
		ultimateData->CreateEntityFood(rand() % 100 + 50, rand() % 100 + 50, 0, 0, 2000, 10);
		//ultimateData->CreateEntityMaterial(0,0, 0, 0, 10);
		ultimateData->CreateEntityMaterial(rand() % 100 + 50, rand() % 100 + 50, 0, 0, 10);
		//ultimateData->CreateInsect(rand() % 60 + i, rand() % 20 + i, 0, InsectTypes::APHID);
		//ultimateData->CreateInsect(30, 5, 0, InsectTypes::APHID);
	}
	for (int i = 0; i < 15; i++) {
		//	ultimateData->CreateEntityFood(rand() % 100 + 50, rand() % 100 + 50, 0, 0, 2000, 10);
			//ultimateData->CreateEntityMaterial(0,0, 0, 0, 10);
		//ultimateData->CreateEntityMaterial(rand() % 100 + 50, rand() % 100 + 50, 0, 0, 10);
		ultimateData->CreateInsect(rand() % stockWidth + stockX, rand() % stockY + stockX, 0, InsectTypes::APHID, {stockX, stockY}, {stockWidth, stockHeight});
		//ultimateData->CreateInsect(30, 5, 0, InsectTypes::APHID);
	}
	/*for (int i = 0; i < 100; i++) {
		ultimateData->CreateEntity(rand() % 100 + 50, rand() % 100 + 50,5);
	}*/

	
	
	//ultimateData->entityList.insert({ 3, entity3 });

	//ѕриветствие
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
		for (auto ent : ultimateData->entityList) {

			Entity* curr = ent.second;
			if(curr->getType() == Entities::ANT) {
				
				ultimateData->MoveEntity(ent.first);


			}
			else if (curr->getType() == Entities::INSECT) {
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
#endif