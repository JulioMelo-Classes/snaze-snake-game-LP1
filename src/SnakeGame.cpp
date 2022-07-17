#include "SnakeGame.hpp"

#include "Level.hpp"
#include "Player.hpp"
#include "utils.hpp"

#include <fstream>
#include <iostream>

#include <chrono> //por causa do sleep
#include <thread> //por causa do sleep

using namespace std;

SnakeGame::SnakeGame(string levels)
{
    m_levels_file = levels;
    m_choice = "";
    m_frameCount = 0;

    ifstream levelFile(m_levels_file);
    string line;

    if (levelFile.is_open())
    {
        while (!levelFile.eof())
        {
            getline(levelFile, line);

            vector<string> parts = split(line, ' ');

            int lines = stoi(parts[0]);
            int columns = stoi(parts[1]);
            int foods = stoi(parts[2]);

            Level *level = new Level(lines, columns, foods);

            for (int l = 0; l < lines; l++)
            {
                getline(levelFile, line);
                string levelLine = "";

                for (int c = 0; c < columns; c++)
                {
                    if (line[c] == 'V')
                    {
                        level->setStartPosition(make_pair(l, c));
                        line[c] = ' '; // Limpa o lugar onde o lugar inicial para que não sejam impressas mais de uma snake no render
                    }

                    levelLine += line[c];
                }

                level->insertLine(levelLine, l);
            }

            m_levels.push_back(level);
        }
    }
    start();
}

void SnakeGame::start()
{

    if (this->hasValidLevels())
    {
        m_state = WAITING_USER; // estado inicial é WAITING_USER, mas poderia ser outro

        m_currentLevel = 1;

        m_ia_player = Player();

        m_snake = new Snake(m_levels[m_currentLevel - 1]->getStartPosition());
        m_levels[m_currentLevel - 1]->getSpawnFruit(true);
    }
    else
    {
        std::cout << "Arquivo de níveis com configurações inválidas!" << std::endl;
        m_state = GAME_OVER;
    }
}

bool SnakeGame::hasValidLevels()
{
    for (auto level : m_levels)
    {
        auto levelSize = level->getMazeSize();

        if (levelSize.first <= 0 || levelSize.second <= 0 || level->getFoods() <= 0)
            return false;
    }
    return true;
}

void SnakeGame::inputs()
{
    switch (m_state)
    {
    case WAITING_USER: // o jogo bloqueia aqui esperando o usuário digitar a escolha dele
        cin >> std::ws >> m_choice;
        // TODO IA - busca em largura
        m_ia_player.find_solution(m_levels[m_currentLevel - 1], m_snake, "bfs"); //* MODO BFS IA <---
        break;
    case WAITING_IA:
        // m_ia_player.find_solution(m_levels[m_currentLevel - 1], m_snake, "randomIA"); //* MODO RANDOM IA <---
        m_action = m_ia_player.next_move();
        break;
    default:
        // nada pra fazer aqui
        break;
    }
}

void SnakeGame::update()
{
    // atualiza o estado do jogo de acordo com o resultado da chamada de "process_actions"
    switch (m_state)
    {
    case RUNNING:
        // if(m_frameCount>0 && m_frameCount%10 == 0) //depois de 10 frames o jogo pergunta se o usuário quer continuar
        //     m_state = WAITING_USER;
        /*atualiza a posição do pacman de acordo com a escolha*/
        if (m_action == Player::UP)
        { // UP
            m_snake->move(-1, 0);
        }
        else if (m_action == Player::DOWN)
        { // DOWN
            m_snake->move(1, 0);
        }
        else if (m_action == Player::RIGHT)
        { // RIGHT
            m_snake->move(0, 1);
        }
        else if (m_action == Player::LEFT)
        { // LEFT
            m_snake->move(0, -1);
        }

        if (m_snake->getPosition() == m_levels[m_currentLevel - 1]->getSpawnFruit(false))
        { // Se o snake encostou na comida
            m_snake->eatFood();
            m_levels[m_currentLevel - 1]->getSpawnFruit(true); // MODIFICAR DEPOIS PARA CONSIDERAR O CASO DE COMER A ÙLTIMA COMIDA DO MAPA
        }

        if (!m_levels[m_currentLevel - 1]->allowed(m_snake->getPosition())) // Se a posição em que a snake se moveu não for permitida
            m_state = LOSE_LIFE;

        // sempre depois de executar "running" uma vez
        // o jogo pergunta para a IA qual sua escolha
        if (m_state == RUNNING) // se ainda form running (não pediu para esperar pelo user)
            m_state = WAITING_IA;
        break;
    case LOSE_LIFE:
        m_snake->loseLife();                                                    // Cobra perde 1 vida
        m_snake->setPosition(m_levels[m_currentLevel - 1]->getStartPosition()); // Reinicia a posição da cobra no nível

        if (m_snake->getLifes() == 0)
            m_state = END_LIFES; // Se a cobra não tiver mais vidas
        else
            m_state = WAITING_USER;

        break;
    case END_LIFES:
        delete m_snake;                                       // Deleta a snake atual
        m_snake = new Snake(m_levels[0]->getStartPosition()); // Cria outra snake

        m_state = WAITING_USER; // Após acabar as vidas, o jogo irá perguntar se o jogador quer continuar a simulação
        break;
    case WAITING_USER: // se o jogo estava esperando pelo usuário então ele testa qual a escolha que foi feita
        if (m_choice == "n")
        {
            m_state = GAME_OVER;
            game_over();
        }
        else
        {
            // pode fazer alguma coisa antes de fazer isso aqui
            m_state = WAITING_IA;
        }
        break;
    case WAITING_IA: // Esperando pela IA
        /*alguma coisa aqui*/
        m_state = RUNNING; // depois de processar coisas da IA sempre passa para Running
        break;
    default:
        // nada pra fazer aqui
        break;
    }
}

void SnakeGame::render()
{
    // clearScreen();
    switch (m_state)
    {
    case RUNNING:
        cout << "Lifes: " << m_snake->getLifes() << " | Score: 0 "
             << "| Foods Eaten: " << m_snake->getFoodsEaten() << " of "
             << m_levels[m_currentLevel - 1]->getFoods() << endl
             << endl;

        for (int i = 0; i < m_levels[0]->getMazeSize().first; i++)
        {
            for (int j = 0; j < m_levels[0]->getMazeSize().second; j++)
            {

                if (i == m_snake->getPosition().first && j == m_snake->getPosition().second)
                    cout << m_snake->getIcon();
                else if (i == m_levels[0]->getSpawnFruit(false).first && j == m_levels[0]->getSpawnFruit(false).second)
                    cout << "F";
                else
                    cout << m_levels[0]->getElement(i, j);
            }
            cout << endl;
        }
        cout << "Snake Position: (" << m_snake->getPosition().first << "," << m_snake->getPosition().second << ") | Frame: " << m_frameCount << endl
             << endl;
        break;
    case LOSE_LIFE:
        cout << "A snake colidiu e perdeu 1 vida!" << endl;
        break;
    case END_LIFES:
        cout << "Você perdeu todas as vidas. Fim da simulação!" << endl;
        break;
    case WAITING_USER:
        cout << "Você quer iniciar/continuar o jogo? (s/n)" << endl;
        break;
    case GAME_OVER:
        cout << "O jogo terminou!" << endl;
        break;
    }
    m_frameCount++;
}

/**
 * @brief função auxiliar para fazer o programa esperar por alguns milisegundos
 * @param ms a quantidade de segundos que o programa deve esperar
 */
void wait(int ms)
{
    this_thread::sleep_for(chrono::milliseconds(ms));
}

/**
 * @brief função auxiliar para limpar o terminal
 */
void clearScreen()
{
// some C++ voodoo here ;D
#if defined _WIN32
    system("cls");
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined(__APPLE__)
    system("clear");
#endif
}

void SnakeGame::game_over()
{
}

void SnakeGame::loop()
{
    render(); // chama um render para a interface inicial
    while (m_state != GAME_OVER)
    {
        cout << "\033[1;32mSTATUS\033[0m: ";
        if (m_state == WAITING_IA)
        {
            cout << "Aguardando os dados da IA..." << endl;
        }
        else if(m_state == WAITING_USER)
        {
            cout << "Aguardando os dados do usuario..." << endl;

        } else if (m_state == RUNNING){
            cout << "Processando os dados e renderizando o level" << endl;
        }
        inputs();  // nao executado no RUNNING
        render();  // nao executado no WAITING_IA
        update();  // skipa para o render quando no WAITING_IA
        wait(100); // espera 1 segundo entre cada frame
    }
}
