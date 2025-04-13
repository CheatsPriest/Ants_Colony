#include "includes.h"
//#include "ImGuiTail.h"
#include "SFMLWindow.h"
#include "Entity.h";
#include "Collector.h"
#include "unordered_map"
#include <thread>
#include <conio.h>
#include <random>
#include <Windows.h>
#include "SFML/Graphics.hpp"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#define NOMINMAX





InfoSpace* ultimateData = new InfoSpace;


void processingEntities() {
	
	srand(time(0));
	ultimateData->CreateStockpile(60, 10, 0, 17, 17, 0, 1);
	ultimateData->CreateStockpile(60, 60, 0, 17, 17, 1, 1);

	ultimateData->CreateEntityFood(10, 20, 0, 0, 10, 10);

	for (int i = 0; i < 100; i++) {
		ultimateData->CreateEntityAnt(15, 2 * i, 0, 0, 1,1);
	}
	for (int i = 0; i < 50; i++) {
		ultimateData->CreateEntityAnt(10, 2*i, 0, 0, 2,1);
	}
	for (int i = 0; i < 10; i++) {
		ultimateData->CreateEntityAnt(12, i, 0, 0, 3,1);
	}

	for (int i = 0; i < 200; i++) {
		ultimateData->CreateEntityFood(rand() % 100 + 50, rand() % 100 + 50, 0, 0, 2000, 10);
		ultimateData->CreateEntityMaterial(rand() % 100 + 50, rand() % 100 + 50, 0, 0, 10);
	}


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

	Window_sfml* start = new Window_sfml(ultimateData);
	sf::RenderWindow mainWindow(sf::VideoMode(ultimateData->main_window_wide,
		ultimateData->main_window_hight), "Ant Colony");

	while (mainWindow.isOpen())
	{
		sf::Event event;

		while (mainWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				mainWindow.close();
		}
		mainWindow.clear();
		for (auto ent : ultimateData->entityList) 
		{
			Entity* curr = ent.second;
			if(curr->getType() == Entities::ANT) 
			{
			
			ultimateData->MoveEntity(ent.first);

			}
		}
		start->DrawMainScene_sfml(mainWindow);
		mainWindow.display();
	}

	//while (ultimateData->mainLoop && mainWindow.isOpen()) 
	//{
	//	for (auto ent : ultimateData->entityList) 
	//	{
	//		Entity* curr = ent.second;
	//		if(curr->getType() == Entities::ANT) 
	//		{
	//			
	//			ultimateData->MoveEntity(ent.first);

	//		}
	//	}

	//	

	//	if (GetAsyncKeyState(VK_LEFT) & 0x8000 != 0)
	//	{
	//		ultimateData->MoveCam(-1, 0);
	//		for (int i = 0; i < 25; i++) {
	//			ultimateData->CreateEntityFood(rand() % 100 + 50, rand() % 100 + 50, 0, 0, 20000, 10);
	//		}
	//	}

	//	// камера Сани

	//	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000 != 0) {
	//		ultimateData->MoveCam(1, 0);
	//	}
	//	else if (GetAsyncKeyState(VK_UP) & 0x8000 != 0) {
	//		ultimateData->MoveCam(0, -1);
	//	}
	//	else if (GetAsyncKeyState(VK_DOWN) & 0x8000 != 0) {
	//		ultimateData->MoveCam(0, 1);
	//	}
	//
	//}

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





