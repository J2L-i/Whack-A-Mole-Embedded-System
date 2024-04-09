//
// Created by Jennifer Lewis on 12/1/23.
//

#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite()
{
}

AnimatedSprite::AnimatedSprite(sf::Texture &texture, int rows, int cols)
{
    setup(texture, rows, cols);
}

void AnimatedSprite::setup(sf::Texture &texture, int rows, int cols)
{
    width = texture.getSize().x;
    height = texture.getSize().y;
    setTexture(texture);
    setupIntRect(texture.getSize(), rows, cols);
}

void AnimatedSprite::animate()
{
    if(clock.getElapsedTime().asMilliseconds() > time)
    {
        if(intRect.left + intRect.width >= width)
        {
            intRect.left = 0;
            animating = false;
        }
        else
        {
            intRect.left += intRect.width;
            animating = true;
        }
        clock.restart();
        setTextureRect(intRect);
    }
}

void AnimatedSprite::animateDefault()
{
    changeDirection(BACK);
    goUp();
}

void AnimatedSprite::goUp()
{
    if(clock.getElapsedTime().asMilliseconds() > time)
    {
        if(intRect.left + intRect.width >= width)
        {

        }
        else
        {
            intRect.left = intRect.left + intRect.width;
        }
        setTextureRect(intRect);
        clock.restart();
    }
}

bool AnimatedSprite::goUpIsEnabled()
{
    return animating;
}

void AnimatedSprite::setupIntRect(sf::Vector2u imgSize, int rows, int cols)
{
    intRect.width = std::round(width / static_cast<float>(cols));
    intRect.height = std::round(height / static_cast<float>(rows));
    intRect.left = 0;
    intRect.top = 0;
    setTextureRect(intRect);
}

int AnimatedSprite::getTime() const
{
    return time;
}

void AnimatedSprite::setTime(int time)
{
    AnimatedSprite::time = time;
}

void AnimatedSprite::update()
{
    //animate only if movable
    if (moving)
    {
        animate();
    }
}

void AnimatedSprite::eventHandler(sf::RenderWindow &window, sf::Event event)
{
    sf::Vector2f velocity;
    if(sf::Keyboard::isKeyPressed(forwardKey))
    {
        changeDirection(FORWARD);
        velocity.x = 0;
        velocity.y = speed;
    }
    else if(sf::Keyboard::isKeyPressed(downKey))
    {
        changeDirection(BACK);
        velocity.x = 0;
        velocity.y = -speed;
    }
    else if(sf::Keyboard::isKeyPressed(leftKey))
    {
        changeDirection(LEFT);
        velocity.x = -speed;
        velocity.y = 0;
    }
    else if(sf::Keyboard::isKeyPressed(rightKey))
    {
        changeDirection(RIGHT);
        velocity.x = speed;
        velocity.y = 0;
    }
    //else if spae click toggle movabel
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        moving = -moving;
        while(sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
    }
    move(velocity);
}

void AnimatedSprite::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Sprite s = (*this);
    target.draw(s);
}

void AnimatedSprite::changeDirection(directions direction)
{
    intRect.top = direction * intRect.height;
}

float AnimatedSprite::getSpeed() const
{
    return speed;
}

void AnimatedSprite::setSpeed(float speed)
{
    AnimatedSprite::speed = speed;
}

void AnimatedSprite::setForwardKey(sf::Keyboard::Key forwardKey)
{
    AnimatedSprite::forwardKey = forwardKey;
}

void AnimatedSprite::setLeftKey(sf::Keyboard::Key leftKey)
{
    AnimatedSprite::leftKey = leftKey;
}

void AnimatedSprite::setRightKey(sf::Keyboard::Key rightKey)
{
    AnimatedSprite::rightKey = rightKey;
}

void AnimatedSprite::setDownKey(sf::Keyboard::Key downKey)
{
    AnimatedSprite::downKey = downKey;
}
