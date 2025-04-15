#pragma once
#include "SFML/Graphics.hpp"
#include "InfoSpace.h"
using namespace std;

static sf::Color Green      = sf::Color::Green;
static sf::Color Blue       = sf::Color(0.4f, 0.4f, 0.9f);
static sf::Color WhiteBlue  = sf::Color(0.4f, 0.1f, 0.9f);

static sf::Color Yellow     = sf::Color(0.8f, 0.8f, 0.1f);

static sf::Color Pink       = sf::Color(0.9f, 0.2f, 0.9f);

static sf::Color Brown      = sf::Color(0.8f, 0.4f, 0.1f);

static sf::Color Purple     = sf::Color(0.8f, 0.1f, 0.9f);

static sf::Color Black      = sf::Color(0.01f, 0.01f, 0.01f);
static sf::Color White      = sf::Color::White;
static sf::Color Red        = sf::Color::Red;

class Window_sfml {
public:

    Window_sfml(InfoSpace* data_p);

    void DrawMainScene_sfml (sf::RenderWindow& mainWindow); 

private:

    int wide, hight;
    

    

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

    Field* field;



};

