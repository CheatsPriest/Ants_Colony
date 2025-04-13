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



	sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
	sf::RenderWindow mainWindow(desktopMode, "Ant Colony", sf::Style::Fullscreen);

	Window_sfml* start = new Window_sfml(ultimateData);

	//sf::RenderWindow mainWindow(	sf::VideoMode(ultimateData->main_window_wide,
	//	ultimateData->main_window_hight), "Ant Colony");

	// BackGround
	sf::Texture place;
	if (!place.loadFromFile("images/back.jpeg"))
		return;
	sf::Sprite back(place);

	float scaleX = static_cast<float>(desktopMode.width) / place.getSize().x;
	float scaleY = static_cast<float>(desktopMode.height) / place.getSize().y;
	float scale = std::max(scaleX, scaleY);
	back.setScale(scale, scale);

	back.setPosition(
		(desktopMode.width - back.getGlobalBounds().width) / 2,
		(desktopMode.height - back.getGlobalBounds().height) / 2
	);
	// BackGround


	// Camera
	sf::View view = mainWindow.getDefaultView();
	float currentZoom = 1.0f;
	const float zoomSpeed = 0.1f;
	const float moveSpeed = 500.0f;

	const float minZoom = 0.5f; // Приближаем в 2 раза макс
	const float maxZoom = 2.0f; // Отдаляем в 2 раза макс

	float scale_X = desktopMode.width / place.getSize().x;
	float scale_Y = desktopMode.height / place.getSize().y;

	currentZoom = std::min(scale_X, scale_Y);
	currentZoom = std::max(minZoom, std::min(currentZoom, maxZoom));

	view.zoom(1.0f / currentZoom);
	view.setCenter(place.getSize().x / 2, place.getSize().y / 2);
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

		for (auto ent : ultimateData->entityList) 
		{
			Entity* curr = ent.second;
			if(curr->getType() == Entities::ANT) 
			{
			
			ultimateData->MoveEntity(ent.first);

			}
		}
		mainWindow.draw(back);
		start->DrawMainScene_sfml(mainWindow);
		mainWindow.display();
	}


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





