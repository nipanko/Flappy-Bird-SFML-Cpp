#include "Game.h"
#include <iostream>
#include "Globals.h"
#include <sstream>

Game::Game(sf::RenderWindow& window):win(window),isEnterPressed(false),run_game(true),pipe_counter(71),pipe_spawn_time(70),score(0),start_monitoring(false)
{
  

    win.setFramerateLimit(60);
    bg_texture.loadFromFile("res/textures/bg.png");
    bg_sprite.setTexture(bg_texture);
    bg_sprite.setScale(SCALE_FACTOR, SCALE_FACTOR);
    bg_sprite.setPosition(0.f, -250.f);


    ground_texture.loadFromFile("res/textures/ground.png");
    ground_sprite1.setTexture(ground_texture);
    ground_sprite2.setTexture(ground_texture);

    ground_sprite1.setScale(SCALE_FACTOR,SCALE_FACTOR);
    ground_sprite2.setScale(SCALE_FACTOR,SCALE_FACTOR);

    ground_sprite1.setPosition(0, 578);
    ground_sprite2.setPosition(ground_sprite1.getGlobalBounds().width, 578);

    font.loadFromFile("res/fonts/04B_19__.TTF");
    restart_text.setFont(font);
    restart_text.setCharacterSize(48);
    restart_text.setFillColor(sf::Color::Magenta);
    restart_text.setPosition(150, 650);
    restart_text.setString("RESTART GAME!");


    score_text.setFont(font);
    score_text.setCharacterSize(25);
    score_text.setFillColor(sf::Color::Black);
    score_text.setPosition(20, 20);
    score_text.setString("SCORE : 0");

    Pipe::loadTexture();

}

void Game::checkCollisions()
{
    if(pipes.size()>0)
    {
        if (pipes[0].sprite_down.getGlobalBounds().intersects(bird.bird_sprite.getGlobalBounds())||
            pipes[0].sprite_up.getGlobalBounds().intersects(bird.bird_sprite.getGlobalBounds())||
            bird.bird_sprite.getGlobalBounds().top>=540)
        {
            isEnterPressed = false;
            run_game = false;
        }
    }
}

void Game::draw()
{
    win.draw(bg_sprite);
    for(Pipe& pipe:pipes)
    {
        win.draw(pipe.sprite_down);
        win.draw(pipe.sprite_up);
    }
    win.draw(ground_sprite1);
    win.draw(ground_sprite2);
    win.draw(bird.bird_sprite);
    win.draw(score_text);
    if(!run_game)
    {
        win.draw(restart_text);
    }
}

void Game::moveGround(sf::Time& dt)
{
    ground_sprite1.move(-ground_move_speed * dt.asSeconds(), 0.f);
    ground_sprite2.move(-ground_move_speed * dt.asSeconds(), 0.f);

    if(ground_sprite1.getGlobalBounds().left + ground_sprite1.getGlobalBounds().width<0) //left will give x coordinate
    {
        ground_sprite1.setPosition(ground_sprite2.getGlobalBounds().left + ground_sprite2.getGlobalBounds().width,578);

    }
    if(ground_sprite2.getGlobalBounds().left + ground_sprite2.getGlobalBounds().width<0) //left will give x coordinate
    {
        ground_sprite2.setPosition(ground_sprite1.getGlobalBounds().left + ground_sprite1.getGlobalBounds().width,578);

    }


}

void Game::checkScore()
{
    if(pipes.size()>0)
    {
        if(!start_monitoring)
        {
            if(bird.bird_sprite.getGlobalBounds().left>pipes[0].sprite_down.getGlobalBounds().left &&
                bird.getRightBound()<pipes[0].getRightBound())
            {
                start_monitoring = true;
            }
        }
        else
        {
            if(bird.bird_sprite.getGlobalBounds().left>pipes[0].getRightBound())
            {
                
                score++;
                score_text.setString("SCORE : "+toString(score));
                start_monitoring = false;
            }
        }
    }
}

std::string Game::toString(int num)
{
    std::stringstream ss;
    ss << num;
    return ss.str();
}

void Game::restartGame()
{
    bird.resetBirdPosition();
    bird.setShouldFly(false);
    run_game = true;
    isEnterPressed = false;
    pipe_counter = 71;
    pipes.clear();
    score = 0;
    score_text.setString("SCORE : 0");
}

void Game::doProcessing(sf::Time& dt)
{
    if(isEnterPressed)
    {
        moveGround(dt);
        if(pipe_counter>pipe_spawn_time)
        {
            pipes.push_back(Pipe(dist(rd)));
            pipe_counter = 0;
        }
        pipe_counter++;

        for(int i =0;i < pipes.size();i++)
        {
            pipes[i].Update(dt);
            if(pipes[i].getRightBound()<0)
            {
                pipes.erase(pipes.begin() + i);
            }
        }
        checkCollisions();
        checkScore();
    }
    bird.Update(dt);
}

void Game::StartGameLoop()
{
    sf::Clock clock;

    while (win.isOpen())
    {
        sf::Time dt = clock.restart();
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win.close();
            if(event.type==sf::Event::KeyPressed && run_game)
            {
                if(event.key.code == sf::Keyboard::Enter && !isEnterPressed)
                {
                    isEnterPressed = true;
                    bird.setShouldFly(true);
                }
                if(event.key.code == sf::Keyboard::Space && isEnterPressed)
                {
                    bird.flapBird(dt);
                    
                }
            }
            if(event.type ==sf::Event::MouseButtonPressed && event.mouseButton.button==sf::Mouse::Left && !run_game)
            {
                if(restart_text.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y))
                {
                    restartGame();
                }
                
            }
        }
       
       
        doProcessing(dt);
        draw();
        win.display();

    }


}