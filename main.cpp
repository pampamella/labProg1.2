#include "Damas.h"


int main(){
    Damas Dama;
    Dama.inicializarTabuleiro();
    Dama.mostrarTabuleiro();
    bool fim = Dama.fimJogo();
    Dama.calcularMovimentosPossiveis();
    Dama.limparSobreposicoes();
    Dama.categoriaDosMovimentosSimples();
    
    string posInicial, posFinal;
    while(!fim){
        cin >> posInicial>> posFinal;
        cout << posInicial << " " << posFinal << endl;
        Dama.Jogar(posInicial, posFinal);
        Dama.Jogar();
        fim = Dama.fimJogo();
        Dama.mostrarTabuleiro();
        Dama.limparSobreposicoes();
        Dama.categoriaDosMovimentosSimples();
        Dama.imprimirMovimentos();
    }

    return 0;
}