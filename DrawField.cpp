
#include "ImGuiTail.h"
int c_x;
int c_y;
int max_x, max_y;
int cell_size;
int draw_x, draw_y;

unsigned int work_id;


Entity* cur;

void Window::DrawScout(int x, int y, unsigned int id) {
    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x + 1.f, y + 1.f), ImVec2(x + data->cell_size - 1.0f, y + data->cell_size - 1.0f), Blue, 0.1f, 0);
    ImGui::GetBackgroundDrawList()->AddText(ImVec2(x + 1.f, y + 1.f), Black, "R");
    ImGui::GetBackgroundDrawList()->AddText(ImVec2(x + 1.f, y + 11.f), Black, std::to_string((unsigned int)id).c_str());
}
void Window::DrawWorker(int x, int y, unsigned int id) {
    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x + 1.f, y + 1.f), ImVec2(x + data->cell_size - 1.0f, y + data->cell_size - 1.0f), White, 0.1f, 0);
    ImGui::GetBackgroundDrawList()->AddText(ImVec2(x + 1.f, y + 1.f), Black, "W");
    ImGui::GetBackgroundDrawList()->AddText(ImVec2(x + 1.f, y + 11.f), Black, std::to_string((unsigned int)id).c_str());
}
void Window::DrawSoldier(int x, int y, unsigned int id) {
    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x + 1.f, y + 1.f), ImVec2(x + data->cell_size - 1.0f, y + data->cell_size - 1.0f), Red, 0.1f, 0);
    ImGui::GetBackgroundDrawList()->AddText(ImVec2(x + 1.f, y + 1.f), Black, "S");
    ImGui::GetBackgroundDrawList()->AddText(ImVec2(x + 1.f, y + 11.f), Black, std::to_string((unsigned int)id).c_str());
}
void Window::DrawFood(int x, int y, unsigned int id) {
    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x + 1.f, y + 1.f), ImVec2(x + data->cell_size - 1.0f, y + data->cell_size - 1.0f), Green, 0.1f, 0);
   // ImGui::GetBackgroundDrawList()->AddText(ImVec2(x + 1.f, y + 1.f), Black, "F");
   // ImGui::GetBackgroundDrawList()->AddText(ImVec2(x + 1.f, y + 11.f), Black, std::to_string((unsigned int)id).c_str());
}
void Window::DrawMaterial(int x, int y, unsigned int id) {
    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x + 1.f, y + 1.f), ImVec2(x + data->cell_size - 1.0f, y + data->cell_size - 1.0f), Brown, 0.1f, 0);
    // ImGui::GetBackgroundDrawList()->AddText(ImVec2(x + 1.f, y + 1.f), Black, "F");
    // ImGui::GetBackgroundDrawList()->AddText(ImVec2(x + 1.f, y + 11.f), Black, std::to_string((unsigned int)id).c_str());
}

void Window::DrawMainScene() {

    

    ImGui::SetNextWindowSize(ImVec2(data->main_window_wide, data->main_window_hight));
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1, 1, 1, 0.4));

    cell_size = data->cell_size;
    c_x = data->x_cam/cell_size;
    c_y = data->y_cam / cell_size;
    
    max_x = c_x + data->main_window_wide / cell_size;
    max_y = c_y + data->main_window_hight / cell_size;
    
    if (ImGui::Begin("Main Scene", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
    {
        //for (int x = 0; x < data->field_size_x; x++) {
        //    for (int y = 0; y < data->field_size_y; y++){//Неоптимизированно
        for (int x = c_x; x < max_x; x++) {
            for (int y = c_y; y < max_y; y++) {
                draw_x = (x - c_x) * cell_size;
                draw_y = (y - c_y) * cell_size;

                //ImGui::GetBackgroundDrawList()->AddRect(ImVec2(draw_x, draw_y), ImVec2(draw_x + cell_size, draw_y + cell_size), Green, 0.1f, 0, 1.0f);
                //ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(draw_x, draw_y), ImVec2(draw_x + cell_size, draw_y + cell_size), Green, 0.1f, 0);
                if (data->field->field[x][y][data->z_cam].cWall != 0) {
                    //cout << 1 << endl;
                    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(draw_x + 1.f, draw_y + 1.f), ImVec2(draw_x + cell_size - 1.0f, draw_y + cell_size - 1.0f), Purple, 0.1f, 0);
                }
                if (field->field[x][y][data->z_cam].IDs[0] != 0) {

                    cur = data->entityList[field->field[x][y][data->z_cam].IDs[0]];
                    if (cur == NULL) continue;
                    if (cur->getType() == Entities::ANT) {
                        Ant* curAnt = (Ant*)(cur->getPtr());
                        
                        //ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(draw_x +1.f, draw_y + 1.f), ImVec2(draw_x + cell_size-1.0f, draw_y + cell_size-1.0f), Brown, 0.1f, 0);
                        
                        if (data->draw_debug_move_lines) {
                   
                            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(draw_x + cell_size / 2, draw_y + cell_size / 2), ImVec2((curAnt->aim.first - c_x) * cell_size+cell_size/2, (curAnt->aim.second - c_y) * cell_size+cell_size/2), Red, 1.f);
                            ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(draw_x + cell_size / 2, draw_y + cell_size / 2), 3.f, Red);
                            
                            
                        }

                        if (curAnt->type == 1) {
                            DrawScout(draw_x, draw_y, field->field[x][y][data->z_cam].IDs[0]);
                        }
                        else if (curAnt->type == 2) {
                            DrawWorker(draw_x, draw_y, field->field[x][y][data->z_cam].IDs[0]);
                        }
                        else if (curAnt->type == 3) {
                            DrawSoldier(draw_x, draw_y, field->field[x][y][data->z_cam].IDs[0]);
                        }
                        else if (curAnt->type == 0) {
                            ImGui::GetBackgroundDrawList()->AddText(ImVec2(draw_x + 1.f, draw_y + 1.f), Black, "Q");
                        }
                        else if (curAnt->type == 4) {//костыль
                            ImGui::GetBackgroundDrawList()->AddText(ImVec2(draw_x + 1.f, draw_y + 1.f), Black, "F");
                        }
                        else if (curAnt->type == 5) {//костыль
                            ImGui::GetBackgroundDrawList()->AddText(ImVec2(draw_x + 1.f, draw_y + 1.f), Black, "E");
                        }
                        //ImGui::GetBackgroundDrawList()->AddText(ImVec2(draw_x + 1.f, draw_y + 11.f), Black, std::to_string((unsigned int)field->field[x][y][data->z_cam].IDs[0]).c_str());
                        
                    }
                    else if (cur->getType() == Entities::FOOD) {
                        Food* curFood = (Food*)(cur->getPtr());
                        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(draw_x + 1.f, draw_y + 1.f), ImVec2(draw_x + cell_size - 1.0f, draw_y + cell_size - 1.0f), Green, 0.1f, 0);
                       
                    }
                    else if (cur->getType() == Entities::MATERIALS) {
                        Materials* curMat = (Materials*)(cur->getPtr());
                        DrawMaterial(draw_x, draw_y, field->field[x][y][data->z_cam].IDs[0]);

                    }
                   
                }

            }

        }
        //ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(100, 100), ImVec2(200, 200), Green, 0.f, 0);

        Stockpile* curStock;
        for (auto el : data->stockpileList) {
            curStock = el.second;
            //cout << curStock->pos_x << " " << curStock->pos_x + curStock->size_x << endl;
            ImGui::GetBackgroundDrawList()->AddRect(ImVec2((curStock->pos_x)* cell_size - data->x_cam, (curStock->pos_y)* cell_size - data->y_cam), ImVec2((curStock->pos_x + curStock->size_x)* cell_size - data->x_cam, (curStock->pos_y + curStock->size_y)* cell_size - data->y_cam), Red, 0.1f, 0, 2.0f);
            if (curStock->type == FOOD_STOCK) {
                for (int i = 0; i < curStock->size_y; i++) {
                    for (int j = 0; j < curStock->size_x; j++) {

                        work_id = curStock->stuff[i][j];
                        if (work_id != 0) {
                            cur = data->entityList[work_id];
                            Food* curFood = (Food*)(cur->getPtr());

                            draw_x = (curFood->pos_x - c_x) * cell_size;
                            draw_y = (curFood->pos_y - c_y) * cell_size;
                            DrawFood(draw_x, draw_y, work_id);
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
                            DrawMaterial(draw_x, draw_y, work_id);
                        }
                    }
                }
            }
        }

    }ImGui::End();

    ImGui::PopStyleColor();
}