#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <SFML/Graphics.hpp>

struct Coordinates {
    int x;
    int y;
};

enum Direction {UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3};

class Snake : public sf::Drawable, public sf::Transformable {
public:
    Snake();
    ~Snake();

    void snake_init();

    void next_step();

    void turn(Direction step);

    void add_len();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    Coordinates * snake_arr;

    Coordinates eat_coordinates;

    sf::Texture body_texture;

    sf::Texture head_texture;

    sf::Texture eat_texture;

    int snake_len;

    int direct;

    bool can_turn;
    bool resized;
};

#endif // SNAKE_HPP
