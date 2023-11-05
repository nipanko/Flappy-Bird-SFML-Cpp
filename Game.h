#pragma once

#include<SFML/Graphics.hpp>

#include "Bird.h"
#include "Pipe.h"
#include <random>

class Game
{
    public:
        Game(sf::RenderWindow&);
        sf::RenderWindow& win;
        void StartGameLoop();
    private:
        sf::Texture bg_texture,ground_texture;
        sf::Sprite bg_sprite,ground_sprite1,ground_sprite2;
        const float ground_move_speed = 550;
        Bird bird;
        bool isEnterPressed,run_game,start_monitoring;
        void moveGround(sf::Time&);
        void draw();
        void doProcessing(sf::Time &dt);
        void checkCollisions();
        void restartGame();
        void checkScore();
        std::string toString(int);

        int pipe_counter, pipe_spawn_time,score;
        std::vector<Pipe> pipes;
        std::random_device rd;
        std::uniform_int_distribution<int> dist{250, 550};


        sf::Font font;
        sf::Text restart_text;
        sf::Text score_text;



      
       
       
      
};

