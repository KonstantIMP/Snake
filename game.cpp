#include "game.hpp"

Game::Game() {
    sf::Image mw_icon;
    if(!(mw_icon.loadFromFile("snake.png"))) exit(1);

    main_win = new sf::RenderWindow(sf::VideoMode(760, 540), "Snake");
    main_win->setIcon(mw_icon.getSize().x, mw_icon.getSize().y, mw_icon.getPixelsPtr());
    main_win->setVerticalSyncEnabled(true);

    if(!(dejavu.loadFromFile("DejaVuSansMono.ttf"))) exit(2);

    mw_game.snake_init();
    mw_game.setPosition(sf::Vector2f(19, 19));
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
                    default: break;
                }
            }
        }

        if(frame_ptr.getElapsedTime().asSeconds() > 0.1){
            frame_ptr.restart();
            mw_game.next_step();
        }

        main_win->clear();

        main_win->draw(mw_game);

        main_win->display();
    }
}
