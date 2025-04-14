
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
	

	int start_x = 1000;
	int start_y = 1000;

	long long tick = 0;

	ultimateData->coloniesList[1] = new Colony(1, start_x+20, start_y+20, 0);

	//ultimateData->CreateStockpile(start_x, start_y, 0, 30, 30, 2, 1);

	ultimateData->CreateStockpile(start_x+40, start_y+40, 0, 17, 17, 3, 1);
	
	

	//ultimateData->CreateStockpile(start_x+40, start_y, 0, 17, 17, 0, 1);
	//ultimateData->CreateStockpile(start_x+30, start_y+40, 0, 17, 17, 1, 1);
	//ultimateData->CreateStockpile(start_x+30, start_y + 90, 0, 17, 17, 1, 1);


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
	// ��� ������ ������
	//for (int i = 0; i < 50; i++) {
	//	ultimateData->CreateInsect(rand() % wallWidth + wallX, rand() % wallHeight + wallY, 0, InsectTypes::APHID, { wallX, wallY }, { wallWidth , wallHeight }, true);
	//}

	//// ��� ��� ������(�� ���� ���� ���)
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


	//�����������
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

	
	sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
	sf::RenderWindow mainWindow(desktopMode, "Ant Colony", sf::Style::Fullscreen);

	Window_sfml* start = new Window_sfml(ultimateData);

	//sf::RenderWindow mainWindow(	sf::VideoMode(ultimateData->main_window_wide,
	//	ultimateData->main_window_hight), "Ant Colony");




	// Camera
	sf::View view = mainWindow.getDefaultView();
	float currentZoom = 1.0f;
	const float zoomSpeed = 0.1f;
	const float moveSpeed = 500.0f;

	const float minZoom = 0.5f; // ���������� � 2 ���� ����
	const float maxZoom = 2.0f; // �������� � 2 ���� ����

	currentZoom = std::max(minZoom, std::min(currentZoom, maxZoom));

	view.zoom(1.0f / currentZoom);
	view.setCenter(desktopMode.width / 2, desktopMode.height / 2);
	// Camera

	sf::Clock clock;

	while (mainWindow.isOpen())
	{

		sf::Event event;

		while (mainWindow.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed) ||
				(event.type == sf::Event::KeyPressed &&
					event.key.code == sf::Keyboard::Escape))
				mainWindow.close();

			if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
				{
					float delta = event.mouseWheelScroll.delta;
					currentZoom *= (1.0f - delta * zoomSpeed);
					currentZoom = std::max(minZoom, std::min(currentZoom, maxZoom));
					view.setSize(desktopMode.width, desktopMode.height);
					view.zoom(1.0f / currentZoom);
				}
			}
		}
		
		float deltaTime = clock.restart().asSeconds();
		sf::Vector2f movement(0, 0);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			movement.y -= moveSpeed * deltaTime;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			movement.y += moveSpeed * deltaTime;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			movement.x -= moveSpeed * deltaTime;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			movement.x += moveSpeed * deltaTime;

		view.move(movement * currentZoom);
		mainWindow.setView(view);

		mainWindow.clear();

		if (tick++ > 200) 
		{
			tick = 1;
		}

		for (auto el : ultimateData->coloniesList) 
		{
			ultimateData->BuildNewStockpile(el.second);
		}

		if (tick % 5 == 0) 
		{
			ultimateData->RecountAphid();
		}


		for (auto ent : ultimateData->entityList)
		{


			Entity* curr = ent.second;
			if (curr && curr->getType() == Entities::ANT)
			{

				ultimateData->MoveEntity(ent.first);


			}
			else if (curr and curr->getType() == Entities::INSECT)
			{
				Insect* insect = (Insect*)curr;

				ultimateData->MoveInsect(ent.first);

				//insect->move(ultimateData->entityList, ent.first);
			}
		}
		start->DrawMainScene_sfml(mainWindow);
		mainWindow.display();
	}


}



int main() {

	
	//����� ��������� Entity
	thread ProcessingEntity(processingEntities);
	//����� ���������
	//thread Drow(draw);
	


	ProcessingEntity.join();
	//Drow.join();
	return 0;
}
