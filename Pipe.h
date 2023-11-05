#pragma once
#include <SFML/Graphics.hpp>

class Pipe
{
    public:
        Pipe(int);
        static void loadTexture();
        sf::Sprite sprite_up, sprite_down;
        void Update(sf::Time&);
        float getRightBound();
    private:
        static sf::Texture texture_down, texture_up;
        static int pipe_distance, move_speed;
};

