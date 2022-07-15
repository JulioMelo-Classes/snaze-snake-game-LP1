#include "Player.hpp"
#include <iostream>
#include <random>
#include "utils.hpp"


using namespace std;

void Player::find_solution(Level *level, Snake *snake){
    std::vector<Direction> generatedMoves = {}; // Movimentos já sorteados    
    bool hasValidMove = false;

    auto pos = make_pair(0, 0);
    Direction dir = UP;


    while (!hasValidMove && generatedMoves.size()!=4){ // Enquanto não foi encontrado um movimento válido e ainda não foram sorteados todos os movimentos
        std::random_device rd;
        std::default_random_engine eng(rd());

        std::uniform_int_distribution<int> distrLines(0, 3); // Sorteia um dos 4 movimentos        

        int randDir = distrLines(eng);
        pos = snake->getPosition();

        switch(randDir){
            case UP:
                pos.first -=1;
                dir = UP;
                break;
            case DOWN:
                pos.first +=1;
                dir = DOWN;
                break;
            case RIGHT:
                pos.second +=1;
                dir = RIGHT;
                break;
            case LEFT:
                pos.second -=1;
                dir = LEFT;
        }
    
        if(level->allowed(pos)){ // Se a posição sorteada não for matar a snake
            m_moves.push_back(dir);
            hasValidMove = true; // Encontrou um movimento válido
        }if(!isIn(dir, generatedMoves)) generatedMoves.push_back(dir);
    }

    if(!hasValidMove) m_moves.push_back(UP); // Se não achou nenhum movimento válido escolhe qualquer um (Nesse caso, pra cima)

    //"resolve o problema com base no mapa, a posição atual da cobra e a posição atual da comida"
}

Player::Direction Player::next_move(){
    //sorteia uma ação aleatória que não causa morte
    /*retorna uma ação aleatória entre 0 e 3*/
    Direction acao = m_moves.front();
    m_moves.erase(m_moves.begin());
    return acao;
}