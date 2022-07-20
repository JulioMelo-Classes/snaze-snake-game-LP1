#include "Player.hpp"
#include "utils.hpp"
#include <algorithm>
#include <iostream>
#include <queue>
#include <random>
#include <vector>

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

        if (level->isPath(pos))
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

bool Player::backTracking(Level *level, Snake *snake, pair<int, int> position)
{
    m_visited[position.first][position.second] = true;
    if (position == level->getSpawnFood(false))
    {
        return true;
    }
    else
    {
        if (level->isPath(make_pair(position.first + 1, position.second)) && !m_visited[position.first + 1][position.second])
        {
            backTracking(level, snake, make_pair(position.first + 1, position.second));
        }

        if (level->isPath(make_pair(position.first - 1, position.second)) && !m_visited[position.first - 1][position.second])
        {
            backTracking(level, snake, make_pair(position.first - 1, position.second));
        }

        if (level->isPath(make_pair(position.first, position.second + 1)) && !m_visited[position.first][position.second + 1])
        {
            backTracking(level, snake, make_pair(position.first, position.second + 1));
        }

        if (level->isPath(make_pair(position.first, position.second - 1)) && !m_visited[position.first][position.second - 1])
        {
            backTracking(level, snake, make_pair(position.first, position.second - 1));
        }
    }
    return false;
}

int Player::bfs(Level *level, Snake *snake)
{
    pair<int, int> startPosition = snake->getPosition();
    // UP, LEFT,RIGHT, DOWN
    int lines[] = {-1, 0, 0, 1};
    int columns[] = {0, -1, 1, 0};

    m_visited[startPosition.first][startPosition.second] = true; // marca a posicao como visitada

    queue<Location> paths; // fila com os possiveis caminhos

    Location temp = {startPosition, 0, vector<Direction>()};
    
    paths.push(temp);
    pair<int, int> food = level->getSpawnFood(false);

    while (!paths.empty())
    {

        Location location = paths.front();
        if (location.position == food)
        {
            m_moves = location.moveRegister;   // salva os movimentos quando encontra a comida
            return location.distanceFromStart; // retorna a quantidade de movimentos registrados
        }
        paths.pop();

        for (int i = 0; i < 4; i++)
        {
            pair<int, int> pos = make_pair(location.position.first + lines[i], location.position.second + columns[i]);
            if (level->isPath(pos) && !m_visited[pos.first][pos.second])
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
void Player::resetVisited(Level *level)
{
    // define a matriz de posicoes visitas pelo tamanho do level
    m_visited = vector<vector<bool>>(level->getMazeSize().first, vector<bool>(level->getMazeSize().second));

    for (size_t i = 0; i < m_visited.size(); i++)
    {
        for (size_t j = 0; j < m_visited[i].size(); j++)
        {
            m_visited[i][j] = false;
        }
    }
}

Player::Direction Player::next_move()
{
    if (!m_moves.empty())
    {
        Direction acao = m_moves.front();
        m_moves.erase(m_moves.begin());
        return acao;
    }
    else
    {
        cout << "\033[1;31m(IA sem movimentos) \033[0m";
        return UP;
    }
}