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
    tiposDePeca tipo;
    Peca(tiposDePeca tipo):tipo(tipo){};

    public:
    virtual Movimento movimentar(){}
    virtual vector<Movimento> movimentosPossiveis(){}
};

class Vazia:public Peca{
    public:
    Vazia():Peca(vazia){}
    Movimento movimentar(){
        Movimento movimento();
        return movimento;
    }
    vector<Movimento> movimentosPossiveis(){
        vector<Movimento> movimentos;
        return movimentos;
    }
};

class Normal:public Peca{
    public:
    Normal():Peca(normal){}
    Movimento movimentar(){
        Movimento movimento();
        return movimento;
    }
    vector<Movimento> movimentosPossiveis(){
        vector<Movimento> movimentos;
        return movimentos;
    }
};

class Rainha:public Peca{
    public:
    Rainha():Peca(rainha){}
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