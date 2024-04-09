#include "RandomPatternGenerator.h"

int RandomPatternGenerator::getPattern()
{
    if(clock.getElapsedTime().asSeconds() > timeIncrement/static_cast<float>(variations) && count < variations)
    {
        clock.restart();
        count++;
        enabled = true;
        if(count == 1)
        {
            selected = rand() % 6;
        }
        if(count == variations)
        {
            count = 0;
        }
    }
    else
    {
        enabled = false;
    }

    return selected;
}

bool RandomPatternGenerator::isEnabled()
{
    getPattern();
    return enabled;
}

int RandomPatternGenerator::getVariations() const
{
    return variations;
}
float RandomPatternGenerator::getTimeIncrement() const
{
    return timeIncrement;
}

void RandomPatternGenerator::setVariations(int v)
{
    variations = v;
}
void RandomPatternGenerator::setTimeIncrement(float ti)
{
    timeIncrement = ti;
}
