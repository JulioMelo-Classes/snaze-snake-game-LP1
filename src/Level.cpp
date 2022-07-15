#include "Level.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <random>

using namespace std;

Level::Level(int lines, int columns, int foods){
    m_lines = lines;
    m_columns = columns;
    m_foods = foods;
    m_startPosition = make_pair(0, 0);

    for(int l=0; l < lines; l++){
        std::string line = "";

        for(int c=0; c < columns; c++){
            line+=" ";
        }

        m_map.push_back(line);
    }
}

void Level::insertLine(std::string line, int position){
    if((int)line.length() != m_columns || position < 0 || position > m_lines) return;

    m_map[position] = line;
}

pair<int, int> Level::getStartPosition(){return m_startPosition;}

void Level::setStartPosition(pair<int, int> position){
    m_startPosition = position;
}

pair<int, int> Level::getMazeSize(){return make_pair(m_lines, m_columns);}

int Level::getFoods(){return m_foods;}

char Level::getElement(int l, int c){
    return m_map.at(l).at(c);
}

bool Level::allowed(std::pair<int,int> pos){
    if(pos.first < 0 || pos.second < 0)
        return false;
    
    if(pos.first >= m_lines || pos.second >= m_columns)
        return false;

    if(m_map.at(pos.first).at(pos.second) == '#')
        return false;

    return true;
}

pair<int, int> Level::getSpawnFruit(bool spawn){
    if(spawn){
        std::random_device rd;
        std::default_random_engine eng(rd());

        std::uniform_int_distribution<int> distrLines(0, m_lines - 1);
        std::uniform_int_distribution<int> distrColumns(0, m_columns - 1);

        m_fruitPosition = make_pair(distrLines(eng), distrColumns(eng));

        while(!allowed(m_fruitPosition)){
            m_fruitPosition = make_pair(distrLines(eng), distrColumns(eng));
        }

    }
    return m_fruitPosition;
}

