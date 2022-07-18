#include <iostream>
#include "SnakeGame.hpp"

using namespace std;

int main(int argc, char *argv[]){

    //TODO: processar os argumentos
    SnakeGame game("../data/teste.txt");//* START
    
    game.loop();//* UPDATE

    return 0;
}