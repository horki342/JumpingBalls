#pragma once

#include "Ball.h"
#include <string>
#include <vector>

class Game
{
public:
    Game(
        int width, 
        int height, 
        const std::string &title, 
        Vector2 gravity, 
        float factor,
        float radius
    );
    ~Game();

    void run();

    void render();
    void handleUserInput();
    void update(float dt);

private:
    void generateBall(Vector2 position);
    void checkBoundaries(Ball &ball);
    void checkCollisions(Ball &ball);

private:
    int width;
    int height;

    std::string title;

    std::vector<Ball> balls;

    Vector2 gravity;

    float factor;
    float radius;

    const int FPS{60};
};