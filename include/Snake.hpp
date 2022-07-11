#ifndef Snake_hpp
#define Snake_hpp
#include <iostream>
using namespace std;

class Snake{
    private:
        pair<int, int> m_position;
        char m_icon;

    public:
        Snake(pair<int,int> t_position);

        pair<int, int> getPosition();

        void setPosition(std::pair<int,int> t_position);
        
        char getIcon();

        void move(int l, int c);
        
};
#endif