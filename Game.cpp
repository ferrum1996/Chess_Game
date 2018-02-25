//
// Created by vayo on 24.02.2018.
//

#include "Game.hpp"
#include "Connector.hpp"

int Game::start(sf::RenderWindow &window) {
    std::cout << "Hello, World!" << std::endl;

    sf::Vector2f old_coords, new_coords; //coordinates of start and end positions of a moving figure

    int dx, dy, i, j, k=-1;
   
    char* engine = strdup("stockfish.exe");

    //ConnectToEngine(engine);


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
                //CloseConnection();
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
                    if(f[j].getFaction() == turn){

                         //positioning in the center of the cell
                        int px = (f[j].sprite.getPosition().x+f[j].getWidth()/2)/cell_size;
                        px = cell_size*px +(cell_size-f[j].getWidth())/2;
                        int py = (f[j].sprite.getPosition().y+f[j].getHeight()/2)/cell_size;
                        py = py*cell_size +(cell_size-f[j].getHeight());
                        //end of positioning

                        new_coords = sf::Vector2f(float(px), float(py));
                        moveFigure(j,new_coords, old_coords);
                        std::cout << toBoardCoordinates(f[j].sprite.getPosition(), f[j].getHeight())<< std::endl;
                    }
                }
            }
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::BackSpace){
                    if(!moves.empty()){
                        moveBack();
                    }
                }
            }

        }
        if(moving) f[j].sprite.setPosition(pos.x-dx, pos.y-dy);

        window.clear( );


        window.draw(board.getSprite());
        for(i=0; i<32; i++){
            if(f[i].isAlive())
            window.draw(f[i].sprite);
        }

        window.display();
    }
    return 0;
}


void Game::loadTheBoard(sf::Texture *texture)  //initial placing of figures on the board
{
    int k = 0;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++) {
            int n = board.board[i][j];
            if (n == 0) { continue; }
            f[k].setFigure(n, texture);
            float x = (float) j * board.getSize() + (board.getSize() - f[k].getWidth()) / 2;
            float y = (float) i * board.getSize() + (board.getSize() - f[k].getHeight());
            f[k].sprite.setPosition(x, y);
            k++;
        }
    }
}

//start region of moves
void  Game::moveFigure(int j, sf::Vector2f new_coords, sf::Vector2f old_coords){
    moving = false;
    bool legal;
    int k=-1, i;
    if((legal = (old_coords!=new_coords && f[j].isLegalMove(old_coords, new_coords)))){
        f[j].sprite.setPosition(new_coords.x, new_coords.y);
        for(i=0; i<32; ++i){
            if(i!=j && toBoardCoordinates(f[i].sprite.getPosition(), f[i].getHeight()) ==
                        toBoardCoordinates(f[j].sprite.getPosition(), f[j].getHeight())){
                if (f[j].getFaction() != f[i].getFaction()) { //only different factions can kill
                    f[i].setDead(); //Killing the figure that was in  the cell;
                    k = i;
                    f[i].sprite.setPosition(520, 520);
                    break;
                }
                else{
                    legal = false;   //the player wanted to put figure on another his/her figure
                    break;
                }
            }
        }
    }
    if(legal){
        turn = (turn == 0) ? 1 : 0;
        moves.push(newMove(old_coords, new_coords, j, k)); //adding a move into the history of all moves
        k=-1;
    }
    else f[j].sprite.setPosition(old_coords.x, old_coords.y);
}


void Game::moveBack(){
    int* last_move = moves.top();
    f[last_move[4]].sprite.setPosition(last_move[0], last_move[1]);
    if(last_move[5]!=-1){
        f[last_move[5]].sprite.setPosition(last_move[2], last_move[3]);
        f[last_move[5]].setDead();  //revive the figure
    }
    moves.pop();
    free(last_move);
    turn = (turn==0)? 1:0;
}

//end region of moves

std::string Game::toBoardCoordinates(sf::Vector2f coordSprite, int height){
    std::string coordBoard ="";
    coordBoard += (char)(int(coordSprite.x/cell_size) + 97);
    coordBoard += (char)(int((coordSprite.y+height-cell_size)/cell_size) + 49);
    return coordBoard;
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