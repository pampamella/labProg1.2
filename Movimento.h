#ifndef MOVIMENTO_H
#define MOVIMENTO_H

#include<iostream>

using namespace std;

enum tipoMovimento {
    normal=0,
    captura,
    convertRainha,
    vazio,
    proibido
};

class Movimento {
    private:
        string posicaoInicial;
        string posicaoFinal;
        tipoMovimento categoria;
    public:
        Movimento(string posInicial, string posFinal, tipoMovimento categoria = normal): posicaoInicial(posInicial), posicaoFinal(posFinal), categoria(categoria) {}
        Movimento(const Movimento &Mov): posicaoInicial(Mov.posicaoInicial), posicaoFinal(Mov.posicaoFinal), categoria(Mov.categoria) {}
        Movimento():posicaoInicial(" "), posicaoFinal(" "), categoria(normal) {}
        tipoMovimento getCategoria(){ return categoria; }
        string getPosicaoInicial(){ return posicaoInicial; }
        string getPosicaoFinal(){ return posicaoFinal; }
        void setCategoria(enum tipoMovimento tipo){
            categoria = tipo;
        }

};




#endif