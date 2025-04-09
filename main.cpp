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
//	//����� ��������� Entity
//	thread ProcessingEntity(processingEntities);
//	//����� ���������
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
	// �������� ����
	sf::RenderWindow window(sf::VideoMode(800, 600), "Zoom with Texture Switch");
	sf::Clock clock;
	// �������� �������
	sf::Texture antTexture, subObjTexture;
	if (!antTexture.loadFromFile("X://ant.png") ||
		!subObjTexture.loadFromFile("X://antFace.png"))
	{
		return EXIT_FAILURE; // �������� �������� �������
	}


	int cell = 1; // +- 0.1



	// �������� �������     
	sf::Sprite object(antTexture);
	object.setPosition(300, 200); // ������� �� ������ ������

	// ��������� ������
	sf::View view = window.getDefaultView();

	float zoomLevel = 1.0f; // ������� ������� ���� (1.0 = 100%)
	const float cameraSpeed = 200.0f; // �������� � ��������/���

	// ������ ����� �������
	const float FAR_ZOOM = 2.0f;  // 50% ���������
	const float NEAR_ZOOM = 1.0f; // 100% ���������

	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			// ��������� ������
			if (event.type == sf::Event::MouseWheelScrolled)
			{
				// ����������� (H)
				if (event.mouseWheelScroll.delta > 0)
				{
					view.zoom(0.9f); // ��������� ������ ����
					zoomLevel *= 0.9f;
				}
				// ��������� (U)
				else if (event.mouseWheelScroll.delta < 0)
				{
					view.zoom(1.1f); // ����������� ������ ����
					zoomLevel *= 1.1f;
				}
			}
		}

		// �������� ������
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			view.move(0, -cameraSpeed * deltaTime);


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			view.move(0, cameraSpeed * deltaTime);


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			view.move(-cameraSpeed * deltaTime, 0);


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			view.move(cameraSpeed * deltaTime, 0);

		// �������� ������ ���� � ����� ��������
		if (zoomLevel >= FAR_ZOOM)
		{
			object.setTexture(subObjTexture);
		}
		else
		{
			object.setTexture(antTexture);
		}

		// ���������� ������
		window.setView(view);

		// ���������
		window.setView(view);
		window.clear();
		window.draw(object);
		window.display();
	}

	return 0;
}
