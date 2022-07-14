#include "Player.hpp"
#include <iostream>

using namespace std;

void Player::find_solution(Level *level, Snake *snake){
    auto pos = snake->getPosition();
    
    while (true){
        int a = rand()%4;
        if (a == 0){

            pos = snake->getPosition();
            pos.first -= 1; //up
            if(level->allowed(pos)){
                m_moves.push_back(UP);
                break;
            }

        } else if (a == 1){
        
            pos = snake->getPosition();
            pos.second += 1; //right
            if(level->allowed(pos)){
                m_moves.push_back(RIGHT);
                break;
            }

        } else if (a == 2){

            pos = snake->getPosition();
            pos.first += 1; //down
            if(level->allowed(pos)){
                m_moves.push_back(DOWN);
                break;
            }

        } else if (a == 3){
        
            pos = snake->getPosition();
            pos.second -= 1; //left
            if(level->allowed(pos)){
                m_moves.push_back(LEFT);
                break;
            }

        }
    }
    //"resolve o problema com base no mapa, a posição atual da cobra e a posição atual da comida"
}

Player::Direction Player::next_move(){
    //sorteia uma ação aleatória que não causa morte
    /*retorna uma ação aleatória entre 0 e 3*/
    Direction acao = m_moves.front();
    m_moves.erase(m_moves.begin());
    return acao;
}