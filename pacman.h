#pragma once
#include <SFML/Graphics.hpp>

struct Field;

enum struct Direction {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Packman {
    sf::ConvexShape topShape;
    sf::ConvexShape bottomShape;
    Direction direction;
    unsigned eatenCookies;
    sf::Vector2f position; 
    float orientationDegrees; 
    float animationPhase; 
};

void initializePackman(Packman& packman);
void updatePackman(Packman& packman, float elapsedTime, Field& field);
void drawPackman(sf::RenderWindow& window, const Packman& packman);
sf::FloatRect getPackmanBounds(const Packman& packman);
