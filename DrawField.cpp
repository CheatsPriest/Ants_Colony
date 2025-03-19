
#include "ImGuiTail.h"
int c_x;
int c_y;
int max_x, max_y;
int cell_size;


ImColor Green = ImColor(0.2f, 0.6f, 0.2f);
ImColor Brown = ImColor(0.8f, 0.4f, 0.1f);
ImColor Black = ImColor(0.f, 0.f, 0.f);
Entity* cur;

void DrawAnt() {

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
        
        for (int x = c_x; x < max_x; x++) {
            for (int y = c_y; y < max_y; y++) {
                ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x*cell_size, y* cell_size), ImVec2(x * cell_size+cell_size, y * cell_size + cell_size), Green, 0.1f,0,1.0f);
                if (field->field[x][y][data->z_cam].IDs[0] != 0) {

                    cur = data->entityList[field->field[x][y][data->z_cam].IDs[0]];

                    if (cur->getType() == Entities::ANT) {
                        Ant* curAnt = (Ant*)(cur->getPtr());
                        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x * cell_size+1.f, y * cell_size + 1.f), ImVec2(x * cell_size + cell_size-1.0f, y * cell_size + cell_size-1.0f), Brown, 0.1f, 0);

                        if (curAnt->type == 1) {
                            ImGui::GetBackgroundDrawList()->AddText(ImVec2(x * cell_size + 1.f, y * cell_size + 1.f), Black, "S");
                        }
                        else if (curAnt->type == 2) {
                            ImGui::GetBackgroundDrawList()->AddText(ImVec2(x * cell_size + 1.f, y * cell_size + 1.f), Black, "W");
                        }
                        else if (curAnt->type == 3) {
                            ImGui::GetBackgroundDrawList()->AddText(ImVec2(x * cell_size + 1.f, y * cell_size + 1.f), Black, "S");
                        }
                        else if (curAnt->type == 0) {
                            ImGui::GetBackgroundDrawList()->AddText(ImVec2(x * cell_size + 1.f, y * cell_size + 1.f), Black, "Q");
                        }
                    }


                }
            }
        }
        //ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(100, 100), ImVec2(200, 200), Green, 0.f, 0);
    }ImGui::End();

    ImGui::PopStyleColor();
}