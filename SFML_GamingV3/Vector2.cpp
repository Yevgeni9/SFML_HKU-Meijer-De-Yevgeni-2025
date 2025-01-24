#include "Vector2.h"

Vector2::Vector2(float friction, float maxSpeed)
    : velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f), friction(friction), maxSpeed(maxSpeed) {}

void Vector2::setAcceleration(const sf::Vector2f& accel) 
{
    acceleration = accel;
}

void Vector2::setFriction(float frictionValue) 
{
    friction = frictionValue;
}

void Vector2::setMaxSpeed(float maxSpeedValue) 
{
    maxSpeed = maxSpeedValue;
}

void Vector2::update(float deltaTime)
{
    // Acceleratie toevoegen
    velocity += acceleration * deltaTime;

    // Maximale snelheden
    if (velocity.x > maxSpeed) velocity.x = maxSpeed;
    if (velocity.x < -maxSpeed) velocity.x = -maxSpeed;
    if (velocity.y > maxSpeed) velocity.y = maxSpeed;
    if (velocity.y < -maxSpeed) velocity.y = -maxSpeed;

    // Frictie toepassen
    velocity.x *= friction;
    velocity.y *= friction;

    // Zet de versnelling naar 0
    acceleration = sf::Vector2f(0.0f, 0.0f);
}

void Vector2::applyForce(const sf::Vector2f& force)
{
    acceleration += force;
}

sf::Vector2f Vector2::getVelocity() const
{
    return velocity;
}