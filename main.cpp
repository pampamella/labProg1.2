#include "Damas.h"


int main(){
    Damas Dama;
    bool fim = Dama.fimJogo();
    string posInicial, posFinal;
    while(!fim){
        cin>> posInicial>> posFinal;
        Dama.Jogar(posInicial, posFinal);
        Dama.Jogar();
        fim = Dama.fimJogo();
    }

    return 0;
}