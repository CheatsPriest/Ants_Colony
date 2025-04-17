
//#include "includes.h"
//#include "ImGuiTail.h"
//#include "InfoSpace.h"
//#include "SFMLWindow.h"
//#include "Entity.h";
//#include "Collector.h"
//#include "unordered_map"
//#include <thread>
//#include <conio.h>
//#include <random>
//#include <Windows.h>
//#include "SFML/Graphics.hpp"
//#include <cstdlib>
//#include <ctime>
//#include <cmath>
//#include <stdlib.h>
//#include <iostream>
//#define NOMINMAX

//InfoSpace* ultimateData = new InfoSpace;


#include "SFML/Graphics.hpp"
#include <iostream>


void processingEntities() 
{

	sf::RenderWindow window(sf::VideoMode(1920, 1440), "Zoom with Texture Switch");
	sf::Texture antTexture;
	if (!antTexture.loadFromFile("X://ant.png"))
	{
		std::cout << "Trash" << "\n";
		window.close();
		return;
	}
	
	sf::Sprite object(antTexture);
	object.setPosition(0, 0); 

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(object);
		window.display();
	}

	/*while (mainWindow.isOpen())
	{
		sf::Event event;

		while (mainWindow.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed) ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			{
				mainWindow.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space && isPaused) 
					isPaused = false;
				else if (event.key.code == sf::Keyboard::Space && !isPaused) 
					isPaused = true;
			}

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

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1)
			{
				view.setCenter(start_x * ultimateData->cell_size + 100, start_y * ultimateData->cell_size + 100);
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2)
			{
				view.setCenter(start_x1 * ultimateData->cell_size + 100, start_y1 * ultimateData->cell_size + 100);
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

		view.move(movement / currentZoom);
		mainWindow.setView(view);

		if (!isPaused)
		{
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
				else if (curr && curr->getType() == Entities::INSECT) 
				{
					ultimateData->MoveInsect(ent.first);
				}
			}
		}

		sf::Vector2f viewCenter = view.getCenter();
		sf::Vector2f viewHalfSize = view.getSize() / 2.0f;

		sf::FloatRect visibleArea(
			viewCenter.x - viewHalfSize.x,
			viewCenter.y - viewHalfSize.y,
			view.getSize().x,
			view.getSize().y
		);

		mainWindow.clear();
		start->DrawMainScene_sfml(visibleArea);
	
		mainWindow.display();
	}*/
}



int main() {
	//thread ProcessingEntity(processingEntities);

	//ProcessingEntity.join();
    processingEntities();
	return 0;
}
