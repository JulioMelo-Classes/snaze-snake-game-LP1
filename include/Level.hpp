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
        int m_startLine, m_startColumn;
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

        vector<string> getLevel(int lvl); // MÉTODO PARA TESTE

        pair<int, int> getStartPosition();

        pair<int, int> getMazeSize();
        
        char getElement(int l, int c);

        bool allowed(std::pair<int,int> pos);
};

#endif
