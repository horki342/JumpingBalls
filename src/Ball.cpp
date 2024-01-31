#include "Ball.h"
#include "raymath.h"

Ball::Ball(Color color, float radius, Vector2 position, float mass)
    : color(color), radius(radius), position(position), mass(mass)
{
}

bool Ball::operator==(Ball &other) const
{
    return (
        other.get_mass() == get_mass() 
        && Vector2Equals(get_position(), get_position())
        && Vector2Equals(get_velocity(), get_velocity())
    );
}

void Ball::draw()
{
    DrawCircle(position.x, position.y, radius, color);
}

void Ball::update(Vector2 acceleration, float dt)
{
    Vector2 dv = Vector2Scale(acceleration, dt);
    velocity = Vector2Add(velocity, dv);
    Vector2 dr = Vector2Scale(velocity, dt);
    position = Vector2Add(position, dr);
}

void Ball::changeVelocity(Vector2 new_velocity)
{
    velocity = new_velocity;
}

void Ball::correctPosition(Vector2 new_position)
{
    position = new_position;
}

Vector2 Ball::get_velocity() const
{
    return velocity;
}

Vector2 Ball::get_position() const
{
    return position;
}

float Ball::get_mass() const
{
    return mass;
}