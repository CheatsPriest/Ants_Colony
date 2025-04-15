#include "SFMLWindow.h"
#include "stdlib.h"
#include <ctime>
#include <cmath>
#include <iostream>
#include <cstdlib>

int c_x;
int c_y;
int max_x, max_y;
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

    rect.setFillColor(Red); 


    window.draw(rect);
    
}

void Window_sfml::DrawQueen_sfml    (int x, int y, unsigned id, sf::RenderWindow& window)
{
    sf::RectangleShape rect;


    float size = data->cell_size - 2.0f;
    rect.setSize(sf::Vector2f(size, size));


    rect.setPosition(x + 1.f, y + 1.f);

    rect.setFillColor(Red);


    window.draw(rect);

}

void Window_sfml::DrawNurse_sfml    (int x, int y, unsigned id, sf::RenderWindow& window)
{
    sf::RectangleShape rect;


    float size = data->cell_size - 2.0f;
    rect.setSize(sf::Vector2f(size, size));


    rect.setPosition(x + 1.f, y + 1.f);

    rect.setFillColor(Red);


    window.draw(rect);

}

void Window_sfml::DrawScout_sfml    (int x, int y, unsigned id, sf::RenderWindow& window)
{
    sf::RectangleShape rect;


    float size = data->cell_size - 2.0f;
    rect.setSize(sf::Vector2f(size, size));


    rect.setPosition(x + 1.f, y + 1.f);

    rect.setFillColor(Red);


    window.draw(rect);

}

void Window_sfml::DrawWorker_sfml   (int x, int y, unsigned id, sf::RenderWindow& window)
{
    sf::RectangleShape rect;


    float size = data->cell_size - 2.0f;
    rect.setSize(sf::Vector2f(size, size));


    rect.setPosition(x + 1.f, y + 1.f);

    rect.setFillColor(Red);


    window.draw(rect);

}

void Window_sfml::DrawSoldier_sfml  (int x, int y, unsigned id, sf::RenderWindow& window)
{
    sf::RectangleShape rect;


    float size = data->cell_size - 2.0f;
    rect.setSize(sf::Vector2f(size, size));


    rect.setPosition(x + 1.f, y + 1.f);

    rect.setFillColor(Red);


    window.draw(rect);

}

void Window_sfml::DrawFood_sfml     (int x, int y, sf::RenderWindow& window)
{
    sf::RectangleShape rect;


    float size = data->cell_size - 2.0f;
    rect.setSize(sf::Vector2f(size, size));


    rect.setPosition(x + 1.f, y + 1.f);

    rect.setFillColor(Green);


    window.draw(rect);

}

void Window_sfml::DrawMaterial_sfml (int x, int y, sf::RenderWindow& window)
{
    sf::RectangleShape rect;


    float size = data->cell_size - 2.0f;
    rect.setSize(sf::Vector2f(size, size));


    rect.setPosition(x + 1.f, y + 1.f);

    rect.setFillColor(Green);


    window.draw(rect);

}

void Window_sfml::DrawWall_sfml     (int x, int y, sf::RenderWindow& window)
{
    sf::RectangleShape rect;


    float size = data->cell_size - 2.0f;
    rect.setSize(sf::Vector2f(size, size));


    rect.setPosition(x + 1.f, y + 1.f);

    rect.setFillColor(White);


    window.draw(rect);

}

bool Window_sfml::DrawPlace_sfml    (int x, int y, sf::RenderWindow& window)
{
    sf::Texture place;
    if (!place.loadFromFile("X://Repositories/Ants_Colony/images/back.JPG")) {
        return EXIT_FAILURE;
    }

    sf::Sprite backGround(place);
    float targetSize = data->cell_size - 2.0f; 

    // �������� �������� ������ ��������
    sf::Vector2u textureSize = place.getSize();
    float scaleX = targetSize / textureSize.x;
    float scaleY = targetSize / textureSize.y;
    backGround.setScale(scaleX, scaleY);

    // ������� � ������ �������� (���� x � y ��� � ��������)
    backGround.setPosition(x + 1.f, y + 1.f);

    window.draw(backGround);
}


void Window_sfml::DrawMainScene_sfml(sf::RenderWindow& mainWindow) {

    cell_size = data->cell_size;
    c_x = data->x_cam / cell_size;
    c_y = data->y_cam / cell_size;

    max_x = c_x + data->main_window_wide / data->cell_size;
    max_y = c_y + data->main_window_hight / data->cell_size;


        
    for (int x = c_x; x < max_x; x++) {
        for (int y = c_y; y < max_y; y++) {
            draw_x = (x - c_x) * cell_size;
            draw_y = (y - c_y) * cell_size;

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

                        draw_x = (curFood->pos_x - c_x) * cell_size;
                        draw_y = (curFood->pos_y - c_y) * cell_size;
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

                        draw_x = (curMat->pos_x - c_x) * cell_size;
                        draw_y = (curMat->pos_y - c_y) * cell_size;
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

                        draw_x = (curStock->pos_x + i - c_x) * cell_size;
                        draw_y = (curStock->pos_y + j - c_y) * cell_size;
                        DrawMaggot_sfml(draw_x, draw_y, work_id, mainWindow);
                    }
                }
            }
        }
    }
    
}



bool Window_sfml::isLoaded(sf::Texture scout_texture,   sf::Texture worker_texture,
                           sf::Texture soldier_texture, sf::Texture queen_texture, 
                           sf::Texture nurse_texture,   sf::Texture maggot_texture)
{
    if (!scout_texture.loadFromFile("images/ant.png") || !worker_texture.loadFromFile("images/ant.png") ||
        !soldier_texture.loadFromFile("images/ant.png") || !queen_texture.loadFromFile("images/ant.png") ||
        !nurse_texture.loadFromFile("images/ant.png") || !maggot_texture.loadFromFile("images/ant.png"))
        return EXIT_FAILURE;

}


