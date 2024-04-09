#include "Application.h"

#include <iostream>

enum class DifficultyLevel {
    Easy,
    Medium,
    Hard
};

void Application::run()
{
    sf::RenderWindow window({720, 720, 32}, "WhackAMole");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    Board wAM(6, {720, 720});


    RandomPatternGenerator rpg;
    rpg.setVariations(4);


    // Start Screen
    sf::Texture startTexture;
    sf::Sprite startScreen;
    startTexture.loadFromFile("dayBackground.png"); // Replace "startScreen.png" with the path to your start screen image
    startScreen.setTexture(startTexture);

    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Text welcomeText;
    welcomeText.setFont(font);
    welcomeText.setCharacterSize(50);
    welcomeText.setFillColor(sf::Color::White);
    welcomeText.setString("Welcome to Whack-A-Mole!");
    welcomeText.setPosition(100, 100);

    sf::RectangleShape easyButton(sf::Vector2f(100, 50));
    easyButton.setFillColor(sf::Color::Green);
    easyButton.setPosition(180, 300);

    sf::Text easyText;
    easyText.setFont(font);
    easyText.setCharacterSize(20);
    easyText.setFillColor(sf::Color::White);
    easyText.setString("Easy");
    easyText.setPosition(210, 310);

    sf::RectangleShape mediumButton(sf::Vector2f(100, 50));
    mediumButton.setFillColor(sf::Color::Yellow);
    mediumButton.setPosition(320, 300);

    sf::Text mediumText;
    mediumText.setFont(font);
    mediumText.setCharacterSize(20);
    mediumText.setFillColor(sf::Color::Black);
    mediumText.setString("Medium");
    mediumText.setPosition(340, 310);

    sf::RectangleShape hardButton(sf::Vector2f(100, 50));
    hardButton.setFillColor(sf::Color::Red);
    hardButton.setPosition(460, 300);

    sf::Text hardText;
    hardText.setFont(font);
    hardText.setCharacterSize(20);
    hardText.setFillColor(sf::Color::White);
    hardText.setString("Hard");
    hardText.setPosition(490, 310);

    sf::RectangleShape startButton(sf::Vector2f(200, 50));
    startButton.setFillColor(sf::Color::Blue);
    startButton.setPosition(260, 400);

    sf::Text startText;
    startText.setFont(font);
    startText.setCharacterSize(30);
    startText.setFillColor(sf::Color::White);
    startText.setString("Start Game");
    startText.setPosition(280, 405);

    DifficultyLevel selectedLevel = DifficultyLevel::Easy;
    bool levelSelected = false;

    // Display the start screen until the level is selected
    while (window.isOpen() && !levelSelected)
    {
        sf::Event startEvent;
        while (window.pollEvent(startEvent))
        {
            if (startEvent.type == sf::Event::Closed)
            {
                window.close();
                return;
            }
            else if (startEvent.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (easyButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                {
                    selectedLevel = DifficultyLevel::Easy;
                    levelSelected = true;
                }
                else if (mediumButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                {
                    selectedLevel = DifficultyLevel::Medium;
                    levelSelected = true;
                }
                else if (hardButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                {
                    selectedLevel = DifficultyLevel::Hard;
                    levelSelected = true;
                }
            }
        }

        window.clear();
        window.draw(startScreen);
        window.draw(welcomeText);
        window.draw(easyButton);
        window.draw(easyText);
        window.draw(mediumButton);
        window.draw(mediumText);
        window.draw(hardButton);
        window.draw(hardText);
        window.display();
    }
    switch (selectedLevel) {
    case DifficultyLevel::Easy:
        playerSprite.setSpeed(1.0);
        rpg.setTimeIncrement(0.5);

        break;
    case DifficultyLevel::Medium:
        playerSprite.setSpeed(5.0);
        rpg.setTimeIncrement(0.6);

        break;
    case DifficultyLevel::Hard:
        playerSprite.setSpeed(20.0);
        rpg.setTimeIncrement(0.6);

        break;
    }



    // Initialize game components after the level is selected

    int clickCount = 0;

    sf::Texture backgroundTexture;
    sf::Sprite background;
    backgroundTexture.loadFromFile("dayBackground.png");
    background.setTexture(backgroundTexture);
    background.setPosition({0, 0});

    sf::Font scoreFont;
    scoreFont.loadFromFile("arial.ttf");

    sf::Text score;
    score.setFont(scoreFont);
    score.setCharacterSize(30);
    score.setFillColor(sf::Color::Yellow);
    score.setPosition(10, 10);

    sf::Text timePassed;
    timePassed.setFont(scoreFont);
    timePassed.setCharacterSize(30);
    timePassed.setFillColor(sf::Color::White);
    timePassed.setPosition(500, 10);
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("Game Over!");
    gameOverText.setPosition(250, 200);

    sf::Text finalScoreText;
    finalScoreText.setFont(font);
    finalScoreText.setCharacterSize(30);
    finalScoreText.setFillColor(sf::Color::White);
    finalScoreText.setPosition(300, 300);


    sf::Clock wAMClock;

    while (window.isOpen())
    {
        // event listener
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            wAM.eventHandler(window, event, clickCount);
        }

        // Update mole animation based on pattern
        if (rpg.isEnabled())
        {
            int n = rpg.getPattern();
            wAM.goUp(n);
        }

        // Check conditions for stopping mole animation
        if (clickCount >= 100 || wAMClock.getElapsedTime().asSeconds() > 30)
        {
            wAM.showDefault();
            currentState = GameState::GameOver;

            // Display game over screen with final score
            finalScoreText.setString("Final Score: " + std::to_string(clickCount));

            window.clear();
            window.draw(gameOverText);
            window.draw(finalScoreText);
            window.display();

            // Wait for a moment before closing the window (you can adjust the duration)
            sf::sleep(sf::seconds(3));

            window.close();
        }

        // Update score and time display
        score.setString("Score: " + std::to_string(clickCount));
        timePassed.setString("Time: " + std::to_string(wAMClock.getElapsedTime().asSeconds()));

        // Clear and draw everything
        window.clear();
        window.draw(background);
        window.draw(score);
        window.draw(timePassed);
        window.draw(wAM);
        window.display();
    }
}

