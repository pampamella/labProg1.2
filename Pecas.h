#ifndef PECAS_H
#define PECAS_H

#include<vector>
#include<iostream>
#include<Movimento.h>


using namespace std;

enum tiposDePeca{
    vazia = 0,
    normal,
    rainha
};

class Peca{
    protected:
    string posicao;
    tiposDePeca tipo;
    Peca(string posicao,tiposDePeca tipo):posicao(posicao),tipo(tipo){};

    public:
    void movimentar(string posicaoFinal){
        posicao = posicaoFinal;
    }
    virtual vector<Movimento> movimentosPossiveis(){}
};

class Vazia:public Peca{
    public:
    Vazia(string posicao):Peca(posicao,vazia){}
    vector<Movimento> movimentosPossiveis(){
        vector<Movimento> movimentos;
        return movimentos;
    }
};

class Normal:public Peca{
    public:
    Normal(string posicao):Peca(posicao,normal){}
    vector<Movimento> movimentosPossiveis(){
        vector<Movimento> movimentos;
        return movimentos;
    }
};

class Rainha:public Peca{
    public:
    Rainha(string posicao):Peca(posicao,rainha){}
    vector<Movimento> movimentosPossiveis(){
        vector<Movimento> movimentos;
        return movimentos;
    }
};




#endif