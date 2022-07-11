#include "Player.hpp"
#include <iostream>

using namespace std;

void Player::find_solution(Level *level, Snake *snake){
    
    if(m_moves.size()==0){
        //for(int i=0; i<4; i++)
        auto pos = snake->getPosition();
        pos.first -= 1; //up
        if(level->allowed(pos)){
            m_moves.push_back(0);
            return;
        }
        
        pos = snake->getPosition();
        pos.second += 1; //right
        if(level->allowed(pos)){
            m_moves.push_back(2);
            return;
        }

        pos = snake->getPosition();
        pos.first += 1; //down
        if(level->allowed(pos)){
            m_moves.push_back(1);
            return;
        }
        
        pos = snake->getPosition();
        pos.second -= 1; //left
        if(level->allowed(pos)){
            m_moves.push_back(3);
            return;
        }
    }
    //"resolve o problema com base no mapa, a posição atual da cobra e a posição atual da comida"
}

int Player::next_move(){
    //sorteia uma ação aleatória que não causa morte
    /*retorna uma ação aleatória entre 0 e 3*/
    int acao = m_moves.front();
    m_moves.erase(m_moves.begin());
    return acao;
}