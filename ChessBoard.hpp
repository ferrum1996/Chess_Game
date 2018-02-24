//
// Created by vayo on 19.02.2018.
//

#ifndef CHESS_SFML_C_CHESSBOARD_HPP
#define CHESS_SFML_C_CHESSBOARD_HPP

#include <SFML/Graphics.hpp>

class ChessBoard {
private:
    const int cell_size=65;
    sf::Sprite sprite;
public:
    int board[8][8] = {
            -4,-2,-3,-5,-6,-3,-2,-4,
            -1,-1,-1,-1,-1,-1,-1,-1,
             0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0,
             1, 1, 1, 1, 1, 1, 1, 1,
             4, 2, 3, 5, 6, 3, 2, 4
    };
    const int getSize() const;

    void setSprite(sf::Texture *texture);

    const sf::Sprite &getSprite() const;
};




#endif //CHESS_SFML_C_CHESSBOARD_HPP
