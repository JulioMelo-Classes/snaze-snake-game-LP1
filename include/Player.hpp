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

        /**
         * @brief estrutura para armazenar um possivel caminho da snake e a distancia percorrida
         */
        struct Location
        {
            pair<int, int> position;
            int distanceFromStart;
            vector<Direction> moveRegister;
        };

    private:
        std::string m_mode; // Modo da IA (find ou random)
        std::vector<Direction> m_moves; // movimentos a serem exutados pelo player
        vector<vector<bool>> m_visited;//matriz com os caminhos ja visitados

        /**
         * @brief metodo da IA baseado em busca em largura(Breadth-First Search)
         * 
         * @param level faze atual
         * @param snake a cobra
         * @return int a quantidade de movimentos ate chegar na comida
         */
        int  bfs(Level *level, Snake *snake);

        /**
         * @brief medo da IA baseado na selecao aleatoria de movimentos
         * 
         * @param level faze atual
         * @param snake a cobra
         */
        void randomIA(Level *level, Snake *snake); 

    public:
        /**
         * @brief Constrói um objeto da classe Player
         * 
         * @param mode Modo da ia (find ou random)
         */
        Player(string mode);

        /**
         * define o conjunto de movimentos ideal para a snake com base no level atual
         * @param level fase atual
         * @param snake a snake
         * @return a próxima ação do jogador
         **/
        bool find_solution(Level *level, Snake *snake);

        /**
         * @brief limpa e redimensiona a matriz de posicoes visitadas
         * 
         */
        void resetVisited(Level *level);
        
        /**
         * Retorna a próxima ação do jogador (UP, DOWN, RIGHT ou LEFT)
         * 
         * @param level Nível que está sendo jogaod
         * @param snake snake que está jogando
         * @return a próxima ação do jogador
         **/
        Direction next_move(Level* level, Snake* snake);
};
#endif //Player_hpp