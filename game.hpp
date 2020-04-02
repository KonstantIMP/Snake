#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include "snake.hpp"

class Game {
public:
    Game();
    ~Game();

    void Run();

private:
    sf::RenderWindow *main_win;

    sf::Event mw_event;

    sf::Font dejavu;

    sf::Clock frame_ptr;

    Snake mw_game;
};

#endif // GAME_HPP
