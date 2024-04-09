#ifndef SIMON_BOARD_H
#define SIMON_BOARD_H
#include "iostream"
#include <SFML/Graphics.hpp>
#include <vector>
#include "AnimatedSprite.h"
#include "RandomPatternGenerator.h"

class Board : public AnimatedSprite
{

private:
    std::vector<AnimatedSprite> moles;
    sf::Texture texture;
    RandomPatternGenerator patternGenerator;

    AnimatedSprite createAMole(int rows, int col, float setSpeed);
    void position();
    sf::Vector2f windowSize;
    bool enabled = false;
    sf::Clock clock;
    int column = 0;
    bool stop = false;

public:
    Board();
    Board(int numberOfMoles, sf::Vector2f windowSize);
    void setPosition(sf::Vector2f position);
    virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    void eventHandler(sf::RenderWindow& window, sf::Event event, int &clickCount);
    void lightUp(int index);
    void goUp(int index);
    void showDefault();



};


#endif //SIMON_BOARD_H
