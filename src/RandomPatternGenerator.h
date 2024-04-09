#ifndef SIMON_RANDOMPATTERNGENERATOR_H
#define SIMON_RANDOMPATTERNGENERATOR_H
#include <SFML/Graphics.hpp>

class RandomPatternGenerator
{
private:
    sf::Clock clock;
    bool enabled = false, running = true; //enabled = false
    int variations, count = 0, selected;
    float timeIncrement;
public:
    int getPattern();
    bool isEnabled();
    int getVariations() const;
    float getTimeIncrement() const;

    void setVariations(int v);
    void setTimeIncrement(float ti);
};


#endif //SIMON_RANDOMPATTERNGENERATOR_H
