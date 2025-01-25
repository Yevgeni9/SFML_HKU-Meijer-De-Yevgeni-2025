#include <iostream>
#include <filesystem>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "Vector2.h"
#include "Enemy.h"
#include "Player.h"

int main()
{
    std::filesystem::path workingDirectory = std::filesystem::current_path();
    std::cout << "Current working directory: " << workingDirectory << std::endl;

    sf::RenderWindow window(sf::VideoMode(800, 800), "C++ SFML Parachute Panic!");
    sf::Font font;

    std::filesystem::path projectDirectory = std::filesystem::current_path();
    std::filesystem::path caughtSoundPath = projectDirectory / "SoundFiles" / "caught.wav";
    std::filesystem::path explosionSoundPath = projectDirectory / "SoundFiles" / "explosion.wav";
    std::filesystem::path musicFilePath = projectDirectory / "SoundFiles" / "background_music.wav";
    sf::Music backgroundMusic;

    sf::SoundBuffer caughtBuffer;
    sf::SoundBuffer explosionBuffer;

    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }

    if (!backgroundMusic.openFromFile(musicFilePath.string())) {
        std::cout << "Error loading background music!" << std::endl;
        return -1;
    }

    if (!caughtBuffer.loadFromFile(caughtSoundPath.string())) {
        std::cout << "Error loading caught sound!" << std::endl;
    }
    if (!explosionBuffer.loadFromFile(explosionSoundPath.string())) {
        std::cout << "Error loading explosion sound!" << std::endl;
    }

    sf::Sound caughtSound(caughtBuffer);
    sf::Sound explosionSound(explosionBuffer);



    backgroundMusic.setLoop(true);
    backgroundMusic.play();

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score: 0");
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(15.0f, 10.0f);

    sf::Text livesText;
    livesText.setFont(font);
    livesText.setString("Lives: 2");
    livesText.setCharacterSize(24);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(15.0f, 35.0f);

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("Game Over! Press R to restart");
    gameOverText.setCharacterSize(32);
    gameOverText.setFillColor(sf::Color::White);

    // Game over tekst komt in het midden
    float textWidth = gameOverText.getLocalBounds().width;
    float textHeight = gameOverText.getLocalBounds().height;
    gameOverText.setPosition((window.getSize().x - textWidth) / 2, (window.getSize().y - textHeight) / 2);

    // Variabelen voor het spel
    int score = 0;
    int lives = 2;
    bool paused = false;

    // Maak de speler en enemies
    Player player(25.0f, sf::Vector2f(400,750), 0.9995f, 1500.0f);
    std::vector<Enemy> enemies;

    // Variabelen voor het spawnen voor de enemies
    float spawnTimer = 0.0f;
    float spawnInterval = 1.75f;

    sf:: Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        if (lives <= 0 && !paused)
        {
            paused = true;
            std::cout << "Game Over! R to restart" << std::endl;
        }

        spawnTimer += deltaTime;

        // Twee if-statements in elkaar is niet best, maar ik ben onzeker hoe ik dit kan verbeteren
        // Spawnen mag zolang pause niet waar is
        if (!paused)
        {
            player.update(deltaTime, window);
        
            if (spawnTimer >= spawnInterval) 
            {
                float margin = 100.0f;

                // Willekeurige spawn positie zodat er nog meer random is
                float spawnX = margin + rand() % static_cast<int>(800 - 2 * margin);
                float spawnY = -30.0f;
                // Willekeurige horizontale snelheid voor de enemies
                float randomXSpeed = static_cast<float>(rand() % 1000 - 500);
                Vector2 enemyVelocity(0.9995f, 2000.0f);
                enemies.push_back(Enemy(spawnX, spawnY, 20, enemyVelocity, randomXSpeed));
                spawnTimer = 0.0f;
                std::cout << "Random X Speed: " << randomXSpeed << std::endl;
            }

            for (auto it = enemies.begin(); it != enemies.end();)
            {
                it->update(deltaTime, window);

                // Dit checked botsingen via circle-collision methode, uitgelegd in de physics les 
                if (std::sqrt(std::pow(player.getPosition().x - it->getPosition().x, 2) +
                            std::pow(player.getPosition().y - it->getPosition().y, 2)) <
                    (player.getRadius() + it->getRadius()))
                {
                    std::cout << "Collision detected!" << std::endl;
                    score++;
                    scoreText.setString("Score: " + std::to_string(score));
                    caughtSound.play();
                    it = enemies.erase(it);
                }

                else
                {
                    ++it;
                }
            }
        }

        // Voor het restarten wanneer de levens op
        if (paused && sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            paused = false;
            score = 0;
            scoreText.setString("Score: " + std::to_string(score));
            lives = 2;
            livesText.setString("Lives: " + std::to_string(lives));
            enemies.clear();
        }

        // apart variabele voor de enemies die verwijderd worden
        int enemiesRemoved = 0;

        enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
            [&window, &enemiesRemoved](const Enemy& enemy) {
                if (enemy.getPosition().y - enemy.getRadius() > window.getSize().y) {
                    ++enemiesRemoved;
                    return true;
                }
                return false;
            }), enemies.end());

        // Als er een vijand verwijderd wordt, moeten de levens omlaag
        if (enemiesRemoved > 0) {
            std::cout << enemiesRemoved << " enemy got removed" << std::endl;
            lives--;
            livesText.setString("Lives: " + std::to_string(lives));
            explosionSound.play();
        }

        window.clear();

        for (Enemy& enemy : enemies)
        {
            enemy.draw(window);
        }

        // Game over tekst verschijnt na window.clear(); anders kan je het niet zien
        if (paused)
        {
            window.draw(gameOverText);
        }

        player.draw(window);
        window.draw(scoreText);
        window.draw(livesText);
        window.display();
    }

    return 0;
}