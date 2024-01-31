#pragma once

#include "raylib.h"

class Ball
{
public:
    Ball(Color color, float radius, Vector2 position, float mass);

    bool operator==(Ball &other) const;

    void draw();

    void update(Vector2 acceleration, float dt);

    void changeVelocity(Vector2 new_velocity);
    void correctPosition(Vector2 new_position);

    Vector2 get_velocity() const;
    Vector2 get_position() const;
    float get_mass() const;

private:
    Color color;
    float radius;
    Vector2 position;
    Vector2 velocity;

    float mass;
};