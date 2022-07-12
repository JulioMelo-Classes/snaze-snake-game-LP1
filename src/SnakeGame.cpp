#include "SnakeGame.hpp"

#include "Player.hpp"
#include "Level.hpp"
#include "utils.hpp"

#include <iostream>
#include <fstream>

#include <chrono> //por causa do sleep
#include <thread> //por causa do sleep

using namespace std;

SnakeGame::SnakeGame(string levels){
    m_levels_file=levels;
    m_choice = "";
    m_frameCount = 0;

    ifstream levelFile(m_levels_file);
    string line;

    if(levelFile.is_open()){
        while(!levelFile.eof()){
            getline(levelFile, line);
            
            vector<string> parts = split(line, ' ');
            
            int lines = stoi(parts[0]);
            int columns = stoi(parts[1]);
            int foods = stoi(parts[2]);
            
            Level *level = new Level(lines, columns, foods);

            for(int l=0; l < lines; l++){
                getline(levelFile, line);
                string levelLine = "";
                
                for(int c=0; c < columns; c++){
                    if(line[c]=='V') level->setStartPosition(make_pair(l, c));

                    levelLine+=line[c];
                }
                
                level->insertLine(levelLine, l);
            }

            m_levels.push_back(level);
        }
    }
    start();
}

void SnakeGame::start(){

    m_state = WAITING_USER; //estado inicial é WAITING_USER, mas poderia ser outro

    m_ia_player = Player();
    cout << m_levels[0]->getStartPosition().first << "," << m_levels[0]->getStartPosition().second << endl;
    m_snake = new Snake(m_levels[0]->getStartPosition());
    m_levels[0]->getSpawnFruit(true);
}



void SnakeGame::inputs(){
    switch(m_state){
        case WAITING_USER: //o jogo bloqueia aqui esperando o usuário digitar a escolha dele
            cin>>std::ws>>m_choice;
            break;
        case WAITING_IA:
            //TODO - IA ALEATORIA
            m_ia_player.find_solution(m_levels[0], m_snake);
            m_action = m_ia_player.next_move();
            break;
        default:
            //nada pra fazer aqui
            break;
    }
}

void SnakeGame::update(){
    //atualiza o estado do jogo de acordo com o resultado da chamada de "process_actions"
    switch(m_state){
        case RUNNING:
            //if(m_frameCount>0 && m_frameCount%10 == 0) //depois de 10 frames o jogo pergunta se o usuário quer continuar
            //    m_state = WAITING_USER;
            /*atualiza a posição do pacman de acordo com a escolha*/
            if(m_action == 0){ //up
                m_snake->move(-1,0);
                int linha = m_snake->getPosition().first;
                if(linha < 0)
                    m_snake->setPosition({0, m_snake->getPosition().second});
            }
            else if(m_action == 1){ //down
                m_snake->move(1,0);
                int linha = m_snake->getPosition().first;
                if(linha >= m_levels[0]->getMazeSize().first)
                    m_snake->setPosition({m_levels[0]->getMazeSize().first -1, m_snake->getPosition().second});
            }
            else if(m_action == 2){ //right
                m_snake->move(0,1);
                int coluna = m_snake->getPosition().second;
                if(coluna >= m_levels[0]->getMazeSize().second)
                    m_snake->setPosition({m_snake->getPosition().first,  m_levels[0]->getMazeSize().second - 1});
            }
            else{ //left
                m_snake->move(0,-1);
                int coluna = m_snake->getPosition().second;
                if(coluna  < 0)
                    m_snake->setPosition({m_snake->getPosition().first, 0});
            }
            //sempre depois de executar "running" uma vez
            //o jogo pergunta para a IA qual sua escolha
            if(m_state == RUNNING) //se ainda form running (não pediu para esperar pelo user)
                m_state = WAITING_IA;
            break;
        case WAITING_USER: //se o jogo estava esperando pelo usuário então ele testa qual a escolha que foi feita
            if(m_choice == "n"){
                m_state = GAME_OVER;
                game_over();
            }
            else{
                //pode fazer alguma coisa antes de fazer isso aqui
                m_state = WAITING_IA;
                
            }
            break;
        case WAITING_IA: //Esperando pela IA
            /*alguma coisa aqui*/
            m_state = RUNNING; //depois de processar coisas da IA sempre passa para Running
            break;
        default:
            //nada pra fazer aqui
            break;
    }
}


void SnakeGame::render(){
    //clearScreen();
    switch(m_state){
        case RUNNING:
            for(int i=0; i<m_levels[0]->getMazeSize().first ;i++){
                for(int j=0;j<m_levels[0]->getMazeSize().second ; j++){
                    
                    if(i == m_snake->getPosition().first && j == m_snake->getPosition().second)
                        cout<<m_snake->getIcon();
                    else if(i == m_levels[0]->getSpawnFruit(false).first && j == m_levels[0]->getSpawnFruit(false).second)
                        cout<< "F";
                    else
                        cout<<m_levels[0]->getElement(i,j);
                }
                cout<<endl;
            }
            cout<<"l,c: " << m_snake->getPosition().first << "," << m_snake->getPosition().second << " fc: "<<m_frameCount<<endl;
            break;
        case WAITING_USER:
            cout<<"Você quer iniciar/continuar o jogo? (s/n)"<<endl;
            break;
        case GAME_OVER:
            cout<<"O jogo terminou!"<<endl;
            break;
    }
    m_frameCount++;
}

/**
 * @brief função auxiliar para fazer o programa esperar por alguns milisegundos
 * @param ms a quantidade de segundos que o programa deve esperar
 */
void wait(int ms){
    this_thread::sleep_for(chrono::milliseconds(ms));
}

/**
 * @brief função auxiliar para limpar o terminal
 */
void clearScreen(){
    //some C++ voodoo here ;D
    #if defined _WIN32
        system("cls");
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
    #elif defined (__APPLE__)
        system("clear");
    #endif
}

void SnakeGame::game_over(){
}

void SnakeGame::loop(){
    render(); //chama um render para a interface inicial
    while(m_state != GAME_OVER){
        inputs();
        update();
        render();
        wait(50);// espera 1 segundo entre cada frame
    }
}
