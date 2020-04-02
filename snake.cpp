#include "snake.hpp"

Snake::Snake() {

    if(!(body_texture.loadFromFile("body.png"))) exit(3);

    if(!(head_texture.loadFromFile("head.png"))) exit(3);

    if(!(eat_texture.loadFromFile("eat.png"))) exit(3);

    if(!(dejavu.loadFromFile("DejaVuSansMono.ttf"))) exit(4);

    snake_init();
}

Snake::~Snake() {
    delete snake_arr;
}

int Snake::get_len() {
    return snake_len;
}

void Snake::snake_init() {
    snake_len = 3;
    snake_arr = new Coordinates[snake_len];

    snake_arr[0].x = 1; snake_arr[0].y = 13;
    snake_arr[1].x = 2; snake_arr[1].y = 13;
    snake_arr[2].x = 3; snake_arr[2].y = 13;

    eat_coordinates.x = 19;
    eat_coordinates.y = 15;

    direct = RIGHT;

    can_turn = true;

    resized = false;
    game_over = false;
}

void Snake::next_step() {
    if(game_over == true) return;

    if(resized == false) {
        for(int i{0}; i < snake_len - 1; i++) {
            snake_arr[i].x = snake_arr[i + 1].x;
            snake_arr[i].y = snake_arr[i + 1].y;
        }
    }

    resized = false;

    switch (direct) {
    case UP:
        snake_arr[snake_len - 1].y -= 1;
        if(snake_arr[snake_len - 1].y < 0) snake_arr[snake_len - 1].y = 24;
        break;
    case RIGHT:
        snake_arr[snake_len - 1].x += 1;
        break;
    case DOWN:
        snake_arr[snake_len - 1].y += 1;
        break;
    case LEFT:
        snake_arr[snake_len - 1].x -= 1;
        if(snake_arr[snake_len - 1].x < 0) snake_arr[snake_len - 1].x = 24;
        break;
    }

    if(snake_arr[snake_len - 1].x % 25 == eat_coordinates.x && snake_arr[snake_len - 1].y % 25 == eat_coordinates.y) add_len();

    for(int i{0}; i < snake_len - 3; i++){
        if(snake_arr[i].x % 25 == snake_arr[snake_len - 1].x % 25 && snake_arr[i].y % 25 == snake_arr[snake_len - 1].y % 25) game_over = true;
    }

    can_turn = true;
}

void Snake::turn(Direction step) {
    if(game_over == true) return;

    if(step == direct || can_turn == false) return;

    if(step == UP && direct == DOWN) return;
    if(step == DOWN && direct == UP) return;

    if(step == RIGHT && direct == LEFT) return;
    if(step == LEFT && direct == RIGHT) return;

    switch (step) {
        case UP: direct = UP; break;
        case RIGHT: direct = RIGHT; break;
        case DOWN: direct = DOWN; break;
        case LEFT: direct = LEFT; break;
    }

    can_turn = false;
}

void Snake::add_len() {
    if(game_over == true) return;

    Coordinates *tmp = snake_arr;

    snake_arr = new Coordinates[snake_len + 1];

    for(int i{0}; i < snake_len; i++){
        snake_arr[i].x = tmp[i].x;
        snake_arr[i].y = tmp[i].y;
    }

    snake_arr[snake_len].x = tmp[snake_len - 1].x;
    snake_arr[snake_len].y = tmp[snake_len - 1].y;

    snake_len++;
    resized = true;

    delete tmp;

    int i{0};

    srand(time(0));
    while(i < snake_len){
        if(i == 0){
            eat_coordinates.x = rand() % 25;
            eat_coordinates.y = rand() % 25;
        }
        if(eat_coordinates.x == snake_arr[i].x % 25 && eat_coordinates.y == snake_arr[i].y % 25) i = 0;
        else i++;
    }
}

void Snake::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    sf::RectangleShape field;
    field.setSize(sf::Vector2f(504, 504));
    field.setOutlineThickness(2.f);
    field.setOutlineColor(sf::Color::Green);
    field.setFillColor(sf::Color::Transparent);
    field.setPosition(0, 0);

    target.draw(field, states);

    sf::Sprite eat(eat_texture);
    eat.setPosition(sf::Vector2f(2 + 20 * eat_coordinates.x, 2 + 20 * eat_coordinates.y));
    target.draw(eat, states);

    sf::Sprite body(body_texture);
    for(int i{0}; i < snake_len - 1; i++){
        body.setPosition(sf::Vector2f(2 + 20 * (snake_arr[i].x % 25), 2 + 20 * (snake_arr[i].y % 25)));
        target.draw(body, states);
    }

    sf::Sprite head(head_texture);
    head.setPosition(sf::Vector2f(2 + 20 * (snake_arr[snake_len - 1].x % 25), 2 + 20 * (snake_arr[snake_len - 1].y % 25)));
    target.draw(head, states);

    if(game_over == true) {
        sf::RectangleShape msg_sh;
        msg_sh.setSize(sf::Vector2f(300, 100));
        msg_sh.setOutlineColor(sf::Color::White);
        msg_sh.setOutlineThickness(5);
        msg_sh.setFillColor(sf::Color::Red);
        msg_sh.setPosition(102, 202);

        target.draw(msg_sh, states);

        sf::Text msg("You lose!", dejavu, 44);
        msg.setFillColor(sf::Color::White);
        msg.setPosition(142, 216);

        target.draw(msg, states);

        msg.setString("Press F2 to restart & ESC to exit");
        msg.setCharacterSize(12);
        msg.setPosition(140, 275);

        target.draw(msg, states);
    }
}
