#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include "Application.h"
#include "Board.h"

int main()
{
    srand(time(0));

    Application application;
    application.run();
    return 0;
}

