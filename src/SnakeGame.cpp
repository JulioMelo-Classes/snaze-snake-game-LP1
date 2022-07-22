#include "SnakeGame.hpp"

#include "Level.hpp"
#include "Player.hpp"
#include "utils.hpp"

#include <fstream>
#include <iostream>

#include <chrono> //por causa do sleep
#include <thread> //por causa do sleep

using namespace std;

SnakeGame::SnakeGame(string levels, string iaMode)
{
    m_levels_file = levels;
    m_ia_player =new Player(iaMode);
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

        m_currentLevel = 1; // Define o nível atual como o primeiro

        m_snake = new Snake(m_levels[m_currentLevel - 1]->getStartPosition());
        m_levels[m_currentLevel - 1]->getSpawnFood(true);
    }
    else
    {
        std::cout << "Arquivo de níveis com configurações inválidas!" << std::endl;
        m_state = GAME_OVER;
    }
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

void SnakeGame::inputs()
{
    switch (m_state)
    {
    case WAITING_USER: // o jogo bloqueia aqui esperando o usuário digitar a escolha dele
        cin >> std::ws >> m_choice;
        break;
    case WAITING_IA:
        m_action = m_ia_player->next_move(m_levels[m_currentLevel - 1], m_snake);
        break;
    case WIN_SIMULATION: case LEVEL_UP:
        cin >> std::ws >> m_choice;
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
        this->processIAMove();
        this->processFoodColision();

        if (!m_levels[m_currentLevel - 1]->isPath(m_snake->getPosition())) // Se a posição em que a snake se moveu não for permitida
            m_state = LOSE_LIFE;

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
        m_snake->resetAttributes(true);                        // Reinicia os atributos da snake
        m_snake->setPosition(m_levels[0]->getStartPosition()); // reinicia a posição da snake no nível 0
        m_currentLevel = 1;                                    // Reinicia  o nível

        m_state = WAITING_USER; // Após acabar as vidas, o jogo irá perguntar se o jogador quer continuar a simulação
        break;
    case LEVEL_UP:
        if (m_choice == "1")
            m_currentLevel++;
        if (m_choice == "3")
            m_currentLevel = 1; // Reinicia o nível para 1
        // O caso da escolha ser 2, o nível apenas se mantém

        m_levels[m_currentLevel - 1]->getSpawnFood(true);
        m_snake->resetAttributes(false); // Reinicia os atributos da snake sem restaurar as vidas
        m_snake->setPosition(m_levels[m_currentLevel - 1]->getStartPosition());

        m_state = WAITING_IA;
        break;
    case WIN_SIMULATION:
        if(m_choice == "1"){
            m_currentLevel = 1; // Reinicia do nível 1
            m_levels[m_currentLevel - 1]->getSpawnFood(true);
            m_snake->resetAttributes(true);
            m_snake->setPosition(m_levels[m_currentLevel - 1]->getStartPosition());

            m_state = WAITING_IA;           
        }
        else
            m_state = GAME_OVER; // Termina o jogo

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
    //clearScreen();
    switch (m_state)
    {
    case RUNNING:
        cout << endl
             << "Lifes: " << m_snake->getLifes() << " | Score: 0 "
             << "| Foods Eaten: " << m_snake->getFoodsEaten() << " of "
             << m_levels[m_currentLevel - 1]->getFoods() << endl
             << endl;

        printCurrentActionIA();

        for (int j = 0; j < m_levels[m_currentLevel - 1]->getMazeSize().second; j++)
        {
            cout << "\033[4;36m" << j << "\033[0m";
        }
        cout << "\033[4;36m"
             << "|●"
             << "\033[0m";
        cout << endl;
        for (int i = 0; i < m_levels[m_currentLevel - 1]->getMazeSize().first; i++)
        {
            for (int j = 0; j < m_levels[m_currentLevel - 1]->getMazeSize().second; j++)
            {

                if (i == m_snake->getPosition().first && j == m_snake->getPosition().second)
                    cout << "\033[1;32m" << m_snake->getIcon() << "\033[0m";
                else if (i == m_levels[m_currentLevel - 1]->getSpawnFood(false).first && j == m_levels[m_currentLevel - 1]->getSpawnFood(false).second)
                    cout << "\033[31m●\033[0m";
                else
                    cout << m_levels[m_currentLevel - 1]->getElement(i, j);
            }
            cout << "\033[36m"
                 << "|" << i << "\033[0m" << endl;
        }
        cout << "Snake Position: (" << m_snake->getPosition().first << "," << m_snake->getPosition().second
             << ") | Frame: " << m_frameCount
             << " | Food: (" << m_levels[m_currentLevel - 1]->getSpawnFood(false).first << "," << m_levels[m_currentLevel - 1]->getSpawnFood(false).second << ")"
             << endl;
        break;
    case LOSE_LIFE:
        cout << "A snake colidiu e perdeu 1 vida!" << endl;
        break;
    case END_LIFES:
        cout << "Você perdeu todas as vidas. Fim da simulação!" << endl;
        break;
    case LEVEL_UP:
        cout << "Você completou o nível " << m_currentLevel << "." << endl;
        cout << "O que deseja fazer? " << endl;
        cout << "1. Ir para o próximo nível" << endl;
        cout << "2. Reiniciar o nível " << m_currentLevel << endl;
        cout << "3. Reiniciar simulação" << endl;
        break;
    case WIN_SIMULATION:
        cout << "Você venceu a simulação!" << endl;
        cout << "O que deseja fazer? " << endl;
        cout << "1. Reiniciar simulação" << endl;
        cout << "2. Encerrar simulação" << endl;         
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

void SnakeGame::game_over()
{
    delete m_snake; // Desaloca a snake

    for(Level* level: m_levels) // Desaloca os níveis
        delete level;
    
    m_levels.clear(); // Limpa o vetor de níveis
}

void SnakeGame::loop()
{
    render(); // chama um render para a interface inicial
    while (m_state != GAME_OVER)
    {
        inputs(); // nao executado no RUNNING
        update(); // skipa para o render quando no WAITING_IA
        render(); // nao executado no WAITING_IA
        wait(100); // espera 1 segundo entre cada frame
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

void SnakeGame::processIAMove()
{
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
}

void SnakeGame::processFoodColision()
{
    if (m_snake->getPosition() == m_levels[m_currentLevel - 1]->getSpawnFood(false))
    { // Se o snake encostou na comida
        m_snake->eatFood();

        if (m_snake->getFoodsEaten() == m_levels[m_currentLevel - 1]->getFoods())
        {

            m_state = (m_currentLevel + 1 > m_levels.size()) ? WIN_SIMULATION : LEVEL_UP; // Se o próximo nível existe
        }                                                                                 // Se a cobra comeu todas as comidas do mapa
        {
            m_levels[m_currentLevel - 1]->getSpawnFood(true);
        }
    }
}

void SnakeGame::printCurrentActionIA(){
        cout << "COMANDO:";
        if (m_action == Player::UP)
        {
            cout << "\033[1;36m↑ \033[0m";
        }
        else if (m_action == Player::LEFT)
        {
            cout << "\033[1;36m← \033[0m";
        }
        else if (m_action == Player::RIGHT)
        {
            cout << "\033[1;36m→ \033[0m";
        }
        else if (m_action == Player::DOWN)
        {
            cout << "\033[1;36m↓ \033[0m";
        }
        cout << endl;    
}