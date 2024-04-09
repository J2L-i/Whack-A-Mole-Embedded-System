#ifndef SIMON_APPLICATION_H
#define SIMON_APPLICATION_H
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "RandomPatternGenerator.h"
#include "AnimatedSprite.h"
class Board;
enum class GameState {
    Start,
    GameOver,
    // Add other game states as needed
};
 class Application
{
public:
    void run();
private:
    AnimatedSprite playerSprite;
    GameState currentState;  // Add this line to declare the currentState variable
    bool gameOver;
    sf::Text replayText;
    sf::RectangleShape replayButton;



    sf::RenderWindow window;
    enum class PlayMode {
        Easy,
        Medium,
        Hard
    };

};


#endif //SIMON_APPLICATION_H
