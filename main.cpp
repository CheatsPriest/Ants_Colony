#include "includes.h"
#include "ImGuiTail.h"
#include "Entity.h";
#include "Ant.h";
#include "Queen.h";
#include "Soldier.h"
#include "unordered_map"

int main() {
	unordered_map<int, Entity*> entityList;
	Ant* ant = new Ant();
	Food* food = new Food();
	Soldier* soldier = new Soldier();

	Entity* entity1 = new Entity(ant, Entities::ANT);
	Entity* entity2 = new Entity(food, Entities::FOOD);
	Entity* entity3 = new Entity(soldier, Entities::ANT);

	entityList.insert({ 1, entity1 });
	entityList.insert({ 2, entity2 });
	entityList.insert({ 3, entity3 });
	
	for (auto el : entityList) {
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