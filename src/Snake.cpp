#include "Snake.hpp"
using namespace std;

Snake::Snake(pair<int,int> t_position){
    m_position = t_position;
    m_icon = 'V';
}

pair<int,int> Snake::getPosition(){
    return m_position;
}

void Snake::setPosition(pair<int,int> t_position){
    m_position = t_position;
}

char Snake::getIcon(){
    return m_icon;
}

void Snake::move(int l, int c){
    m_position.first += l;
    m_position.second += c;
}
