#include <iostream>
#include "SnakeGame.hpp"

using namespace std;

int main(int argc, char *argv[]){

    //TODO: processar os argumentos
    if(argc == 4){
        string levelFile = argv[1]; // Caminho do arquivo de nível
        string comandIa = argv[2];
        string iaMode = argv[3];

        if(comandIa == "-ia" and (iaMode == "random" or iaMode=="find")){
            cout << "Inicializando o jogo com a IA no modo " << iaMode << "." << endl;

            SnakeGame game(levelFile, iaMode);
            game.loop();
        }else{
            cout << "Parâmetros de IA inválidos!" << endl;
        }

    }else{
        cout << "Argumentos inválidos para a execução do snaze! O comando de execução do snaze deve respeitar o seguinte padrão:" << endl;
        cout << "./snaze <level_file> -ia [random|find]" << endl;
    }

    return 0;
}