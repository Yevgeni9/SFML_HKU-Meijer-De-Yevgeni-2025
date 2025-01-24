#include "Player.h"

Player::Player(float radius, sf::Vector2f initialPosition, float friction, float maxSpeed)
    : playerMovement(friction, maxSpeed)
{
    playerShape.setRadius(radius);
    playerShape.setFillColor(sf::Color::Green);
    playerShape.setPosition(initialPosition);
}

void Player::update(float deltaTime, const sf::RenderWindow& window)
{
    // Bewegingen via pijltjestoetsen
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        playerMovement.applyForce(sf::Vector2f(-1650.0f, 0.0f));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        playerMovement.applyForce(sf::Vector2f(1650.0f, 0.0f));

    playerMovement.update(deltaTime);

    playerShape.move(playerMovement.getVelocity() * deltaTime);

    // Collision met het venster, positie.x vergelijken is efficiënter dan afstand berekenen tot het venster
    sf::Vector2f position = playerShape.getPosition();
    float radius = playerShape.getRadius();

    if (position.x - radius < -25) {
        position.x = radius - 25;
    }
    if (position.x + radius > window.getSize().x -25) {
        position.x = window.getSize().x - radius -25;
    }

    playerShape.setPosition(position);
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(playerShape);
}

sf::Vector2f Player::getPosition() const {
    return playerShape.getPosition();
}

float Player::getRadius() const {
    return playerShape.getRadius();
}

// Nodig voor collision met enemies
sf::FloatRect Player::getBounds() const {
    return playerShape.getGlobalBounds();
}

