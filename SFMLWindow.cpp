#include "SFMLWindow.h"
#include "stdlib.h"
int c_x;
int c_y;
int max_x, max_y;
int cell_size;
int draw_x, draw_y;

unsigned int work_id;
Entity* cur;

// ???
Window_sfml::Window_sfml(InfoSpace* data_p)
{
    data = data_p;
}
// ???

void Window_sfml::DrawMaggot_sfml   (int x, int y, unsigned id, sf::RenderWindow& window)
{

    sf::RectangleShape rect;

    
    float size = data->cell_size - 2.0f;
    rect.setSize(sf::Vector2f(size, size));
    

    rect.setPosition(x + 1.f, y + 1.f); 

    rect.setFillColor(Red); 


    window.draw(rect);

    //// текст
    //sf::Text qText;
    //qText.setFont(font); // Еще шрифт подгрузить 
    //qText.setString("Q");
    //qText.setCharacterSize(12); 
    //qText.setFillColor(sf::Color::Black);
    //qText.setPosition(x + 1.f, y + 1.f);
    //window.draw(qText);

    //// id
    //sf::Text idText;
    //idText.setFont(font);
    //idText.setString(std::to_string(id));
    //idText.setCharacterSize(12); 
    //idText.setFillColor(sf::Color::Black);
    //idText.setPosition(x + 1.f, y + 11.f); 
    //window.draw(idText);
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

void Window_sfml::DrawMainScene_sfml() {


    // ?

    /*ImGui::SetNextWindowSize(ImVec2(data->main_window_wide, data->main_window_hight));
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1, 1, 1, 0.4));*/
    
    // ?
    cell_size = data->cell_size;
    c_x = data->x_cam / cell_size;
    c_y = data->y_cam / cell_size;

    max_x = c_x + data->main_window_wide / cell_size;
    max_y = c_y + data->main_window_hight / cell_size;

    sf::RenderWindow mainWindow(sf::VideoMode(data->main_window_wide, data->main_window_hight), "Ant Colony");


    while (mainWindow.isOpen())
    {
        for (int x = c_x; x < max_x; x++) {
            for (int y = c_y; y < max_y; y++) {
                draw_x = (x - c_x) * cell_size;
                draw_y = (y - c_y) * cell_size;

                
                if (data->field->field[x][y][data->z_cam].cWall != 0) {
                    DrawWall_sfml(draw_x, draw_y, mainWindow);
                }
                if (field->field[x][y][data->z_cam].IDs[0] != 0) {

                    cur = data->entityList[field->field[x][y][data->z_cam].IDs[0]];
                    if (cur == NULL) continue;
                    if (cur->getType() == Entities::ANT) {
                        Ant* curAnt = (Ant*)(cur->getPtr());
                        // Отрисовка векторов направления 

                        /*if (data->draw_debug_move_lines and curAnt->inventary != 0 and data->entityList[curAnt->inventary]->getType() == MATERIALS) {

                            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(draw_x + cell_size / 2, draw_y + cell_size / 2), ImVec2((curAnt->aim.first - c_x) * cell_size + cell_size / 2, (curAnt->aim.second - c_y) * cell_size + cell_size / 2), Red, 1.f);
                            ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(draw_x + cell_size / 2, draw_y + cell_size / 2), 3.f, Red);


                        }*/

                        if (curAnt->type == 1) {
                            DrawScout_sfml(draw_x, draw_y, field->field[x][y][data->z_cam].IDs[0], mainWindow);
                        }
                        else if (curAnt->type == 2) {
                            DrawWorker_sfml(draw_x, draw_y, field->field[x][y][data->z_cam].IDs[0], mainWindow);
                        }
                        else if (curAnt->type == 3) {
                            DrawSoldier_sfml(draw_x, draw_y, field->field[x][y][data->z_cam].IDs[0], mainWindow);
                        }
                        else if (curAnt->type == 4) {
                            DrawNurse_sfml(draw_x, draw_y, field->field[x][y][data->z_cam].IDs[0], mainWindow);
                        }
                        else if (curAnt->type == 0) {
                            DrawQueen_sfml(draw_x, draw_y, field->field[x][y][data->z_cam].IDs[0], mainWindow);
                        }

                    }
                    else if (cur->getType() == Entities::FOOD) {
                        Food* curFood = (Food*)(cur->getPtr());
                        DrawFood_sfml(draw_x, draw_y, mainWindow);

                    }
                    else if (cur->getType() == Entities::MATERIALS) {
                        Materials* curMat = (Materials*)(cur->getPtr());
                        DrawMaterial_sfml(draw_x, draw_y, mainWindow);
                        //DrawMaterial_sfml(draw_x, draw_y, field->field[x][y][data->z_cam].IDs[0]); // С текстом

                    }
                    else if (cur->getType() == Entities::MAGGOTS) {
                        Maggot* curMat = (Maggot*)(cur->getPtr());
                        DrawMaggot_sfml(draw_x, draw_y, field->field[x][y][data->z_cam].IDs[0], mainWindow);
                    }

                }

            }

        }

        Stockpile* curStock;
        for (auto el : data->stockpileList) {
            curStock = el.second;
            //ImGui::GetBackgroundDrawList()->AddRect(ImVec2((curStock->pos_x) * cell_size - data->x_cam, (curStock->pos_y) * cell_size - data->y_cam), ImVec2((curStock->pos_x + curStock->size_x) * cell_size - data->x_cam, (curStock->pos_y + curStock->size_y) * cell_size - data->y_cam), Red, 0.1f, 0, 2.0f);
            // Обводка склада
            if (curStock->type == FOOD_STOCK) {
                for (int i = 0; i < curStock->size_y; i++) {
                    for (int j = 0; j < curStock->size_x; j++) {

                        work_id = curStock->stuff[i][j];
                        if (work_id != 0) {
                            cur = data->entityList[work_id];
                            Food* curFood = (Food*)(cur->getPtr());

                            draw_x = (curFood->pos_x - c_x) * cell_size;
                            draw_y = (curFood->pos_y - c_y) * cell_size;
                            DrawFood_sfml(draw_x, draw_y, mainWindow); // Здесь с текстом (work_id)
                            //DrawFood(draw_x, draw_y, work_id);
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
                            DrawMaterial_sfml(draw_x, draw_y, mainWindow); // Здесь с текстом (work_id)
                            //DrawMaterial(draw_x, draw_y, work_id);
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
                            //DrawMaggot(draw_x, draw_y, work_id);
                        }
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


