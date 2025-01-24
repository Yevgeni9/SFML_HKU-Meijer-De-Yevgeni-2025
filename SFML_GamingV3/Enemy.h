#pragma once
#include "Vector2.h"
#include <SFML/Graphics.hpp>

// Klasse voor de enemies die bovenin spawnen
class Enemy {
public:
    sf::CircleShape shape;
    Vector2 movement;
    float horizontalSpeed;

    Enemy(float x, float y, float radius, Vector2 initialVelocity, float horizSpeed);

    void update(float deltaTime, const sf::RenderWindow& window);

    void draw(sf::RenderWindow& window);

    // Nodig voor collision met speler
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    float getRadius() const;
};