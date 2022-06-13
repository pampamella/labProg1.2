#include "Damas.h"


int main(){
    Damas Dama;
    Dama.inicializarTabuleiro();
    Dama.mostrarTabuleiro();
    bool fim = Dama.fimJogo();
    Dama.calcularMovimentosPossiveis();
    Dama.limparSobreposicoes();
    
    string posInicial, posFinal;
    while(!fim){
        // cin >> posInicial>> posFinal;
        // cout << posInicial << " " << posFinal << endl;
        posFinal = "b4";
        posInicial ="a3";
        Dama.Jogar(posInicial, posFinal);
        Dama.Jogar();
        fim = Dama.fimJogo();
        Dama.mostrarTabuleiro();
    }

    return 0;
}