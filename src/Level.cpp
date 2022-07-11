#include "Level.hpp"

#include <string>
#include <vector>
#include <iostream> //! temp
using namespace std;

Level::Level(int lines, int columns, int foods){
    m_lines = lines;
    m_columns = columns;
    m_foods = foods;
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

void Level::printLevel(){ // MÉTODO PARA TESTE
    std::cout << m_lines << " " << m_columns << " " << m_foods << std::endl;

    for(int i = 0; i < m_lines; i++){
        std::cout << m_map[i] << std::endl;
    }
}

vector<string> Level::getLevel(int lvl){
    return m_map;
}

pair<int, int> Level::getStartPosition(){
    for(int c=0;c < m_lines;c++){
        if(m_map[c].find("V") != string::npos){
            m_startLine = c;
            m_startColumn = m_map[c].find("V");
        }
    }
    return make_pair(m_startLine, m_startColumn);
}

pair<int, int> Level::getMazeSize(){
    return make_pair(m_lines, m_columns);
}

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