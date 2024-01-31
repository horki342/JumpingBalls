#include "Game.h"

int main()
{
    int width = 1000;
    int height = 1000;
    std::string title = "Jumping Balls";
    Vector2 gravity;
    gravity.x = 0.0f;
    gravity.y = 9.8f;
    float factor = 1000.f;
    float radius = 5.0f;

    Game game(width, height, title, gravity, factor, radius);
    game.run();

    return 0;
}