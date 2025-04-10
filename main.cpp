//#include "includes.h"
//#include "ImGuiTail.h"
//#include "Entity.h";
//#include "Collector.h"
//#include "unordered_map"
//#include <thread>
//#include <conio.h>
//#include <random>
//#define NOMINMAX
//#include <Windows.h>
#include "SFML/Graphics.hpp"
#include <cstdlib>
#include <ctime>
#include <cmath>




//InfoSpace* ultimateData = new InfoSpace;


//void processingEntities() {
//	Window* mainWindow = new Window(ultimateData);
//	srand(time(0));
//	ultimateData->CreateStockpile(60, 10, 0, 17, 17, 0, 1);
//	ultimateData->CreateStockpile(60, 60, 0, 17, 17, 1, 1);
//
//	ultimateData->CreateEntityFood(10, 20, 0, 0, 10, 10);
//
//	for (int i = 0; i < 100; i++) {
//		ultimateData->CreateEntityAnt(15, 2 * i, 0, 0, 1,1);
//	}
//	for (int i = 0; i < 50; i++) {
//		ultimateData->CreateEntityAnt(10, 2*i, 0, 0, 2,1);
//	}
//	for (int i = 0; i < 10; i++) {
//		ultimateData->CreateEntityAnt(12, i, 0, 0, 3,1);
//	}
//
//	for (int i = 0; i < 200; i++) {
//		ultimateData->CreateEntityFood(rand() % 100 + 50, rand() % 100 + 50, 0, 0, 2000, 10);
//		ultimateData->CreateEntityMaterial(rand() % 100 + 50, rand() % 100 + 50, 0, 0, 10);
//	}
//	/*for (int i = 0; i < 100; i++) {
//		ultimateData->CreateEntity(rand() % 100 + 50, rand() % 100 + 50,5);
//	}*/
//
//	
//	
//	//ultimateData->entityList.insert({ 3, entity3 });
//
//	for (auto el : ultimateData->entityList) {
//		Entity* curr = el.second;
//		if (curr->getType() == Entities::ANT) {
//			Ant* currAnt = (Ant*)(curr->getPtr());
//			currAnt->info();
//			
//			
//			
//			
//		}
//		else if (curr->getType() == Entities::FOOD) {
//			Food* currFood = (Food*)(curr->getPtr());
//			currFood->info();
//		}
//	}
//	while (ultimateData->mainLoop) {
//		for (auto ent : ultimateData->entityList) {
//			Entity* curr = ent.second;
//			if(curr->getType() == Entities::ANT) {
//				
//				ultimateData->MoveEntity(ent.first);
//
//
//			}
//		}
//
//
//		if (GetAsyncKeyState(VK_LEFT) & 0x8000 != 0)
//		{
//			ultimateData->MoveCam(-1, 0);
//			for (int i = 0; i < 25; i++) {
//				ultimateData->CreateEntityFood(rand() % 100 + 50, rand() % 100 + 50, 0, 0, 20000, 10);
//			}
//		}
//		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000 != 0) {
//			ultimateData->MoveCam(1, 0);
//		}
//		else if (GetAsyncKeyState(VK_UP) & 0x8000 != 0) {
//			ultimateData->MoveCam(0, -1);
//		}
//		else if (GetAsyncKeyState(VK_DOWN) & 0x8000 != 0) {
//			ultimateData->MoveCam(0, 1);
//		}
//
//		mainWindow->NewFrame();
//
//		mainWindow->EndFrame();
//
//
//	}
//	delete mainWindow;
//}
//
//void draw() {
//	
//	Window* mainWindow = new Window(ultimateData);
//
//	
//
//
//	
//
//	while (ultimateData->mainLoop) {
//		
//		if (GetAsyncKeyState(VK_LEFT) & 0x8000 != 0)
//		{
//			ultimateData->MoveCam(-1, 0);
//		}
//		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000 != 0) {
//			ultimateData->MoveCam(1, 0);
//		}
//		else if (GetAsyncKeyState(VK_UP) & 0x8000 != 0) {
//			ultimateData->MoveCam(0, -1);
//		}
//		else if (GetAsyncKeyState(VK_DOWN) & 0x8000 != 0) {
//			ultimateData->MoveCam(0, 1);
//		}
//		
//		mainWindow->NewFrame();
//
//		mainWindow->EndFrame();
//	}
//
//	mainWindow->Cleanup();
//	delete mainWindow;
//}
//
//
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





struct Ant {
    sf::Sprite sprite;
    sf::Vector2f velocity;
};

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    sf::RenderWindow window(sf::VideoMode(1920, 1440), "Zoom with Texture Switch");
    sf::Clock clock;

    // Загрузка текстур
    sf::Texture antTexture, subObjTexture;
    if (!antTexture.loadFromFile("images//ant.png") ||
        !subObjTexture.loadFromFile("images//antFace.png")) {
        return EXIT_FAILURE;
    }

    // Создание объектов
    std::vector<Ant> ants;
    const int NUM_ANTS = 10;
    for (int i = 0; i < NUM_ANTS; ++i) {
        Ant ant;
        ant.sprite.setTexture(antTexture);
        sf::FloatRect bounds = ant.sprite.getLocalBounds();

        // Центрируем начало координат спрайта
        ant.sprite.setOrigin(bounds.width / 2, bounds.height / 2);

        float x = rand() % (1920 - static_cast<int>(bounds.width));
        float y = rand() % (1440 - static_cast<int>(bounds.height));
        ant.sprite.setPosition(x, y);

        float angle = static_cast<float>(rand() % 360) * (3.14159f / 180.f);
        float speed = 100.0f;
        ant.velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
        ants.push_back(ant);
    }

    // Настройка камеры
    sf::View view = window.getDefaultView();
    float zoomLevel = 1.0f;
    const float FAR_ZOOM = 2.0f;
    const float cameraSpeed = 200.0f;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0) {
                    view.zoom(0.9f);
                    zoomLevel *= 0.9f;
                }
                else {
                    view.zoom(1.1f);
                    zoomLevel *= 1.1f;
                }
            }
        }

        // Движение камеры
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) view.move(0, -cameraSpeed * deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) view.move(0, cameraSpeed * deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) view.move(-cameraSpeed * deltaTime, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) view.move(cameraSpeed * deltaTime, 0);

        // Обновление объектов
        for (auto& ant : ants) {
            ant.sprite.move(ant.velocity * deltaTime);
            sf::FloatRect bounds = ant.sprite.getGlobalBounds();

            // Поворот спрайта по направлению движения
            if (ant.velocity.x != 0 || ant.velocity.y != 0) {
                float angle = std::atan2(ant.velocity.y, ant.velocity.x) * (180 / 3.14159f);
                ant.sprite.setRotation(angle + 90); // +90 если текстура изначально смотрит вверх
            }

            // Проверка границ
            if (bounds.left < 0) {
                ant.velocity.x = std::abs(ant.velocity.x);
                ant.sprite.setPosition(bounds.width / 2, ant.sprite.getPosition().y);
            }
            else if (bounds.left + bounds.width > 1920) {
                ant.velocity.x = -std::abs(ant.velocity.x);
                ant.sprite.setPosition(1920 - bounds.width / 2, ant.sprite.getPosition().y);
            }

            if (bounds.top < 0) {
                ant.velocity.y = std::abs(ant.velocity.y);
                ant.sprite.setPosition(ant.sprite.getPosition().x, bounds.height / 2);
            }
            else if (bounds.top + bounds.height > 1440) {
                ant.velocity.y = -std::abs(ant.velocity.y);
                ant.sprite.setPosition(ant.sprite.getPosition().x, 1440 - bounds.height / 2);
            }

            // Смена текстуры
            if (zoomLevel >= FAR_ZOOM) {
                ant.sprite.setTexture(subObjTexture, true);
            }
            else {
                ant.sprite.setTexture(antTexture, true);
            }
        }

        // Отрисовка
        window.setView(view);
        window.clear();
        for (const auto& ant : ants) {
            window.draw(ant.sprite);
        }
        window.display();
    }

    return 0;
}