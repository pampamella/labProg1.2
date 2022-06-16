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
            cin >> posInicial>> posFinal;
        }
        while(!Dama.Jogar(posInicial, posFinal));
        // Dama.JogarA();
        // this_thread::sleep_for(chrono::milliseconds(1000) );
        Dama.Jogar();
        // this_thread::sleep_for(chrono::milliseconds(1000) );
    }

    return 0;
}