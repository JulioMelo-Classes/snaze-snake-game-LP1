#ifndef Snake_hpp
#define Snake_hpp
#include <iostream>
using namespace std;

class Snake{
    private:
        pair<int, int> m_position; // Par (l, c) de linha e coluna em que o Snake se encontra no mapa 
        char m_icon; // Representação gráfica da Snake no mapa
        int m_lifes = 5; // Quantidade de vidas da snake
        int m_length = 1; // Comprimento da snake 
        int m_foodsEaten = 0; // Quantidade de elementos consumidos pela snake

    public:

        /**
         * @brief Constrói um objeto da classe Snake
         * 
         * @param t_position Um par (l, c) em que @b l e @b c são a linha e coluna, respectivamente, que a snake está no mapa.
         */
        Snake(pair<int,int> t_position);

        /**
         * @brief Obter a posição da snake no mapa
         * 
         * @return pair<int, int> com a linha e a coluna, respectivamente, em que a snake está no mapa
         */
        pair<int, int> getPosition();

        /**
         * @brief Configura a posição da snake no mapa
         * 
         * @param t_position Um par com a linha e coluna, respectivamente, em que a snake está no mapa
         */
        void setPosition(std::pair<int,int> t_position);
        
        /**
         * @brief Obter a representação gráfica do snake no mapa
         * 
         * @return char referente ao caractere que representa a cobra no mapa
         */
        char getIcon();

        /**
         * 
         * @brief modifica a posicao da snake com base em um par
         * 
         * @param l linhas
         * @param c colunas
         **/
        void move(int l, int c);
        
        /**
         * @brief Faz a snake perder 1 vida
         */
        void loseLife();

        /**
         * @brief Reinicia os atributos básicos da snake (Vida, comidas ingeridas e comprimento)
         * 
         * @param resetLife se a vida deve ser restaurada ou não
         */
        void resetAttributes(bool resetLife);

        /**
         * @brief Obter a quantidade de vidas da snake
         * 
         * @return int referente a quantidade de vidas da snake
         */
        int getLifes();

        /**
         * @brief Obter a quantidade de comidas ingeridas pela snake
         * 
         * @return int referente à quantidade de comidas obtidas pela snake
         */
        int getFoodsEaten();  

        /**
         * @brief Realiza a ação de comer uma comida do mapa
         * 
         */
        void eatFood();
};
#endif