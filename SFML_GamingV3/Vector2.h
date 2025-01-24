#ifndef VECTOR2_H
#define VECTOR2_H

#include <SFML/Graphics.hpp>

// De Vector2 class, in ieder geval een velocity, acceleration, friction en maxSpeed
// Nog later uit te breiden
// Frictie is niet hetzelfde als weerstand, maar om het simpel te houden van dit project wel
class Vector2 
{
    private:
        sf::Vector2f velocity;
        sf::Vector2f acceleration;
        float friction;
        float maxSpeed;

    public:
        Vector2(float friction = 0.98f, float maxSpeed = 200.0f);

        void setAcceleration(const sf::Vector2f& accel);
        void setFriction(float frictionValue);
        void setMaxSpeed(float maxSpeedValue);

        void update(float deltaTime);
        void applyForce(const sf::Vector2f& force);

        sf::Vector2f getVelocity() const;
};

#endif