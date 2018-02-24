//
// Created by vayo on 19.02.2018.
//

#include "Figure.hpp"

void Figure::setFigure(int type,sf::Texture *texture) {
    this->index=abs(type);                   //type of figure
    this->faction = (type<0)? 0:1;      //black or white?
    if(index == PAWN){
        this->height = pawn_height;
        this->width = pawn_width;
    }
    else if(index == KNIGHT || index == TOWER){       //tower and knight have the same size
        this->height = knight_height;
        this->width = knight_width;
    }
    else if(index == QUEEN || index == KING || index == ELEPHANT){
        this->height = officer_height;
        this->width = officer_width;
    }
    this->sprite.setTexture(*texture);
    int x1 =(index-1) * figure_gap;
    int y1 = faction * faction_gap;
    this->sprite.setTextureRect(sf::IntRect(x1, y1, width, height));

}

bool Figure::isLegalMove(sf::Vector2f old_coords, sf::Vector2f new_coords){
    switch (index){
        case PAWN:
            return isPawnLegalMove(old_coords, new_coords);
        case KNIGHT:
            return isKnightLegalMove(old_coords, new_coords);
        case ELEPHANT:
            return isElephantLegalMove(old_coords, new_coords);
        case TOWER:
            return isTowerLegalMove(old_coords, new_coords);
        case QUEEN:
            return isRoyalLegalMove(old_coords, new_coords, true);
        case KING:
            return isRoyalLegalMove(old_coords, new_coords, false);
    }
    return false;
}


int Figure::getHeight() const {
    return height;
}

int Figure::getWidth() const {
    return width;
}

int Figure::getIndex() const {
    return index;
}

int Figure::getFaction() const {
    return faction;
}



//Checking Legality of moves by figure type

bool isPawnLegalMove (sf::Vector2f old_coords, sf::Vector2f new_coords){
    return true;
}

bool isKnightLegalMove (sf::Vector2f old_coords, sf::Vector2f new_coords){
    if((abs(old_coords.x - new_coords.x)/cell==1) && (abs(old_coords.y - new_coords.y)/cell==2) )
    return true;

    if((abs(old_coords.x - new_coords.x)/cell == 2) && (abs(old_coords.y - new_coords.y)/cell==1) )
    return true;

    return false;
}

bool isTowerLegalMove (sf::Vector2f old_coords, sf::Vector2f new_coords){
    if(old_coords.x == new_coords.x || old_coords.y == new_coords.y){
        return true;
    }
    return false;
}

bool isElephantLegalMove (sf::Vector2f old_coords, sf::Vector2f new_coords){
    if((old_coords.x - old_coords.y) == (new_coords.x - new_coords.y)){
        return true;
    }
    if((old_coords.x + old_coords.y) == (new_coords.x + new_coords.y)){
        return true;
    }
    return false;
}

bool isRoyalLegalMove (sf::Vector2f old_coords, sf::Vector2f new_coords, bool queen){
    if(queen){
        return (isTowerLegalMove(old_coords, new_coords) || isElephantLegalMove(old_coords, new_coords));
    }
    else{
        if(isTowerLegalMove(old_coords, new_coords) || isElephantLegalMove(old_coords, new_coords)){
            int length = (int)sqrt( (old_coords.x/cell - new_coords.x/cell)*(old_coords.x/cell - new_coords.x/cell)
                       + (old_coords.y/cell - new_coords.y/cell)*(old_coords.y/cell - new_coords.y/cell));
            std::cout << length <<std::endl;
            if(length == 1){
                std::cout << "Is King" << std::endl;
                return true;
            }
        }
    }
    return false;

}