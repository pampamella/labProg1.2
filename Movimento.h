#ifndef MOVIMENTO_H
#define MOVIMENTO_H

#include<iostream>

using namespace std;

enum tipoMovimento {
    normal,
    captura,
    convertRainha
};

class Movimento {
    private:
        string posicaoInicial;
        string posicaoFinal;
        tipoMovimento categoria;
    public:
        Movimento(string posInicial, string posFinal, tipoMovimento categoria): posicaoInicial(posInicial), posicaoFinal(posFinal), categoria(categoria) {}

};




#endif