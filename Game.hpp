//
// Created by vayo on 24.02.2018.
//

#ifndef CHESS_SFML_C_GAME_HPP
#define CHESS_SFML_C_GAME_HPP
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stack>
#include "Figure.hpp"
#include "ChessBoard.hpp"
#include <cstring>

int* newMove(sf::Vector2f old_coords, sf::Vector2f new_coords, int index_k, int index_v);


class Game {

private:
    Figure f[32];
    ChessBoard board;
    int turn=1;
    int cell_size;
    std::stack <int *> moves;   //stack of all movesv
    bool moving = false;        //flag of moving phase

    void loadTheBoard(sf::Texture* texture);
    void moveFigure(int j, sf::Vector2f new_coords, sf::Vector2f old_coords);
    void moveBack();
    std::string toBoardCoordinates(sf::Vector2f coordSprite, int height);

public:
    int start(sf::RenderWindow &window);
};


#endif //CHESS_SFML_C_GAME_HPP
