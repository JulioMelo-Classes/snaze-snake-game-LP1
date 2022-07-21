#include <iostream>
#include "SnakeGame.hpp"

using namespace std;

int main(int argc, char *argv[]){

    //TODO: processar os argumentos
    if(argc == 2){
        string levelFile = argv[1];

        SnakeGame game(levelFile);
        
        game.loop();
    }else{
        cout << "Argumentos inválidos para a execução do snaze! Lembre de informar o caminho do arquivo de níveis corretamente." << endl;
    }

    return 0;
}