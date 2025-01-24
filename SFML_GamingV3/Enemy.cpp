#include "Enemy.h"

Enemy::Enemy(float x, float y, float radius, Vector2 initialVelocity, float horizSpeed)
    : movement(initialVelocity), horizontalSpeed(horizSpeed)
{
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(x, y);
}

void Enemy::update(float deltaTime, const sf::RenderWindow& window)
{
    // Gebruik bestaande vector klasse voor beweging naar beneden
    movement.applyForce(sf::Vector2f(0.0f, 2000.0f));
    movement.update(deltaTime);

    sf::Vector2f velocity = movement.getVelocity();

    float xPos = shape.getPosition().x;
    float radius = shape.getRadius();

    if (xPos - radius <= -18 || xPos + radius >= window.getSize().x - 18) {
        horizontalSpeed *= -1;
    }

    shape.move(horizontalSpeed * deltaTime, velocity.y * deltaTime);
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::Vector2f Enemy::getPosition() const {
    return shape.getPosition();
}

float Enemy::getRadius() const {
    return shape.getRadius();
}

// Nodig voor collision met speler
sf::FloatRect Enemy::getBounds() const {
    return shape.getGlobalBounds();
}
