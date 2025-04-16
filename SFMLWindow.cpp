#include "InfoSpace.h"
#include "SFMLWindow.h"
#include "stdlib.h"
#include <ctime>
#include <cmath>
#include <iostream>
#include <cstdlib>

int cell_size;
int draw_x, draw_y;

unsigned int work_id;
Entity* cur;

Window_sfml::Window_sfml(InfoSpace* data_p)
{
    data = data_p;
}

void Window_sfml::DrawMaggot_sfml   (int x, int y, unsigned id, sf::RenderWindow& window)
{

    sf::RectangleShape rect;

    
    float size = data->cell_size - 2.0f;
    rect.setSize(sf::Vector2f(size, size));
    

    rect.setPosition(x + 1.f, y + 1.f); 

    rect.setFillColor(maggotColor); 


    window.draw(rect);

    
    
}

void Window_sfml::DrawQueen_sfml    (int x, int y, unsigned id, sf::RenderWindow& window)
{
    sf::RectangleShape rect;


    float size = data->cell_size - 2.0f;
    rect.setSize(sf::Vector2f(size, size));


    rect.setPosition(x + 1.f, y + 1.f);

    rect.setFillColor(queenColor);


    window.draw(rect);

}

void Window_sfml::DrawNurse_sfml    (int x, int y, unsigned id, sf::RenderWindow& window)
{
    sf::RectangleShape rect;


    float size = data->cell_size - 2.0f;
    rect.setSize(sf::Vector2f(size, size));


    rect.setPosition(x + 1.f, y + 1.f);

    rect.setFillColor(nurseColor);


    window.draw(rect);

}

void Window_sfml::DrawAphid_sfml    (int x, int y, unsigned id, sf::RenderWindow& window)
{
    sf::RectangleShape rect;


    float size = data->cell_size - 2.0f;
    rect.setSize(sf::Vector2f(size, size));


    rect.setPosition(x + 1.f, y + 1.f);

    rect.setFillColor(aphidColor);


    window.draw(rect);
}

void Window_sfml::DrawScout_sfml    (int x, int y, unsigned id, sf::RenderWindow& window)
{
    sf::RectangleShape rect;


    float size = data->cell_size - 2.0f;
    rect.setSize(sf::Vector2f(size, size));


    rect.setPosition(x + 1.f, y + 1.f);

    rect.setFillColor(scoutColor);


    window.draw(rect);

}

void Window_sfml::DrawLadybug_sfml  (int x, int y, unsigned id, sf::RenderWindow& window)
{
    sf::RectangleShape rect;


    float size = data->cell_size - 2.0f;
    rect.setSize(sf::Vector2f(size, size));


    rect.setPosition(x + 1.f, y + 1.f);

    rect.setFillColor(ladybugColor);


    window.draw(rect);
}

void Window_sfml::DrawWorker_sfml   (int x, int y, unsigned id, sf::RenderWindow& window)
{
    sf::RectangleShape rect;


    float size = data->cell_size - 2.0f;
    rect.setSize(sf::Vector2f(size, size));


    rect.setPosition(x + 1.f, y + 1.f);

    rect.setFillColor(workerColor);


    window.draw(rect);

}

void Window_sfml::DrawSoldier_sfml  (int x, int y, unsigned id, sf::RenderWindow& window)
{
    sf::RectangleShape rect;


    float size = data->cell_size - 2.0f;
    rect.setSize(sf::Vector2f(size, size));


    rect.setPosition(x + 1.f, y + 1.f);

    rect.setFillColor(soldierColor);


    window.draw(rect);

}

void Window_sfml::DrawFood_sfml     (int x, int y, sf::RenderWindow& window)
{
    sf::RectangleShape rect;


    float size = data->cell_size - 2.0f;
    rect.setSize(sf::Vector2f(size, size));


    rect.setPosition(x + 1.f, y + 1.f);

    rect.setFillColor(foodColor);


    window.draw(rect);

}

void Window_sfml::DrawMaterial_sfml (int x, int y, sf::RenderWindow& window)
{
    sf::RectangleShape rect;


    float size = data->cell_size - 2.0f;
    rect.setSize(sf::Vector2f(size, size));


    rect.setPosition(x + 1.f, y + 1.f);

    rect.setFillColor(materialColor);


    window.draw(rect);

}

void Window_sfml::DrawWall_sfml     (int x, int y, sf::RenderWindow& window)
{
    sf::RectangleShape rect;


    float size = data->cell_size - 2.0f;
    rect.setSize(sf::Vector2f(size, size));


    rect.setPosition(x + 1.f, y + 1.f);

    rect.setFillColor(wallColor);


    window.draw(rect);

}



void Window_sfml::DrawMainScene_sfml(sf::RenderWindow& mainWindow, sf::FloatRect& visibleArea) {

    cell_size = data->cell_size;

    int mapWidth = data->field_size_x; 
    int mapHeight = data->field_size_y;

    int startX = std::max(0, static_cast<int>(visibleArea.left / cell_size));
    int endX = std::min(mapWidth, static_cast<int>((visibleArea.left + visibleArea.width) / cell_size) + 1);
    int startY = std::max(0, static_cast<int>(visibleArea.top / cell_size));
    int endY = std::min(mapHeight, static_cast<int>((visibleArea.top + visibleArea.height) / cell_size) + 1);

    for (int x = startX; x < endX; x++) {
        for (int y = startY; y < endY; y++) {
            draw_x = x * cell_size;
            draw_y = y * cell_size;

            if (data->field->field[x][y][data->z_cam].cWall != 0) {
                DrawWall_sfml(draw_x, draw_y, mainWindow);
            }

            if (data->field->field[x][y][data->z_cam].IDs[0] != 0)
            {

                cur = data->entityList[data->field->field[x][y][data->z_cam].IDs[0]];


                if (cur == NULL) continue;
                if (cur->getType() == Entities::ANT) {
                    Ant* curAnt = (Ant*)(cur->getPtr());

                    if (curAnt->type == 1) {
                        DrawScout_sfml(draw_x, draw_y, data->field->field[x][y][data->z_cam].IDs[0], mainWindow);   
                    }
                    else if (curAnt->type == 2) {
                        DrawWorker_sfml(draw_x, draw_y, data->field->field[x][y][data->z_cam].IDs[0], mainWindow);
                    }
                    else if (curAnt->type == 3) {
                        DrawSoldier_sfml(draw_x, draw_y, data->field->field[x][y][data->z_cam].IDs[0], mainWindow);
                    }
                    else if (curAnt->type == 4) {
                        DrawNurse_sfml(draw_x, draw_y, data->field->field[x][y][data->z_cam].IDs[0], mainWindow);
                    }
                    else if (curAnt->type == 0) {
                        DrawQueen_sfml(draw_x, draw_y, data->field->field[x][y][data->z_cam].IDs[0], mainWindow);
                    }

                }
                else if (cur->getType() == Entities::FOOD) {
                    Food* curFood = (Food*)(cur->getPtr());
                    DrawFood_sfml(draw_x, draw_y, mainWindow);

                }
                else if (cur->getType() == Entities::MATERIALS) {
                    Materials* curMat = (Materials*)(cur->getPtr());
                    DrawMaterial_sfml(draw_x, draw_y, mainWindow);

                }

                else if (cur->getType() == Entities::INSECT) {
                    Insect* insect = (Insect*)(cur->getPtr());
                    if (insect->type == InsectTypes::APHID) {
                        DrawAphid_sfml(draw_x, draw_y, data->field->field[x][y][data->z_cam].IDs[0], mainWindow);
                    }
                    else if (insect->type == InsectTypes::LADYBUG) {
                        DrawLadybug_sfml(draw_x, draw_y, data->field->field[x][y][data->z_cam].IDs[0], mainWindow);
                    }

                }

                else if (cur->getType() == Entities::MAGGOTS) {
                    Maggot* curMat = (Maggot*)(cur->getPtr());
                    DrawMaggot_sfml(draw_x, draw_y, data->field->field[x][y][data->z_cam].IDs[0], mainWindow);
                }

            }

        }

    }

    Stockpile* curStock;
    for (auto el : data->stockpileList) {
        curStock = el.second;
        //ImGui::GetBackgroundDrawList()->AddRect(ImVec2((curStock->pos_x) * cell_size - data->x_cam, (curStock->pos_y) * cell_size - data->y_cam), ImVec2((curStock->pos_x + curStock->size_x) * cell_size - data->x_cam, (curStock->pos_y + curStock->size_y) * cell_size - data->y_cam), Red, 0.1f, 0, 2.0f);
        // ������� ������
        if (curStock->type == FOOD_STOCK) {
            for (int i = 0; i < curStock->size_y; i++) {
                for (int j = 0; j < curStock->size_x; j++) {

                    work_id = curStock->stuff[i][j];
                    if (work_id != 0) {
                        cur = data->entityList[work_id];
                        Food* curFood = (Food*)(cur->getPtr());

                        draw_x = curFood->pos_x * cell_size;
                        draw_y = curFood->pos_y * cell_size;
                        DrawFood_sfml(draw_x, draw_y, mainWindow); 
                    }
                }
            }
        }
        else if (curStock->type == MATERIAL_STOCK) {
            for (int i = 0; i < curStock->size_y; i++) {
                for (int j = 0; j < curStock->size_x; j++) {

                    work_id = curStock->stuff[i][j];
                    if (work_id != 0) {
                        cur = data->entityList[work_id];
                        Materials* curMat = (Materials*)(cur->getPtr());

                        draw_x = curMat->pos_x * cell_size;
                        draw_y = curMat->pos_y * cell_size;
                        DrawMaterial_sfml(draw_x, draw_y, mainWindow); 
                    }
                }
            }
        }
        else if (curStock->type == MAGGOT_STOCK) {
            data->Hatching(curStock);
            for (int i = 0; i < curStock->size_y; i++) {
                for (int j = 0; j < curStock->size_x; j++) {

                    work_id = curStock->stuff[i][j];
                    if (work_id != 0) {
                        cur = data->entityList[work_id];
                        Maggot* curMat = (Maggot*)(cur->getPtr());

                        draw_x = curStock->pos_x + i * cell_size;
                        draw_y = curStock->pos_y + j * cell_size;
                        DrawMaggot_sfml(draw_x, draw_y, work_id, mainWindow);
                    }
                }
            }
        }
    }
    
}




