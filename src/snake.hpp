//Copyright 2020 KonstantIMP
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.

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

    int get_len();

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

    sf::Font dejavu;

    int snake_len;

    int direct;

    bool can_turn;
    bool resized;

    bool game_over;
};

#endif // SNAKE_HPP
