//
// Created by vayo on 19.02.2018.
//

#include "ChessBoard.hpp"
#include <iostream>
const int ChessBoard::getSize() const {
    return cell_size;
}



void ChessBoard::setSprite(sf::Texture *texture) {
    sprite.setTexture(*texture);
    sprite.setScale(sf::Vector2f((float)520/sprite.getTexture()->getSize().x, (float)520/sprite.getTexture()->getSize().y));

}

const sf::Sprite &ChessBoard::getSprite() const{
    return sprite;
}
