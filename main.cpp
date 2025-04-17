
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

	int start_x1 = 1500;
	int start_y1 = 1000;

	long long tick = 0;

	ultimateData->coloniesList[1] = new Colony(1, start_x+20, start_y+20, 0);

	ultimateData->coloniesList[2] = new Colony(2, start_x1 + 20, start_y1 + 20, 0);

	//ultimateData->CreateStockpile(start_x, start_y, 0, 30, 30, 2, 1);

	ultimateData->CreateStockpile(start_x+40, start_y+40, 0, 17, 17, 3, 1);
	
	ultimateData->CreateStockpile(start_x1 + 40, start_y1 + 40, 0, 17, 17, 3, 2);

	//ultimateData->CreateStockpile(start_x+40, start_y, 0, 17, 17, 0, 1);
	//ultimateData->CreateStockpile(start_x+30, start_y+40, 0, 17, 17, 1, 1);
	//ultimateData->CreateStockpile(start_x+30, start_y + 90, 0, 17, 17, 1, 1);


	ultimateData->CreateEntityAnt(start_x+50, start_y+50, 0, 0, 0, 1);
	ultimateData->CreateEntityAnt(start_x1 + 50, start_y1 + 50, 0, 0, 0, 2);

	for (int i = 0; i < 200; i++) {
		ultimateData->CreateEntityAnt(start_x+10, 2 * i+ start_y, 0, 0, 1,1);
	}
	for (int i = 0; i < 150; i++) {
		ultimateData->CreateEntityAnt(start_x+20, 2*i+ start_y, 0, 0, 2,1);
	}
	for (int i = 0; i < 500; i++) {
		ultimateData->CreateEntityAnt(start_x+30, i+ start_y, 0, 0, 3,1);
	}
	for (int i = 0; i < 10; i++) {
		ultimateData->CreateEntityAnt(start_x+40, i+ start_y, 0, 0, 4, 1);
	}

	for (int i = 0; i < 200; i++) {
		ultimateData->CreateEntityAnt(start_x1 + 10, 2 * i + start_y1, 0, 0, 1, 2);
	}
	for (int i = 0; i < 150; i++) {
		ultimateData->CreateEntityAnt(start_x1 + 20, 2 * i + start_y1, 0, 0, 2, 2);
	}
	for (int i = 0; i < 500; i++) {
		ultimateData->CreateEntityAnt(start_x1 + 30, i + start_y1, 0, 0, 3, 2);
	}
	for (int i = 0; i < 10; i++) {
		ultimateData->CreateEntityAnt(start_x1 + 40, i + start_y1, 0, 0, 4, 2);
	}

	//ultimateData->CreateInsect(22, 22, 0, InsectTypes::APHID, { 0, 0 }, { 0 , 0 }, false);
	// тля внутри загона
	//for (int i = 0; i < 50; i++) {
	//	ultimateData->CreateInsect(rand() % wallWidth + wallX, rand() % wallHeight + wallY, 0, InsectTypes::APHID, { wallX, wallY }, { wallWidth , wallHeight }, true);
	//}

	//// тля вне загона(не рабы пока что)
	for (int i = 0; i < 1500; i++) {
		ultimateData->CreateInsect(rand() % ultimateData->field_size_x, rand() % ultimateData->field_size_y, 0, InsectTypes::APHID, { 0, 0 }, { 0 , 0 }, false);
	}

	for (int i = 0; i < 100; i++) {
		ultimateData->CreateInsect(rand() % ultimateData->field_size_x, rand() % ultimateData->field_size_y, 0, InsectTypes::LADYBUG, { 0, 0 }, { 0 , 0 }, false);
	}


	for (int i = 0; i < 200'000; i++) {
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

	
	ultimateData->ReCalculateTheColony();

	while (ultimateData->mainLoop) {

		

		if (tick++ > 300) {
			tick = 1;
			ultimateData->ReCalculateTheColony();
		}
		for (auto el : ultimateData->coloniesList) {

			ultimateData->BuildNewStockpile(el.second);

		}
		
		if (tick % 5 == 0) {
			
		}
		ultimateData->RecountAphid();

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
			ultimateData->MoveCam(-5, 0);
			/*for (int i = 0; i < 25; i++) {
				ultimateData->CreateEntityFood(rand() % 100 + 50, rand() % 100 + 50, 0, 0, 20000, 10);
			}*/
			
		}
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000 != 0) {
			ultimateData->MoveCam(5, 0);
		}
		else if (GetAsyncKeyState(VK_UP) & 0x8000 != 0) {
			ultimateData->MoveCam(0, -5);
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000 != 0) {
			ultimateData->MoveCam(0, 5);
		}
		else if (GetAsyncKeyState(VK_SPACE) & 0x8000 != 0) { 
			ultimateData->ReCalculateTheColony();
    		ultimateData->coloniesList[1];
		}
		else if (GetAsyncKeyState(VK_F1) & 0x8000 != 0) {
			if (ultimateData->cell_size > 2) {
				float new_x, new_y;

				ultimateData->x_cam /= ultimateData->cell_size;
				ultimateData->y_cam /= ultimateData->cell_size;
				ultimateData->cell_size--;
				ultimateData->x_cam *= ultimateData->cell_size;
				ultimateData->y_cam *= ultimateData->cell_size;
			}
		}
		else if (GetAsyncKeyState(VK_F2) & 0x8000 != 0) {
			if (ultimateData->cell_size < 50) {
				ultimateData->x_cam /= ultimateData->cell_size;
				ultimateData->y_cam /= ultimateData->cell_size;
				ultimateData->cell_size++;
				ultimateData->x_cam *= ultimateData->cell_size;
				ultimateData->y_cam *= ultimateData->cell_size;
			}
		}
		else if (GetAsyncKeyState(VK_F3) & 0x8000 != 0) {
			if (!ultimateData->isSpectating) {

				vector<unsigned int> targets;
				for (auto ent : ultimateData->entityList) {
					if (ent.second and ent.second->getType() == ANT) {
						targets.push_back(ent.first);
					}
				}
				ultimateData->objectOfInterest=ultimateData->entityList[targets[rand() % (targets.size() - 1)]];
				targets.clear();
				ultimateData->isSpectating = true;
			
			}
			else {
				ultimateData->isSpectating = false;
			}
		}
		else if (GetAsyncKeyState(VK_F4) & 0x8000 != 0) {
			if (!ultimateData->isSpectating) {

				vector<unsigned int> targets;
				for (auto ent : ultimateData->entityList) {
					if (ent.second and ent.second->getType() == INSECT) {
						targets.push_back(ent.first);
					}
				}
				ultimateData->objectOfInterest = ultimateData->entityList[targets[rand() % (targets.size() - 1)]];
				targets.clear();
				ultimateData->isSpectating = true;

			}
			else {
				ultimateData->isSpectating = false;
			}
		}

		if (ultimateData->isSpectating) {
			if (ultimateData->objectOfInterest == 0) {
				ultimateData->isSpectating = false;
			}
			if (ultimateData->objectOfInterest->getType() == ANT) {
				Ant* spec = (Ant*)ultimateData->objectOfInterest->getPtr();
				ultimateData->x_cam = ultimateData->cell_size * (spec->pos_x ) - ultimateData->main_window_wide/2;
				ultimateData->y_cam = ultimateData->cell_size * (spec->pos_y ) - ultimateData->main_window_hight / 2;
			}
			else if (ultimateData->objectOfInterest->getType() == INSECT) {
				Insect* spec = (Insect*)ultimateData->objectOfInterest->getPtr();
				ultimateData->x_cam = ultimateData->cell_size * (spec->pos_x) - ultimateData->main_window_wide / 2;
				ultimateData->y_cam = ultimateData->cell_size * (spec->pos_y) - ultimateData->main_window_hight / 2;
			}
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
