#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "snake.hpp"

class Game {
public:
    Game();
    ~Game();

    void Run();

private:
    sf::RenderWindow *main_win;

    sf::Texture earth;

    sf::Texture background;

    sf::Event mw_event;

    sf::Font dejavu;

    sf::Clock frame_ptr;

    sf::Clock timer;

    sf::Music mw_music;

    Snake mw_game;

    float speed;
};

#endif // GAME_HPP
