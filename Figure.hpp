//
// Created by vayo on 19.02.2018.
//

#ifndef CHESS_SFML_C_FIGURE_HPP
#define CHESS_SFML_C_FIGURE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

const int KNIGHT = 2;
const int ELEPHANT = 3;
const int TOWER = 4;
const int QUEEN = 5;
const int KING = 6;
const int PAWN = 1;

const int cell = 65;

const int figure_gap = 60;
const int faction_gap =88;

const int pawn_width = 36;
const int pawn_height =50;

const int knight_width = 44;
const int knight_height =64;

const int officer_width = 44;
const int officer_height =74;

class Figure {
protected :
    int height;
    int width;
    int faction; //colour of a figure
    int index;

public:
    sf::Sprite sprite;
    void setFigure(int type, sf::Texture *texture);

    bool isLegalMove(sf::Vector2f old_coords, sf::Vector2f new_coords);

    int getIndex() const;
    int getHeight() const;
    int getWidth() const;

    int getFaction() const;
};

bool isPawnLegalMove (sf::Vector2f old_coords, sf::Vector2f new_coords);
bool isKnightLegalMove (sf::Vector2f old_coords, sf::Vector2f new_coords);
bool isTowerLegalMove (sf::Vector2f old_coords, sf::Vector2f new_coords);
bool isElephantLegalMove (sf::Vector2f old_coords, sf::Vector2f new_coords);
bool isRoyalLegalMove (sf::Vector2f old_coords, sf::Vector2f new_coords, bool queen);
//                                                                       ^^^^^^^^
//bool queen is for checking whether figure is queen or not, if not then figure is King, means the figure
//able to move the same way but distance = 1




#endif //CHESS_SFML_C_FIGURE_HPP
