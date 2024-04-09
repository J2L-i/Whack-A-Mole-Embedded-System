#include "Board.h"


Board::Board() {
}

Board::Board(int numberOfMoles, sf::Vector2f windSize ) {
    windowSize = windSize;
    column = 4;

    for(int i = 0; i < numberOfMoles; i++)
        moles.push_back(createAMole(4, column,5));

    position();

}

void Board::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    for(int i=0; i<moles.size(); i++)
        window.draw(moles[i]);
}

AnimatedSprite Board::createAMole(int rows, int col, float speed) {
    texture.loadFromFile("mole_edit_6.png");
    AnimatedSprite mole(texture, rows, col);
    mole.setSpeed(speed);
    mole.setScale(0.5f, 0.5f);
    return mole;
}

void Board::position() {

    const int numRows = 2;  // Adjust the number of rows as needed
    const int numCols = 3;  // Adjust the number of columns as needed

    // Calculate the starting position based on the size of the window
    float startX = (windowSize.x - moles[3].getGlobalBounds().width * numCols) / 2.0f;
    float startY = (windowSize.y - moles[3].getGlobalBounds().height * numRows) / 2.0f;

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            int moleIndex = col + row * numCols;
            moles[moleIndex].setPosition(startX + col * moles[3].getGlobalBounds().width,
                                         startY + row * moles[3].getGlobalBounds().height);
        }
    }

}


void Board::setPosition(sf::Vector2f position) {
    moles[5].setPosition((windowSize.x / 2), (windowSize.y / 2));
    Board::position();
}

void Board::eventHandler(sf::RenderWindow& window, sf::Event event, int &clickCount) {
    if(sf::Mouse::isButtonPressed((sf::Mouse::Left))) {
        sf::Vector2f mpos = (sf::Vector2f) sf::Mouse::getPosition(window);
        for(int i = 0; i < moles.size(); i++) {
            if(moles[i].getGlobalBounds().contains(mpos) && moles[i].goUpIsEnabled()) {
                clickCount++;
                break;
            }
        }
    }
    while(sf::Mouse::isButtonPressed((sf::Mouse::Left)));
}

void Board::goUp(int index) {
    if(!stop)
        moles[index].animate();
}

void Board::showDefault() {
    for(int i = 0; i < moles.size(); i++)
        moles[i].animateDefault();
    stop = true;
}




