#include "Level.hpp"

#include <string>
#include <iostream> // REMOVER DEPOIS

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