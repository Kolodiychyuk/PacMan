#include "gamescene.h"
#include "utils.h"
#include <cassert>

static const sf::Color TRANSPARENT_GRAY = sf::Color(200, 200, 200, 200);

static const std::map<GhostId, std::string> TEXTURE_MAPPING = {
    { GhostId::BLINKY, RED_GHOST_TEXTURE },
    { GhostId::PINKY, PINK_GHOST_TEXTURE },
    { GhostId::INKY, BLUE_GHOST_TEXTURE },
    { GhostId::CLYDE, ORANGE_GHOST_TEXTURE },
};

static bool initializeGhostById(std::map<GhostId, Ghost>& ghosts, GhostId id) {
    Ghost& ghost = ghosts[id];
    const std::string texturePath = TEXTURE_MAPPING.at(id);
    return initializeGhost(ghost, getGhostStartPosition(id), texturePath);
}

static unsigned getRemainingCookies(const GameScene& scene) {
    return scene.totalCookieCount - scene.packman.eatenCookies;
}

static void updateGameOverLabel(sf::Text& label, const std::string& text) {
    label.setString(text);
    utils::centerizeTextOrigin(label);
}

void initializeGameScene(GameScene& scene, const sf::Vector2f& sceneSize) {
    bool succeed = scene.arial.loadFromFile("res/18938.ttf");

    initializeField(scene.field);
    initializePackman(scene.packman);

    succeed = initializeGhostById(scene.ghosts, GhostId::BLINKY)
        && initializeGhostById(scene.ghosts, GhostId::PINKY)
        && initializeGhostById(scene.ghosts, GhostId::INKY)
        && initializeGhostById(scene.ghosts, GhostId::CLYDE);

    scene.gameState = GameState::Playing;
    scene.totalCookieCount = countRemainingCookies(scene.field);

    scene.gameOverBackground.setFillColor(TRANSPARENT_GRAY);
    scene.gameOverBackground.setSize(sceneSize);

    scene.gameOverLabel.setFont(scene.arial);
    scene.gameOverLabel.setFillColor(sf::Color::Black);
    scene.gameOverLabel.setPosition(0.5f * sceneSize);
}

void updateGameScene(GameScene& scene, float elapsedTime) {
    if (scene.gameState == GameState::Playing) {
        updatePackman(scene.packman, elapsedTime, scene.field);
        for (auto& pair : scene.ghosts) {
            updateGhost(pair.second, elapsedTime, scene.field);
        }

        const sf::FloatRect packmanBounds = getPackmanBounds(scene.packman);
        for (const auto& pair : scene.ghosts) {
            if (getGhostBounds(pair.second).intersects(packmanBounds)) {
                updateGameOverLabel(scene.gameOverLabel, "Game Over! You lose.");
                scene.gameState = GameState::PlayerLosed;
            }
        }

        if (getRemainingCookies(scene) == 0) {
            updateGameOverLabel(scene.gameOverLabel, "Congratulations, you won!");
            scene.gameState = GameState::PlayerWon;
        }
    }
}

void drawGameScene(sf::RenderWindow& window, const GameScene& scene) {
    drawField(window, scene.field);
    drawPackman(window, scene.packman);

    for (const auto& pair : scene.ghosts) {
        drawGhost(window, pair.second);
    }

    if ((scene.gameState == GameState::PlayerLosed)
        || (scene.gameState == GameState::PlayerWon)) {
        window.draw(scene.gameOverBackground);
        window.draw(scene.gameOverLabel);
    }
}

void destroyGameScene(GameScene& scene) {
    destroyField(scene.field);
}