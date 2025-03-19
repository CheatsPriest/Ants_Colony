#include "includes.h"
#include "ImGuiTail.h"
#include "Entity.h";
#include "Collector.h"
#include "unordered_map"
#include <thread>

InfoSpace* ultimateData = new InfoSpace;

void processingEntities() {
	
	Ant* scout = new Scout(4, 5, 0);
	
	Ant* soldier = new Soldier(12,14, 0);

	Entity* entity1 = new Entity(scout, Entities::ANT);
	
	Entity* entity3 = new Entity(soldier, Entities::ANT);



	

	ultimateData->entityList.insert({ 1, entity1 });
	ultimateData->field->field[scout->pos_x][scout->pos_y][scout->pos_z].IDs[0]=1;
	
	//ultimateData->entityList.insert({ 3, entity3 });

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
	}
}

void draw() {
	
	Window* mainWindow = new Window(ultimateData);

	cout << "New project" << endl;

	while (ultimateData->mainLoop) {
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