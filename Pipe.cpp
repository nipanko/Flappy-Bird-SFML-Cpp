#include "Pipe.h"

#include "Globals.h"


sf::Texture Pipe::texture_down, Pipe::texture_up;
int Pipe::pipe_distance = 180, Pipe::move_speed = 400;


Pipe::Pipe(int y_pos)
{
    sprite_down.setTexture(texture_down);
    sprite_up.setTexture(texture_up);

    sprite_down.setScale(SCALE_FACTOR, SCALE_FACTOR);
    sprite_up.setScale(SCALE_FACTOR, SCALE_FACTOR);

    sprite_up.setPosition(WIN_WIDTH, y_pos);
    sprite_down.setPosition(WIN_WIDTH, y_pos - pipe_distance - sprite_up.getGlobalBounds().height);


}

void Pipe::loadTexture()
{
    texture_down.loadFromFile("res/textures/pipedown.png");
    texture_up.loadFromFile("res/textures/pipe.png");
}

void Pipe::Update(sf::Time& dt)
{
    sprite_up.move(-move_speed * dt.asSeconds(), 0.f);
    sprite_down.move(-move_speed * dt.asSeconds(), 0.f);

}

float Pipe::getRightBound()
{
    return sprite_down.getGlobalBounds().left + sprite_down.getGlobalBounds().width                                                                                             ;
}
