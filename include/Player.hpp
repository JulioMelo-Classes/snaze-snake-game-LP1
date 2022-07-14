#ifndef Player_hpp
#define Player_hpp
#include <vector>
#include "Level.hpp"
#include "Snake.hpp"

/**
 * @brief Classe que implementa um player (Nesse caso uma IA) para o jogo snaze
 */
class Player{
    public:
        /**
         * @brief Descreve as possíveis direções que a IA pode fazer a snake se mover
         */
        enum Direction{
            UP, // Movimento para cima
            DOWN, // Movimento para baixo
            RIGHT, // Movimento para a direita
            LEFT, // Movimento para a esquerda
        };

    private:
        std::vector<Direction> m_moves;
    public:

        /**
         * define o conjunto de movimentos ideal para a snake com base no level atual
         * @param level faze atual
         * @param snake a snake
         * @return a próxima ação do jogador
         **/
        void find_solution(Level *level, Snake *snake);
        /**
         * Retorna a próxima ação do jogador (UP, DOWN, RIGHT ou LEFT)
         * @return a próxima ação do jogador
         **/
        Direction next_move();
};
#endif //Player_hpp