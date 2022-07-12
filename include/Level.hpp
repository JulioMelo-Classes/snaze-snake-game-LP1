#ifndef Level_HPP
#define Level_HPP

#include <vector>
#include <string>
using namespace std;

/*Define um nível no snake game*/
class Level{
    private:
        int m_foods; // Quantidade de comida que o nível possui
        int m_lines; // Quantidade de linhas que o mapa do nível possui
        int m_columns; // Quantidade de colunas que o mapa do nível possui
        pair<int, int> m_startPosition; // Posição inicial do mapa
        pair<int, int> m_fruitPosition;
        std::vector<std::string> m_map; // Um vetor de strings representando o mapa do nível 

    public:
        /**
         * @brief Constrói um objeto da classe Level
         * 
         * @param lines Quantidade de linhas que o mapa do nível possui
         * @param columns Quantidade de colunas que o mapa do nível possui
         * @param foods Quantidade de comidas que o nível terá
         */
        Level(int lines,int columns,int foods);

        /**
         * @brief Insere uma linha
         * 
         * @param line Linha a ser inserida
         * @param position Posição em que a linha vai ser inserida (De 0 até m_lines - 1)
         */
        void insertLine(std::string line,int position);

        void printLevel(); // MÉTODO PARA TESTE

        /**
         * @brief Retorna a posição inicial (Onde o personagem nasce) do mapa do level
         * 
         * @return pair<int, int> com o número da linha e coluna, respectivamente, da posição inicial
         */
        pair<int, int> getStartPosition();

        /**
         * @brief Configurar a posição inicial do mapa
         * 
         * @param position Par (l, c) da posição inicial, onde @b l é o número da linha e @b c o número da coluna
         */
        void setStartPosition(pair<int, int> position);

        /**
         * @brief Pegar a quantidade de linhas e colunas do nível
         * 
         * @return pair<int, int> com a quantidade de linhas (first) e colunas (second) do mapa
         */
        pair<int, int> getMazeSize();
        
        /**
         * @brief Retorna a quantidade de comidas do level
         * 
         * @return int referente à quantidade de comidas do level
         */
        int getFoods();
        
        /**
         * @brief Pegar o valor de um elemento específico do mapa
         * 
         * @param l Linha do elemento
         * @param c Coluna do elemento
         * @return char do elemento que está na linha e coluna correspondente
         */
        char getElement(int l, int c);

        /**
         * @brief Chega se a movimentação para uma dada posição é válida no mapa
         * 
         * @param pos posicao de destino
         * 
         * @return true se o movimento for permitido, false caso contrário
         */
        bool allowed(std::pair<int,int> pos);

        /**
         * @brief Sorteia uma posição para a comida
         * 
         * @param spawn Se já tem uma comida spawnada no mapa
         * @return pair<int, int> A posição da comida no mapa
         */
        pair<int, int> getSpawnFruit(bool spawn);
};

#endif
