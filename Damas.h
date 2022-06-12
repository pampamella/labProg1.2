#ifndef DAMAS_H
#define DAMAS_H

#include <Movimento.h>
#include <Pecas.h>
#include<iostream>

using namespace std;

class Damas {
    private:
        bool jogadorAtual;
        vector<vector<Peca>> tabuleiro;
        vector<Movimento> movimentosPossiveis;
    public:
        Damas(): jogadorAtual(false){}
        
};



#endif