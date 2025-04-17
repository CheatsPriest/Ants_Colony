#include "InfoSpace.h"
#include "SFMLWindow.h"
#include "stdlib.h"
#include <ctime>
#include <cmath>
#include <iostream>
#include <cstdlib>

#define PI 3.14159265f
static sf::RectangleShape rect;

int cell_size;
int draw_x, draw_y;

unsigned int work_id;
Entity* cur;



Window_sfml::Window_sfml(InfoSpace* data_p, sf::RenderWindow* window)
{
    data = data_p;
    mainWindow = window;
}

void Window_sfml::DrawMaggot_sfml(int x, int y)
{

    

    static sf::Texture texture;
    static bool isTextureLoaded = false;
    static bool textureLoadFailed = false;
    static sf::Sprite sprite;

    if (!isTextureLoaded && !textureLoadFailed)
    {
        if (!texture.loadFromFile("images/maggot.png"))
            textureLoadFailed = true;
        else
            isTextureLoaded = true;
    }

    if (isTextureLoaded)
    {
        sprite.setTexture(texture);

        const float size = data->cell_size - 2.0f;
        const sf::Vector2u texSize = texture.getSize();

        sprite.setOrigin(texSize.x / 2.f, texSize.y / 2.f);
        sprite.setScale(size / texSize.x * 2, size / texSize.y * 2);
        sprite.setPosition(
            x + 1.f + size / 2.f,
            y + 1.f + size / 2.f
        );

        mainWindow->draw(sprite);
    }
    else
    {
        size = data->cell_size - 2.0f;
        rect.setSize(sf::Vector2f(size, size));


        rect.setPosition(x + 1.f, y + 1.f);

        rect.setFillColor(maggotColor);


        mainWindow->draw(rect);

    }
}

void Window_sfml::DrawQueen_sfml(int x, int y)
{
    

    static sf::Texture texture;
    static bool isTextureLoaded = false;
    static bool textureLoadFailed = false;
    static sf::Sprite sprite;

    if (!isTextureLoaded && !textureLoadFailed)
    {
        if (!texture.loadFromFile("images/queen.png"))
            textureLoadFailed = true;
        else
            isTextureLoaded = true;
    }

    if (isTextureLoaded)
    {
        sprite.setTexture(texture);

        const float size = data->cell_size - 2.0f;
        const sf::Vector2u texSize = texture.getSize();

        sprite.setOrigin(texSize.x / 2.f, texSize.y / 2.f);
        sprite.setScale(size / texSize.x * 2.5f, size / texSize.y * 2.5f);
        sprite.setPosition(
            x + 1.f + size / 2.f,
            y + 1.f + size / 2.f
        );

        mainWindow->draw(sprite);
    }
    else
    {
        size = data->cell_size - 2.0f;
        rect.setSize(sf::Vector2f(size, size));


        rect.setPosition(x + 1.f, y + 1.f);

        rect.setFillColor(queenColor);


        mainWindow->draw(rect);
    }
}

void Window_sfml::DrawNurse_sfml(int x, int y)
{
    
    static sf::Texture texture;
    static bool isTextureLoaded = false;
    static bool textureLoadFailed = false;
    static sf::Sprite sprite;

    if (!isTextureLoaded && !textureLoadFailed)
    {
        if (!texture.loadFromFile("images/nurse.png"))
            textureLoadFailed = true;
        else
            isTextureLoaded = true;
    }

    if (isTextureLoaded)
    {
        sprite.setTexture(texture);

        const float size = data->cell_size - 2.0f;
        const sf::Vector2u texSize = texture.getSize();

        sprite.setOrigin(texSize.x / 2.f, texSize.y / 2.f);
        sprite.setScale(size / texSize.x * 2.5f, size / texSize.y * 2.5f);
        sprite.setPosition(
            x + 1.f + size / 2.f,
            y + 1.f + size / 2.f
        );

        mainWindow->draw(sprite);
    }
    else
    {
        size = data->cell_size - 2.0f;
        rect.setSize(sf::Vector2f(size, size));


        rect.setPosition(x + 1.f, y + 1.f);

        rect.setFillColor(nurseColor);


        mainWindow->draw(rect);
    }
}

void Window_sfml::DrawAphid_sfml(int x, int y)
{
    
    static sf::Texture texture;
    static bool isTextureLoaded = false;
    static bool textureLoadFailed = false;
    static sf::Sprite sprite;

    if (!isTextureLoaded && !textureLoadFailed)
    {
        if (!texture.loadFromFile("images/aphid.png"))
            textureLoadFailed = true;
        else
            isTextureLoaded = true;
    }

    if (isTextureLoaded)
    {
        sprite.setTexture(texture);

        const float size = data->cell_size - 2.0f;
        const sf::Vector2u texSize = texture.getSize();

        sprite.setOrigin(texSize.x / 2.f, texSize.y / 2.f);
        sprite.setScale(size / texSize.x * 2.5f, size / texSize.y * 2.5f);
        sprite.setPosition(
            x + 1.f + size / 2.f,
            y + 1.f + size / 2.f
        );

        mainWindow->draw(sprite);
    }
    else
    {
        size = data->cell_size - 2.0f;
        rect.setSize(sf::Vector2f(size, size));


        rect.setPosition(x + 1.f, y + 1.f);

        rect.setFillColor(aphidColor);


        mainWindow->draw(rect);
    }

}

void Window_sfml::DrawScout_sfml(int x, int y)
{
    static sf::Texture texture;
    static bool isTextureLoaded = false;
    static bool textureLoadFailed = false;
    static sf::Sprite sprite;

    if (!isTextureLoaded && !textureLoadFailed)
    {
        if (!texture.loadFromFile("images/scout.png"))
            textureLoadFailed = true;
        else
            isTextureLoaded = true;
    }

    if (isTextureLoaded)
    {
        // Убираем static для спрайта! Важно для индивидуального вращения

        sprite.setTexture(texture);

        const float size = data->cell_size - 2.0f;
        const sf::Vector2u texSize = texture.getSize();

        sprite.setOrigin(texSize.x / 2.f, texSize.y / 2.f);
        sprite.setScale(size / texSize.x * 2.5f, size / texSize.y * 2.5f);
        sprite.setPosition(
            x + 1.f + size / 2.f,
            y + 1.f + size / 2.f
        );

        mainWindow->draw(sprite);
    }
    else 
    {
        const float size = data->cell_size - 2.0f;
        rect.setSize(sf::Vector2f(size, size));
        rect.setPosition(x + 1.f, y + 1.f);
        rect.setFillColor(maggotColor);
        mainWindow->draw(rect);
    }

}

void Window_sfml::DrawLadybug_sfml(int x, int y)
{
    static sf::Texture texture;
    static bool isTextureLoaded = false;
    static bool textureLoadFailed = false;
    static sf::Sprite sprite;

    if (!isTextureLoaded && !textureLoadFailed)
    {
        if (!texture.loadFromFile("images/ladybug.png"))
            textureLoadFailed = true;
        else
            isTextureLoaded = true;
    }

    if (isTextureLoaded)
    {
        sprite.setTexture(texture);

        const float size = data->cell_size - 2.0f;
        const sf::Vector2u texSize = texture.getSize();

        sprite.setOrigin(texSize.x / 2.f, texSize.y / 2.f);
        sprite.setScale(size / texSize.x * 2.5f, size / texSize.y * 2.5f);
        sprite.setPosition(
            x + 1.f + size / 2.f,
            y + 1.f + size / 2.f
        );

        mainWindow->draw(sprite);
    }
    else
    {
        size = data->cell_size - 2.0f;
        rect.setSize(sf::Vector2f(size, size));


        rect.setPosition(x + 1.f, y + 1.f);

        rect.setFillColor(ladybugColor);


        mainWindow->draw(rect);
    }

}

void Window_sfml::DrawWorker_sfml(int x, int y)
{
    
    static sf::Texture texture;
    static bool isTextureLoaded = false;
    static bool textureLoadFailed = false;
    static sf::Sprite sprite;

    if (!isTextureLoaded && !textureLoadFailed)
    {
        if (!texture.loadFromFile("images/worker.png"))
            textureLoadFailed = true;
        else
            isTextureLoaded = true;
    }

    if (isTextureLoaded)
    {
        sprite.setTexture(texture);

        const float size = data->cell_size - 2.0f;
        const sf::Vector2u texSize = texture.getSize();

        sprite.setOrigin(texSize.x / 2.f, texSize.y / 2.f);
        sprite.setScale(size / texSize.x * 2.5f, size / texSize.y * 2.5f);
        sprite.setPosition(
            x + 1.f + size / 2.f,
            y + 1.f + size / 2.f
        );

        mainWindow->draw(sprite);
    }
    else
    {
        size = data->cell_size - 2.0f;
        rect.setSize(sf::Vector2f(size, size));


        rect.setPosition(x + 1.f, y + 1.f);

        rect.setFillColor(workerColor);


        mainWindow->draw(rect);
    }

}

void Window_sfml::DrawSoldier_sfml(int x, int y)
{
    
    static sf::Texture texture;
    static bool isTextureLoaded = false;
    static bool textureLoadFailed = false;
    static sf::Sprite sprite;

    if (!isTextureLoaded && !textureLoadFailed)
    {
        if (!texture.loadFromFile("images/soldier.png"))
            textureLoadFailed = true;
        else
            isTextureLoaded = true;
    }

    if (isTextureLoaded)
    {
        sprite.setTexture(texture);

        const float size = data->cell_size - 2.0f;
        const sf::Vector2u texSize = texture.getSize();

        sprite.setOrigin(texSize.x / 2.f, texSize.y / 2.f);
        sprite.setScale(size / texSize.x * 2.5f, size / texSize.y * 2.5f);
        sprite.setPosition(
            x + 1.f + size / 2.f,
            y + 1.f + size / 2.f
        );

        mainWindow->draw(sprite);
    }
    else
    {
        size = data->cell_size - 2.0f;
        rect.setSize(sf::Vector2f(size, size));


        rect.setPosition(x + 1.f, y + 1.f);

        rect.setFillColor(soldierColor);


        mainWindow->draw(rect);
    }

}

void Window_sfml::DrawFood_sfml(int x, int y)
{
    


    size = data->cell_size - 2.0f;
    rect.setSize(sf::Vector2f(size, size));


    rect.setPosition(x + 1.f, y + 1.f);

    rect.setFillColor(foodColor);


    mainWindow->draw(rect);

}

void Window_sfml::DrawMaterial_sfml(int x, int y)
{
    


    size = data->cell_size - 2.0f;
    rect.setSize(sf::Vector2f(size, size));


    rect.setPosition(x + 1.f, y + 1.f);

    rect.setFillColor(materialColor);


    mainWindow->draw(rect);
    
    return;
}

void Window_sfml::DrawWall_sfml (int x, int y)
{
    


    size = data->cell_size - 2.0f;
    rect.setSize(sf::Vector2f(size, size));


    rect.setPosition(x + 1.f, y + 1.f);

    rect.setFillColor(wallColor);


    mainWindow->draw(rect);

}



void Window_sfml::DrawMainScene_sfml(sf::FloatRect& visibleArea) {

    cell_size = data->cell_size;

    int mapWidth = data->field_size_x; 
    int mapHeight = data->field_size_y;

    int startX = std::max(0, static_cast<int>(visibleArea.left / cell_size));
    int endX = std::min(mapWidth, static_cast<int>((visibleArea.left + visibleArea.width) / cell_size) + 1);
    int startY = std::max(0, static_cast<int>(visibleArea.top / cell_size));
    int endY = std::min(mapHeight, static_cast<int>((visibleArea.top + visibleArea.height) / cell_size) + 1);

    static sf::CircleShape circle;
    for (auto cl : data->coloniesList) {
        
        circle.setRadius(cl.second->base_radius * cell_size);
        circle.setPosition((cl.second->base_x -cl.second->base_radius)*cell_size, (cl.second->base_y - cl.second->base_radius ) * cell_size);
        circle.setFillColor({ (sf::Uint8)cl.second->red, (sf::Uint8)cl.second->green, (sf::Uint8)cl.second->blue });
        //circle.set
        mainWindow->draw(circle);

    }


    for (int x = startX; x < endX; x++) {
        for (int y = startY; y < endY; y++) {
            draw_x = x * cell_size;
            draw_y = y * cell_size;

            


            if (data->field->field[x][y][data->z_cam].cWall != 0) {
                DrawWall_sfml(draw_x, draw_y);
            }

            if (data->field->field[x][y][data->z_cam].IDs[0] != 0)
            {

                cur = data->entityList[data->field->field[x][y][data->z_cam].IDs[0]];


                if (cur == NULL) continue;

                if (cur->getType() == Entities::ANT) {
                    Ant* curAnt = (Ant*)(cur->getPtr());

                    if (curAnt->type == 1) {
                        DrawScout_sfml(draw_x, draw_y);   
                    }
                    else if (curAnt->type == 2) {
                        DrawWorker_sfml(draw_x, draw_y);
                    }
                    else if (curAnt->type == 3) {
                        DrawSoldier_sfml(draw_x, draw_y);
                    }
                    else if (curAnt->type == 4) {
                        DrawNurse_sfml(draw_x, draw_y);
                    }
                    else if (curAnt->type == 0) {
                        DrawQueen_sfml(draw_x, draw_y);
                    }

                }
                
                else if (cur->getType() == Entities::FOOD) {
                    Food* curFood = (Food*)(cur->getPtr());
                    DrawFood_sfml(draw_x, draw_y);

                }
                else if (cur->getType() == Entities::MATERIALS) {
                    Materials* curMat = (Materials*)(cur->getPtr());
                    DrawMaterial_sfml(draw_x, draw_y);

                }

                else if (cur->getType() == Entities::INSECT) {
                    Insect* insect = (Insect*)(cur->getPtr());
                    if (insect->type == InsectTypes::APHID) {
                        DrawAphid_sfml(draw_x, draw_y);
                    }
                    else if (insect->type == InsectTypes::LADYBUG) {
                        DrawLadybug_sfml(draw_x, draw_y);
                    }

                }

                else if (cur->getType() == Entities::MAGGOTS) {
                    Maggot* curMat = (Maggot*)(cur->getPtr());
                    DrawMaggot_sfml(draw_x, draw_y);
                }

            }

        }

    }

    Stockpile* curStock;
    for (auto el : data->stockpileList) {
        curStock = el.second;

        if (curStock->type == FOOD_STOCK) {
            for (int i = 0; i < curStock->size_y; i++) {
                for (int j = 0; j < curStock->size_x; j++) {

                    work_id = curStock->stuff[i][j];
                    if (work_id != 0) {
                        cur = data->entityList[work_id];
                        Food* curFood = (Food*)(cur->getPtr());

                        draw_x = curFood->pos_x * cell_size;
                        draw_y = curFood->pos_y * cell_size;
                        DrawFood_sfml(draw_x, draw_y); 
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
                        DrawMaterial_sfml(draw_x, draw_y); 
                    }
                }
            }
        }
        else if (curStock->type == APHID_STOCK) {
            
        }
        else if (curStock->type == MAGGOT_STOCK) {
            data->Hatching(curStock);
            for (int i = 0; i < curStock->size_y; i++) {
                for (int j = 0; j < curStock->size_x; j++) {

                    work_id = curStock->stuff[i][j];
                    if (work_id != 0) {
                        cur = data->entityList[work_id];
                        Maggot* curMat = (Maggot*)(cur->getPtr());

                        draw_x = (curStock->pos_x + i) * cell_size;
                        draw_y = (curStock->pos_y + j) * cell_size;
                        DrawMaggot_sfml(draw_x, draw_y);
                    }
                }
            }
        }

    }
    
}




