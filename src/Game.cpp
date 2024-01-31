#include "Game.h"
#include "raymath.h"
#include <iostream>

Game::Game(
    int width,
    int height,
    const std::string &title,
    Vector2 gravity,
    float factor,
    float radius)
    : width(width), height(height), title(title), balls(), gravity(gravity), factor(factor), radius(radius)
{
    InitWindow(width, height, title.c_str());
    SetTargetFPS(FPS);

    SetRandomSeed(static_cast<int>(GetTime()));
}

Game::~Game()
{
}

void Game::run()
{
    while (~WindowShouldClose())
    {
        float dt = GetFrameTime();

        handleUserInput();

        update(dt);

        render();
    }
}

void Game::render()
{
    ClearBackground(BLACK);

    BeginDrawing();

    for (auto &ball : balls)
    {
        ball.draw();
    }

    EndDrawing();
}

void Game::handleUserInput()
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        CloseWindow();
    }

    // get the click position
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        generateBall(GetMousePosition());
}

void Game::update(float dt)
{
    for (auto &ball : balls)
    {
        ball.update(gravity, dt);

        checkBoundaries(ball);
        checkCollisions(ball);
    }
}

void Game::generateBall(Vector2 position)
{
    // generate random velocity
    Vector2 velocity;
    velocity.x = GetRandomValue(1, 500) * 1.0f;
    velocity.y = GetRandomValue(1, 500) * 1.0f;

    // get random mass
    float mass = GetRandomValue(1, 10000);

    // std::cout << mass << '\n';

    Ball ball(RED, radius, position, mass);
    ball.changeVelocity(velocity);
    balls.push_back(ball);
}

void Game::checkBoundaries(Ball &ball)
{
    auto position = ball.get_position();
    auto velocity = ball.get_velocity();
    auto new_velocity = velocity;

    if (position.x <= radius)
    {
        new_velocity.x = -1.0f * velocity.x;

        auto correction = radius - position.x;
        position.x += correction;
    }
    else if (position.x >= width - radius)
    {
        new_velocity.x = -1.0f * velocity.x;

        auto correction = position.x - width + radius;
        position.x -= correction;
    }
    if (position.y <= radius)
    {
        new_velocity.y = -1.0f * velocity.y;

        auto correction = radius - position.y;
        position.y += correction;
    }
    else if (position.y >= height - radius)
    {
        new_velocity.y = -1.0f * velocity.y;

        auto correction = position.y - height + radius;
        position.y -= correction;
    }

    ball.correctPosition(position);
    ball.changeVelocity(new_velocity);
}

void Game::checkCollisions(Ball &ball)
{
    for (auto &other : balls)
    {
        if (ball == other) continue;

        if (CheckCollisionCircles(ball.get_position(), radius, other.get_position(), radius))
        {
            // old_velocity_ball
            auto v1 = ball.get_velocity(); 
            // old_velocity_other
            auto v2 = other.get_velocity();

            // position_ball
            auto x1 = ball.get_position();
            // position_other
            auto x2 = other.get_position();

            // mass_ball
            auto m1 = ball.get_mass();
            // mass_other
            auto m2 = ball.get_mass();

            auto distance = Vector2Length(Vector2Subtract(x1, x2));
            distance *= distance;

            auto factor1 = 2 * m2 / (m1 + m2) / distance;
            auto dot1 = Vector2DotProduct(Vector2Subtract(v1, v2), Vector2Subtract(x1, x2));
            auto correction1 = Vector2Scale(Vector2Subtract(x1, x2), factor1 * dot1);
            ball.changeVelocity(Vector2Subtract(v1, correction1));

            auto factor2 = 2 * m1 / (m1 + m2) / distance;
            auto dot2 = Vector2DotProduct(Vector2Subtract(v2, v1), Vector2Subtract(x2, x1));
            auto correction2 = Vector2Scale(Vector2Subtract(x2, x1), factor2 * dot2);
            other.changeVelocity(Vector2Subtract(v2, correction2));
        }
    }
}