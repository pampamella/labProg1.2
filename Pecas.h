#ifndef PECAS_H
#define PECAS_H

#include<vector>
#include<iostream>
#include<Movimentos.h>


using namespace std;

enum tiposDePeca{
    vazia = 0,
    normal,
    rainha
};

class Pecas{
    protected:
    tiposDePeca tipo;
    Pecas(tiposDePeca tipo):tipo(tipo){};

    public:
    virtual Movimentos movimentar(){}
    virtual vector<Movimentos> movimentosPossiveis(){}
};

class Vazia:public Pecas{
    public:
    Vazia():Pecas(vazia){}
    Movimentos movimentar(){
        Movimentos movimento();
        return movimento;
    }
    vector<Movimentos> movimentosPossiveis(){
        vector<Movimentos> movimentos;
        return movimentos;
    }
};

class Normal:public Pecas{
    public:
    Normal():Pecas(normal){}
    Movimentos movimentar(){
        Movimentos movimento();
        return movimento;
    }
    vector<Movimentos> movimentosPossiveis(){
        vector<Movimentos> movimentos;
        return movimentos;
    }
};

class Rainha:public Pecas{
    public:
    Rainha():Pecas(rainha){}
    Movimentos movimentar(){
        Movimentos movimento();
        return movimento;
    }
    vector<Movimentos> movimentosPossiveis(){
        vector<Movimentos> movimentos;
        return movimentos;
    }
};




#endif