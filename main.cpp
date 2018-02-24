#include <iostream>
#include <SFML/Graphics.hpp>
#include <stack>
#include "Figure.hpp"
#include "Connector.hpp"
#include "ChessBoard.hpp"

Figure f[32];
ChessBoard board;
int turn=1;

void loadTheBoard(sf::Texture* texture);
void toBoardCordinates(sf::Vector2f coordSprite);
int* newMove(sf::Vector2f old_coords, sf::Vector2f new_coords, int index_k, int index_v);
                                                                //k - killer , v - victim;

int main() {
    std::cout << "Hello, World!" << std::endl;

    std::stack <int *> moves; //stack of all moves
    sf::Vector2f old_coords, new_coords; //coordinates of start and end positions of a moving figure
    bool moving = false;


    int dx, dy, i, j, cell_size;
    char* engine = strdup("stockfish.exe");

    ConnectToEngine(engine);

    sf::RenderWindow window(sf::VideoMode(600, 600), "Chess");

    sf::Texture figures;
    if(!figures.loadFromFile("assets/ChessFigures.png")){
        std::cout << "Not loaded" << std::endl;
    }
    loadTheBoard(&figures);

    sf::Texture chessBoard;
    if(!chessBoard.loadFromFile("assets/ChessBoard0.png")){
        std::cout << "Not loaded" << std::endl;
    }

    board.setSprite(&chessBoard);

    cell_size=board.getSize();

    while(window.isOpen()) {
        sf::Event event;


        sf::Vector2i pos = sf::Mouse::getPosition(window);


        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed){
                CloseConnection();
                window.close();
            }

            if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left){

                   for(i=0; i<32; ++i){
                        if(f[i].sprite.getGlobalBounds().contains(pos.x, pos.y) && f[i].getFaction()==turn){
                            moving = true;
                            j = i;
                            dx = (int)(pos.x-f[i].sprite.getPosition().x);
                            dy = (int)(pos.y-f[i].sprite.getPosition().y);
                            old_coords= f[i].sprite.getPosition();
                        }
                    }

                }
            }
            if(event.type == sf::Event::MouseButtonReleased){
                if(event.mouseButton.button == sf::Mouse::Left){
                    moving = false;
                    int px = (f[j].sprite.getPosition().x+f[j].getWidth()/2)/cell_size;
                    px = cell_size*px +(cell_size-f[j].getWidth())/2;
                    int py = (f[j].sprite.getPosition().y+f[j].getHeight()/2)/cell_size;
                    py = py*cell_size +(cell_size-f[j].getHeight());
                    new_coords = sf::Vector2f(float(px), float(py));
                    if(f[j].getFaction() == turn){
                        if(old_coords!=new_coords && f[j].isLegalMove(old_coords, new_coords)){
                            f[j].sprite.setPosition(new_coords.x, new_coords.y);
                            turn = (turn == 0) ? 1 : 0;
                            moves.push(newMove(old_coords, new_coords, j, 0));
                        }
                        else {
                            f[j].sprite.setPosition(old_coords.x, old_coords.y);
                        }
                    }
                    toBoardCordinates(f[j].sprite.getPosition());
                }
            }
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::BackSpace){
                    if(!moves.empty()){
                        int* last_move = moves.top();
                        f[last_move[4]].sprite.setPosition(last_move[0], last_move[1]);
                        moves.pop();
                        free(last_move);
                    }
                }
            }

        }
        if(moving) f[j].sprite.setPosition(pos.x-dx, pos.y-dy);

        window.clear( );


        window.draw(board.getSprite());
        for(i=0; i<32; i++){
            window.draw(f[i].sprite);
        }

        window.display();
    }
    return 0;
}


void loadTheBoard(sf::Texture *texture)
{
    int k=0;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            int n = board.board[i][j];
            if (n==0) {continue;}
            f[k].setFigure(n, texture);
            float x = (float)j*board.getSize()+(board.getSize()-f[k].getWidth())/2;
            float y = (float)i*board.getSize()+(board.getSize()-f[k].getHeight());
            f[k].sprite.setPosition(x, y);
            k++;
        }


}

void toBoardCordinates(sf::Vector2f coordSprite){
    std::string coordBoard ="";
    coordBoard += (char)(int(coordSprite.x/65) + 97);
    coordBoard += (char)(int(coordSprite.y/65) + 49);
    std::cout << coordBoard <<std::endl;
}

int* newMove(sf::Vector2f old_coords, sf::Vector2f new_coords, int index_k, int index_v){
    int* temp = (int*)malloc(sizeof(int)*6);
    temp[0] = (int)old_coords.x;
    temp[1] = (int)old_coords.y;
    temp[2] = (int)new_coords.x;
    temp[3] = (int)new_coords.y;
    temp[4] = index_k;
    temp[5] = index_v;
    return temp;
}