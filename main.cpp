#include "SFML/Graphics.hpp"
#include "Globals.h"
#include "Game.h"


int main()
{
    //setup();
    sf::RenderWindow win(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Flappy Bird");
    Game game(win);
    game.StartGameLoop();
    return 0;
}