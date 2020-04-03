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

#include "game.hpp"

Game::Game() {///usr/share/snake/res/
    sf::Image mw_icon;
    if(!(mw_icon.loadFromFile("res/snake.png")) && !(mw_icon.loadFromFile("/usr/share/snake/res/snake.png"))) exit(1);

    main_win = new sf::RenderWindow(sf::VideoMode(760, 540), "Snake");
    main_win->setIcon(mw_icon.getSize().x, mw_icon.getSize().y, mw_icon.getPixelsPtr());
    main_win->setVerticalSyncEnabled(true);

    if(!(dejavu.loadFromFile("res/DejaVuSansMono.ttf")) && !(dejavu.loadFromFile("/usr/share/snake/res/DejaVuSansMono.ttf"))) exit(2);

    if(!(earth.loadFromFile("res/back.png")) && !(earth.loadFromFile("/usr/share/snake/res/back.png"))) exit(5);

    if(!(background.loadFromFile("res/background.png")) && !(background.loadFromFile("/usr/share/snake/res/background.png"))) exit(6);

    if(!(mw_music.openFromFile("res/Fluffing.ogg")) && !(mw_music.openFromFile("/usr/share/snake/res/Fluffing.ogg"))) exit(7);
    mw_music.setLoop(true);
    mw_music.play();

    mw_game.snake_init();
    mw_game.setPosition(sf::Vector2f(18, 18));

    speed = 0.3;

    timer.restart();
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

                    case sf::Keyboard::F2: mw_game.snake_init(); timer.restart(); break;

                    case sf::Keyboard::F3:
                        if(mw_music.getStatus() == sf::Music::Playing) mw_music.pause();
                        else mw_music.play();
                    break;

                    default: break;
                }
            }
        }

        if(mw_game.get_len() == 3) speed = 0.2;
        if(mw_game.get_len() == 5) speed = 0.15;
        if(mw_game.get_len() == 8) speed = 0.1;
        if(mw_game.get_len() == 15) speed = 0.075;
        if(mw_game.get_len() == 21) speed = 0.06;
        if(mw_game.get_len() > 30) speed = 0.05;

        if(frame_ptr.getElapsedTime().asSeconds() > speed){
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

        sf::Text score("You : " + std::to_string(mw_game.get_len()), dejavu, 30);
        score.setFillColor(sf::Color::White);
        score.setPosition(sf::Vector2f(574, 28));

        main_win->draw(score);

        score.setString(std::to_string(((int)((int)timer.getElapsedTime().asSeconds()) / 60)) + " : " + std::to_string(((int)((int)timer.getElapsedTime().asSeconds()) % 60)));
        score.setPosition(sf::Vector2f(610, 70));

        main_win->draw(score);

        score.setString("How to play?");
        score.setCharacterSize(28);
        score.setPosition(sf::Vector2f(541, 200));

        main_win->draw(score);

        score.setString("F2 - new game");
        score.setCharacterSize(24);
        score.setPosition(sf::Vector2f(548, 250));

        main_win->draw(score);

        score.setString("F3 - sound p/p");
        score.setCharacterSize(24);
        score.setPosition(sf::Vector2f(544, 300));

        main_win->draw(score);

        score.setString("ESC - exit game");
        score.setCharacterSize(24);
        score.setPosition(sf::Vector2f(540, 350));

        main_win->draw(score);

        score.setString("Arrows - to turn");
        score.setCharacterSize(24);
        score.setPosition(sf::Vector2f(534, 400));

        main_win->draw(score);//bbabd0

        score.setString("by KonstantIMP");
        score.setCharacterSize(18);
        score.setFillColor(sf::Color(0xbb, 0xab, 0xd0));
        score.setPosition(sf::Vector2f(560, 475));

        main_win->draw(score);

        main_win->display();
    }
}
