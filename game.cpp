#include "game.hpp"

#include <iostream>

Game::Game() {
    sf::Image mw_icon;
    if(!(mw_icon.loadFromFile("snake.png"))) exit(1);

    main_win = new sf::RenderWindow(sf::VideoMode(760, 540), "Snake");
    main_win->setIcon(mw_icon.getSize().x, mw_icon.getSize().y, mw_icon.getPixelsPtr());
    main_win->setVerticalSyncEnabled(true);

    if(!(dejavu.loadFromFile("DejaVuSansMono.ttf"))) exit(2);

    if(!(earth.loadFromFile("back.png"))) exit(5);

    if(!(background.loadFromFile("background.png"))) exit(6);

    mw_game.snake_init();
    mw_game.setPosition(sf::Vector2f(18, 18));
}

Game::~Game() {
    delete  main_win;
}

void Game::Run() {
    frame_ptr.restart();

    while(main_win->isOpen()){
        if(main_win->pollEvent(mw_event)){
            if(mw_event.type == sf::Event::Closed) main_win->close();

            if(mw_event.type == sf::Event::KeyPressed) {
                switch (mw_event.key.code) {
                    case sf::Keyboard::Escape : main_win->close(); break;
                    case sf::Keyboard::Up: mw_game.turn(UP); break;
                    case sf::Keyboard::Right: mw_game.turn(RIGHT); break;
                    case sf::Keyboard::Down: mw_game.turn(DOWN); break;
                    case sf::Keyboard::Left: mw_game.turn(LEFT); break;

                    case sf::Keyboard::F2: mw_game.snake_init(); break;
                    default: break;
                }
            }
        }

        if(frame_ptr.getElapsedTime().asSeconds() > 0.1){
            frame_ptr.restart();
            mw_game.next_step();
        }

        main_win->clear();

        sf::Sprite back(background);
        back.setPosition(0, 0);

        main_win->draw(back);

        sf::Sprite earth_back;

        earth_back.setTexture(earth);
        earth_back.setScale(0.48828125, 0.48828125);
        earth_back.setPosition(20, 20);

        main_win->draw(earth_back);

        sf::RectangleShape line;
        line.setSize(sf::Vector2f(500, 1));
        line.setFillColor(sf::Color(91, 74, 58));

        for(int i{1}; i < 25; i++){
            line.setPosition(20, 20 + 20 * i);
            main_win->draw(line);
        }

        line.setSize(sf::Vector2f(1, 500));

        for(int i{1}; i < 25; i++){
            line.setPosition(20 + 20 * i, 20);
            main_win->draw(line);
        }

        main_win->draw(mw_game);

        main_win->display();
    }
}
