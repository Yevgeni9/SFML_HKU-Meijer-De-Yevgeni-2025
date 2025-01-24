#include <SFML/Graphics.hpp>
#include "Vector2.h"

// Klasse voor de speler
class Player 
{
    public:
        sf::CircleShape playerShape;
        Vector2 playerMovement;

        Player(float radius, sf::Vector2f initialPosition, float friction, float maxSpeed);
        void update(float deltaTime, const sf::RenderWindow& window);
        void draw(sf::RenderWindow& window);

        // Nodig voor collision met enemy
        sf::Vector2f getPosition() const;
        sf::FloatRect getBounds() const;
        float getRadius() const;
};