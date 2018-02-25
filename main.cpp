#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <stack>
#include <cstring>
const int MAIN_MENU = 1;
const int GAME = 2;

int main(){
    std::stack<int> game_stack;
    game_stack.push(MAIN_MENU);

    sf::RenderWindow window (sf::VideoMode(600, 600), "Chess");
    char* source = strdup("assets/start_button.png");
    sf::Texture texture;
    texture.loadFromFile(source);

    sf::Sprite sprite(texture);

    while(window.isOpen()){
        sf::Event event;


        sf::Vector2i pos = sf::Mouse::getPosition(window);


        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {

                window.close();
            }

            else if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Space){
                    Game game;
                    game.start(window);
                }
            }
        }

        window.clear();

        window.draw(sprite);
        window.display();
    }
    return 0;
}