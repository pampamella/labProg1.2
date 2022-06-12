#ifndef PECAS_H
#define PECAS_H

#include<vector>
#include<iostream>
#include<Movimento.h>


using namespace std;

enum tiposDePeca{
    vazia = 0,
    simples,
    rainha
};

class Peca{
    protected:
    string posicao;
    tiposDePeca tipo;
    public:
    Peca(string posicao,tiposDePeca tipo):posicao(posicao),tipo(tipo){};
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

class Simples:public Peca{
    public:
    Simples(string posicao):Peca(posicao,simples){}
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