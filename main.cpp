
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

	

	int start_x = 1000;
	int start_y = 1000;

	long long tick = 0;

	ultimateData->coloniesList[1] = new Colony(1, start_x+20, start_y+20, 0);

	ultimateData->CreateStockpile(start_x+40, start_y+40, 0, 17, 17, 3, 1);
	

	ultimateData->CreateEntityAnt(start_x+50, start_y+50, 0, 0, 0, 1);

	for (int i = 0; i < 200; i++) {
		ultimateData->CreateEntityAnt(start_x+10, 2 * i+ start_y, 0, 0, 1,1);
	}
	for (int i = 0; i < 150; i++) {
		ultimateData->CreateEntityAnt(start_x+20, 2*i+ start_y, 0, 0, 2,1);
	}
	for (int i = 0; i < 10; i++) {
		ultimateData->CreateEntityAnt(start_x+30, i+ start_y, 0, 0, 3,1);
	}
	for (int i = 0; i < 10; i++) {
		ultimateData->CreateEntityAnt(start_x+40, i+ start_y, 0, 0, 4, 1);
	}

	//ultimateData->CreateInsect(22, 22, 0, InsectTypes::APHID, { 0, 0 }, { 0 , 0 }, false);
	// тля внутри загона
	//for (int i = 0; i < 50; i++) {
	//	ultimateData->CreateInsect(rand() % wallWidth + wallX, rand() % wallHeight + wallY, 0, InsectTypes::APHID, { wallX, wallY }, { wallWidth , wallHeight }, true);
	//}

	//// тля вне загона(не рабы пока что)
	for (int i = 0; i < 500; i++) {
		ultimateData->CreateInsect(rand() % 50 + 100  + start_x, rand() % 50 + 100 + start_y, 0, InsectTypes::APHID, { 0, 0 }, { 0 , 0 }, false);
	}

	for (int i = 0; i < 100; i++) {
		ultimateData->CreateInsect(rand() % 50 + 100 + start_x, rand() % 50 + 100 + start_y, 0, InsectTypes::LADYBUG, { 0, 0 }, { 0 , 0 }, false);
	}


	for (int i = 0; i < 20000; i++) {
		ultimateData->CreateEntityFood(rand() % ultimateData->field_size_x, rand() % ultimateData->field_size_y, 0, 0, 2000, 10);
		ultimateData->CreateEntityMaterial(rand() % ultimateData->field_size_x, rand() % ultimateData->field_size_y, 0, 0, 10);
	}
	//for (int i = 0; i < 600; i++) {

	//	//ultimateData->CreateEntityFood(rand() % ultimateData->field_size_x, rand() % ultimateData->field_size_y, 0, 0, 2000, 10);
	//	ultimateData->CreateEntityMaterial(rand() % 50+start_x+20, rand() % 50+start_y+20, 0, 0, 10);
	//}


	//Приветствие
	for (auto el : ultimateData->entityList) {
		break;
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

		if (tick++ > 200) {
			tick = 1;
		}
		for (auto el : ultimateData->coloniesList) {

			ultimateData->BuildNewStockpile(el.second);

		}
		
		if (tick % 5 == 0) {
			ultimateData->RecountAphid();
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
		mainWindow->NewFrame();

		mainWindow->EndFrame();
		
		


	}
	delete mainWindow;
}

int main() {
	thread ProcessingEntity(processingEntities);

	ProcessingEntity.join();

	return 0;
}
