//
//

#ifndef CS3A_SPRING23_SFML_TUTORIAL_ANIMATEDSPRITE_H
#define CS3A_SPRING23_SFML_TUTORIAL_ANIMATEDSPRITE_H
#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>
enum directions {FORWARD, LEFT, RIGHT, BACK};

class AnimatedSprite :  public sf::Sprite
{
private:
    sf::Clock clock;
    sf::IntRect intRect;
    int time = 140;
    float speed;
    sf::Keyboard::Key forwardKey = sf::Keyboard::Down,
    leftKey = sf::Keyboard::Left,
    rightKey = sf::Keyboard::Right,
    downKey = sf::Keyboard::Up;
    bool animating = false;
public:
    void setForwardKey(sf::Keyboard::Key forwardKey);

    void setLeftKey(sf::Keyboard::Key leftKey);

    void setRightKey(sf::Keyboard::Key rightKey);

    void setDownKey(sf::Keyboard::Key downKey);

public:
    float getSpeed() const;

    void setSpeed(float speed);

private:
    unsigned int width, height;
    bool moving = true;
public:
    int getTime() const;

    void setTime(int time);

private:
    void setup(sf::Texture &texture, int rows, int cols);
    void setupIntRect(sf::Vector2u imgSize, int rows, int cols);
public:
    AnimatedSprite();
    AnimatedSprite(sf::Texture &texture, int rows, int cols);
    void changeDirection(directions direction);
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    void eventHandler(sf::RenderWindow &window, sf::Event event);

    void goUp();
    bool goUpIsEnabled();
    void animate();
    void animateDefault();
    void update();
};


#endif //CS3A_SPRING23_SFML_TUTORIAL_ANIMATEDSPRITE_H
