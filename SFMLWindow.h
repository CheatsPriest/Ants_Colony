#ifndef SFML_H
#define SFML_H
#include "SFML/Graphics.hpp"
#include "InfoSpace.h"
using namespace std;


class Window_sfml {
public:

    Window_sfml(InfoSpace* data_p);
    void DrawMainScene_sfml (sf::RenderWindow& mainWindow, sf::FloatRect& visibleArea); 

private:

    int wide = 0, hight = 0;
    

    sf::Texture scout_texture, worker_texture, soldier_texture,
        queen_texture, nurse_texture, maggot_texture,
        aphid_texture, ladybug_texutre;
    sf::Texture wall_texture, food_texture, material_texture;



    InfoSpace* data;
   

    void DrawScout_sfml     (int x, int y, unsigned id, sf::RenderWindow& window);
    void DrawWorker_sfml    (int x, int y, unsigned id, sf::RenderWindow& window);
    void DrawSoldier_sfml   (int x, int y, unsigned id, sf::RenderWindow& window);
    void DrawQueen_sfml     (int x, int y, unsigned id, sf::RenderWindow& window);
    void DrawNurse_sfml     (int x, int y, unsigned id, sf::RenderWindow& window);
    void DrawMaggot_sfml    (int x, int y, unsigned id, sf::RenderWindow& window);
    void DrawAphid_sfml     (int x, int y, unsigned id, sf::RenderWindow& window);
    void DrawLadybug_sfml   (int x, int y, unsigned id, sf::RenderWindow& window);

    void DrawWall_sfml      (int x, int y, sf::RenderWindow& window);
    void DrawFood_sfml      (int x, int y, sf::RenderWindow& window);
    void DrawMaterial_sfml  (int x, int y, sf::RenderWindow& window);

    sf::Color scoutColor    =   sf::Color(0, 71, 171);
    sf::Color aphidColor    =   sf::Color(33, 66, 30);
    sf::Color workerColor   =   sf::Color(245, 245, 245);
    sf::Color wallColor     =   sf::Color(76, 60, 24);
    sf::Color soldierColor  =   sf::Color(255, 36, 0);
    sf::Color queenColor    =   sf::Color(255, 215, 0);
    sf::Color nurseColor    =   sf::Color(241, 156, 187);
    sf::Color maggotColor   =   sf::Color(139, 0, 255);
    sf::Color foodColor     =   sf::Color(0, 255, 127);
    sf::Color materialColor =   sf::Color(152, 118, 84);
    sf::Color ladybugColor  =   sf::Color(255, 79, 0);

    Field* field = { };



};

#endif SFML_H