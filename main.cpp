#include "Damas.h"


int main(){
    Damas Dama;
    Dama.inicializarTabuleiro();
    Dama.mostrarTabuleiro();
    Dama.calcularMovimentosPossiveis();
    Dama.limparSobreposicoes();
    Dama.categoriaDosMovimentosSimples();
    
    int contador = 0;
    while(!Dama.fimJogo()){
        string posInicial, posFinal;
        do{
            cin >> posInicial>> posFinal;
        }
        while(!Dama.Jogar(posInicial, posFinal));
        Dama.Jogar();
    }

    return 0;
}