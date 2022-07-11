#ifndef Player_hpp
#define Player_hpp
#include <vector>
#include "Level.hpp"
#include "Snake.hpp"

class Player{
    private:
        std::vector<int> m_moves;
    public:
        /**
         * define o conjunto de movimentos ideal para a snake com base no level atual
         * @param level faze atual
         * @param snake a snake
         * @return a próxima ação do jogador
         **/
        void find_solution(Level *level, Snake *snake);
        /**
         * Retorna a próxima ação do jogador um mapeamento de 0-3, representando ir para esquerda, cima, direita, baixo
         * @return a próxima ação do jogador
         **/
        int next_move();
};
#endif //Player_hpp