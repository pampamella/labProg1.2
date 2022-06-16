#include "Damas.h"
#include <thread>
#include <chrono>


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
            cout << "Insira o movimento no formato [letra inicial][numero inicial] [letra final][numero final], por exemplo: c3 d4" << endl;
            cout << "Obs: Em casos de movimento de captura, insira a posicao da peca que deseja capturar como a posicao final do movimento, por exemplo: capturar peca em d4, movimento eh da forma c3 d4" << endl;
            cin >> posInicial>> posFinal;
        }
        while(!Dama.JogarA(posInicial, posFinal));
        Dama.JogarB();
    }

    return 0;
}