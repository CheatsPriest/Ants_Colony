#ifndef SFML_H
#define SFML_H
#include "SFML/Graphics.hpp"
#include "InfoSpace.h"
using namespace std;



class Window_sfml {
public:

    Window_sfml(InfoSpace* data_p, sf::RenderWindow* window);
    
    void DrawMainScene_sfml (sf::FloatRect& visibleArea); 

private:

    int wide = 0, hight = 0;
    
    InfoSpace* data;
   

    void DrawScout_sfml     (int x, int y);
    void DrawWorker_sfml    (int x, int y);
    void DrawSoldier_sfml   (int x, int y);
    void DrawQueen_sfml     (int x, int y);
    void DrawNurse_sfml     (int x, int y);
    void DrawMaggot_sfml    (int x, int y);
    void DrawAphid_sfml     (int x, int y);
    void DrawLadybug_sfml   (int x, int y);
    void DrawBeer           (int x, int y);
    void DrawWall_sfml      (int x, int y);
    void DrawFood_sfml      (int x, int y);
    void DrawMaterial_sfml  (int x, int y);

    sf::Color scoutColor    =   sf::Color(0, 71, 171);
    sf::Color aphidColor    =   sf::Color(93, 96, 90);
    sf::Color workerColor   =   sf::Color(245, 245, 245);
    sf::Color wallColor     =   sf::Color(76, 60, 204);
    sf::Color soldierColor  =   sf::Color(255, 36, 0);
    sf::Color queenColor    =   sf::Color(255, 215, 0);
    sf::Color nurseColor    =   sf::Color(241, 156, 187);
    sf::Color maggotColor   =   sf::Color(139, 0, 255);
    sf::Color foodColor     =   sf::Color(0, 255, 127);
    sf::Color materialColor =   sf::Color(152, 118, 84);
    sf::Color ladybugColor  =   sf::Color(255, 79, 0);

    Field* field = { };

    sf::RenderWindow* mainWindow;

   

    float size;
};

#endif SFML_H