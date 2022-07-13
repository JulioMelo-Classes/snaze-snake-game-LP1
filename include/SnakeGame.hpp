#ifndef SnakeGame_hpp
#define SnakeGame_hpp
#include <iostream>
#include <vector>

#include "Level.hpp"

#include "Player.hpp"
#include "Snake.hpp"
using namespace std;

class SnakeGame{
    public:
        /**
        * @brief descreve os possíveis estados do jogo, fique à vontade para adicionar outros se necessário
        **/
        enum GameStates{
            RUNNING, // quando o jogo está executando o estado é RUNNING
            LOSE_LIFE, // Quando a snake perde uma vida
            GAME_OVER, // quando o jogo deve terminar o estado é GAME_OVER
            WAITING_USER, // quando o jogo deve esperar por uma entrada do usuário o estado é WAITING_USER
            WAITING_IA // usualmente o jogo está esperando por comandos da IA, neste caso o estado é WAITING_IA
        };
    private:
        Snake* m_snake;
        vector<Level*> m_levels; // Vector contendo os níveis da simulação
        unsigned int m_currentLevel; // Nível que está sendo jogado

        int m_frameCount; // contador de frames, usado apenas como exemplo
        string m_choice; // usado na função inputs para guardar a escolha do usuário
        GameStates m_state; // guarda o estado do jogo
        string m_levels_file; // arquivo com os níveis do jogo
        Player m_ia_player; // instancia da classe Player responsável pela IA do jogo
        Player::direction m_action; // Representa a ação escolhida pela IA


    public:
        /**
        * @brief construtor padrão, fique à vontade para adicionar parâmetros se desejar
        **/
        SnakeGame(string levels);

        /**
        * @brief chamado no main, este loop executa o jogo indefinidamente até que o usuário escolha terminar!
        */
        void loop();

    private:
        /**
         * @brief Verifica se os níveis de m_levels são válidos (Tem quantidade de linhas, colunas e comidas maiores do que 0)
         * 
         * @return true se os níveis são válidos, false caso contrário 
         */
        bool hasValidLevels();

        /**
        * @brief realiza a inicialização geral do jogo, fique à vontade para adicionar parâmetros se achar que deve
        **/
        void start();

        /**
        * @brief processa as entradas do jogador
        **/
        void inputs();

        /**
        * @brief atualiza o estado do jogo, basicamente movendo os objetos, sorteando novas posições de comida
        **/
        void update();

        /**
        * @brief testa o estado do jogo e desenha a tela correspondente
        **/
        void render();

        /**
        * @brief é chamada quando o jogo termina a fim de destruir/resetar elementos do estado do jogo
        **/
        void game_over();

};

#endif //SnakeGame_hpp