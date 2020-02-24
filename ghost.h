#pragma once
#include <SFML/Graphics.hpp>
#include "pacman.h"

struct Ghost {
    sf::RectangleShape shape;
    sf::Texture texture;
    Direction direction;
};

extern const char BLUE_GHOST_TEXTURE[];
extern const char PINK_GHOST_TEXTURE[];
extern const char RED_GHOST_TEXTURE[];
extern const char ORANGE_GHOST_TEXTURE[];

bool initializeGhost(Ghost& ghost, const sf::Vector2f& position, const std::string& texturePath);
void updateGhost(Ghost& ghost, float elapsedTime, const Field& field);
void drawGhost(sf::RenderWindow& window, const Ghost& ghost);
sf::FloatRect getGhostBounds(const Ghost& ghost);
