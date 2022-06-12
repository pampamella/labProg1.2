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

class Pecas{
    protected:
    tiposDePeca tipo;
    Pecas(tiposDePeca tipo):tipo(tipo){};

    public:
    virtual Movimento movimentar(){}
    virtual vector<Movimento> movimentosPossiveis(){}
};

class Vazia:public Pecas{
    public:
    Vazia():Pecas(vazia){}
    Movimento movimentar(){
        Movimento movimento();
        return movimento;
    }
    vector<Movimento> movimentosPossiveis(){
        vector<Movimento> movimentos;
        return movimentos;
    }
};

class Normal:public Pecas{
    public:
    Normal():Pecas(normal){}
    Movimento movimentar(){
        Movimento movimento();
        return movimento;
    }
    vector<Movimento> movimentosPossiveis(){
        vector<Movimento> movimentos;
        return movimentos;
    }
};

class Rainha:public Pecas{
    public:
    Rainha():Pecas(rainha){}
    Movimento movimentar(){
        Movimento movimento();
        return movimento;
    }
    vector<Movimento> movimentosPossiveis(){
        vector<Movimento> movimentos;
        return movimentos;
    }
};




#endif