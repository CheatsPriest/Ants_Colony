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
	/*for (int i = 0; i < 100; i++) {
		ultimateData->CreateEntity(rand() % 100 + 50, rand() % 100 + 50,5);
	}*/

	
	
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
	while (ultimateData->mainLoop) {
		for (auto ent : ultimateData->entityList) {
			Entity* curr = ent.second;
			if(curr->getType() == Entities::ANT) {
				
				ultimateData->MoveEntity(ent.first);


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


//int main() {
//	
//	//поток обработки Entity
//	thread ProcessingEntity(processingEntities);
//	//поток отрисовки
//	//thread Drow(draw);
//	
//
//
//	ProcessingEntity.join();
//	//Drow.join();
//	return 0;
//}
//InfoSpace* ultimateData = new InfoSpace;


#include "SFML/Graphics.hpp"

int main()
{
	// Создание окна
	sf::RenderWindow window(sf::VideoMode(800, 600), "Zoom with Texture Switch");
	sf::Clock clock;
	// Загрузка текстур
	sf::Texture antTexture, subObjTexture;
	if (!antTexture.loadFromFile("X://ant.png") ||
		!subObjTexture.loadFromFile("X://antFace.png"))
	{
		return EXIT_FAILURE; // Проверка загрузки текстур
	}


	int cell = 1; // +- 0.1



	// Создание спрайта     
	sf::Sprite object(antTexture);
	object.setPosition(300, 200); // Позиция по центру экрана

	// Настройка камеры
	sf::View view = window.getDefaultView();

	float zoomLevel = 1.0f; // Текущий уровень зума (1.0 = 100%)
	const float cameraSpeed = 200.0f; // Скорость в пикселях/сек

	// Пороги смены текстур
	const float FAR_ZOOM = 2.0f;  // 50% видимости
	const float NEAR_ZOOM = 1.0f; // 100% видимости

	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			// Обработка клавиш
			if (event.type == sf::Event::MouseWheelScrolled)
			{
				// Приближение (H)
				if (event.mouseWheelScroll.delta > 0)
				{
					view.zoom(0.9f); // Уменьшаем размер вида
					zoomLevel *= 0.9f;
				}
				// Отдаление (U)
				else if (event.mouseWheelScroll.delta < 0)
				{
					view.zoom(1.1f); // Увеличиваем размер вида
					zoomLevel *= 1.1f;
				}
			}
		}

		// Движение камеры
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			view.move(0, -cameraSpeed * deltaTime);


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			view.move(0, cameraSpeed * deltaTime);


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			view.move(-cameraSpeed * deltaTime, 0);


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			view.move(cameraSpeed * deltaTime, 0);

		// Проверка уровня зума и смена текстуры
		if (zoomLevel >= FAR_ZOOM)
		{
			object.setTexture(subObjTexture);
		}
		else
		{
			object.setTexture(antTexture);
		}

		// Обновление камеры
		window.setView(view);

		// Отрисовка
		window.setView(view);
		window.clear();
		window.draw(object);
		window.display();
	}

	return 0;
}
