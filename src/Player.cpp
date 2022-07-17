#include "Player.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "utils.hpp"
#include <queue>

using namespace std;

void Player::randomIA(Level *level, Snake *snake)
{
    std::vector<Direction> generatedMoves = {}; // Movimentos já sorteados
    bool hasValidMove = false;

    auto pos = make_pair(0, 0);
    Direction dir = UP;

    while (!hasValidMove && generatedMoves.size() != 4)
    { // Enquanto não foi encontrado um movimento válido e ainda não foram sorteados todos os movimentos
        std::random_device rd;
        std::default_random_engine eng(rd());

        std::uniform_int_distribution<int> distrLines(0, 3); // Sorteia um dos 4 movimentos

        int randDir = distrLines(eng);
        pos = snake->getPosition();

        switch (randDir)
        {
        case UP:
            pos.first -= 1;
            dir = UP;
            break;
        case DOWN:
            pos.first += 1;
            dir = DOWN;
            break;
        case RIGHT:
            pos.second += 1;
            dir = RIGHT;
            break;
        case LEFT:
            pos.second -= 1;
            dir = LEFT;
        }

        if (level->allowed(pos))
        { // Se a posição sorteada não for matar a snake
            m_moves.push_back(dir);
            hasValidMove = true; // Encontrou um movimento válido
        }
        if (!isIn(dir, generatedMoves))
            generatedMoves.push_back(dir);
    }

    if (!hasValidMove)
        m_moves.push_back(UP); // Se não achou nenhum movimento válido escolhe qualquer um (Nesse caso, pra cima)
}

int Player::bfs(Level *level, Snake *snake)
{
    pair<int, int> startPosition = level->getStartPosition();
    // UP, LEFT,RIGHT, DOWN
    int lines[] = {-1, 0, 0, 1};
    int columns[] = {0, -1, 1, 0};

    m_visited[startPosition.first][startPosition.second] = true; // marca a posicao como visitada

    queue<Location> paths; // fila com os possiveis caminhos

    Location temp = {startPosition, 0, vector<Direction>()};
    paths.push(temp);
    cout << "reach the loop" << endl;

    while (!paths.empty())
    {
        Location location = paths.front();
        if (location.position == level->getSpawnFruit(false))
        {
            m_moves = location.moveRegister;   // salva os movimentos quando encontra a comida
            return location.distanceFromStart; // retorna a quantidade de movimentos registrados
        }
        paths.pop();

        for (int i = 0; i < 4; i++)
        {
            pair<int, int> pos = make_pair(location.position.first + lines[i], location.position.second + columns[i]);
            if (level->allowed(pos) && !m_visited[pos.first][pos.second])
            {
                m_visited[pos.first][pos.second] = true;
                Location adjacentPosition = {pos, location.distanceFromStart + 1, location.moveRegister};
                // TODO enum
                // adiciona o movimento executado no vetor da posicao
                switch (i)
                {
                case 0:
                    adjacentPosition.moveRegister.push_back(UP);
                    break;
                case 1:
                    adjacentPosition.moveRegister.push_back(LEFT);
                    break;
                case 2:
                    adjacentPosition.moveRegister.push_back(RIGHT);
                    break;
                case 3:
                    adjacentPosition.moveRegister.push_back(DOWN);
                    break;
                default:
                    break;
                }
                paths.push(adjacentPosition);
            }
        }
    }
    return -1; // caso a solucao nao tenha sido encontrada
}

bool Player::find_solution(Level *level, Snake *snake, string mode)
{
    //define a matriz de posicoes visitas pelo tamanho do level
    m_visited.resize(level->getMazeSize().first, vector<bool>(level->getMazeSize().second));
    if (mode == "bfs")
    {
        bfs(level, snake);
    }
    if (mode == "randomIA")
    {
        randomIA(level, snake);
    }
    return false;
}

Player::Direction Player::next_move()
{
    //* imprime os movimentos
    cout << "moves: -";
    for (size_t i = 0; i < m_moves.size(); i++)
    {
        if (m_moves[0] == UP)
        {
            cout << "UP" << '-';
        }
        else if (m_moves[0] == LEFT)
        {
            cout << "LEFT" << '-';
        }
        else if (m_moves[0] == RIGHT)
        {
            cout << "RIGHT" << '-';
        }
        else if (m_moves[0] == DOWN)
        {
            cout << "DOWN" << '-';
        }
    }
    cout << endl;

    Direction acao = m_moves.front();
    m_moves.erase(m_moves.begin());
    return acao;
}