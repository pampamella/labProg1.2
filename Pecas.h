#ifndef PECAS_H
#define PECAS_H

#include<vector>
#include<iostream>
#include "Movimento.h"
#include<algorithm>
#include<string>


using namespace std;

enum tiposDePeca{
    vazia = 0,
    simples,
    rainha
};

class Peca{
    protected:
    bool lado;
    string posicao;
    tiposDePeca tipo;
    public:
    Peca(string posicao,tiposDePeca tipo,bool lado):posicao(posicao),tipo(tipo),lado(lado){};
    public:
    bool getLado(){
        return lado;
    }
    tiposDePeca getTipo(){
        return tipo;
    }
    void setPosicao(string posicaoFinal){
        posicao = posicaoFinal;
    }
    string getPosicao(){
        return posicao;
    }
    vector<Movimento> movimentosPossiveis(){
        if(tipo == simples){
            int movimentador = -1;
            if(lado){
                movimentador = 1;
            }
            vector<Movimento> movimentos;
            int letraPosicao = posicao[0];
            int numeroFinal = posicao[1]+movimentador;
            string posicaoFinal = "";
            posicaoFinal+=char(letraPosicao + 1);
            posicaoFinal+=numeroFinal;
            movimentos.push_back(Movimento(posicao,posicaoFinal));
            posicaoFinal = "";
            posicaoFinal+=char(letraPosicao - 1);
            posicaoFinal+=numeroFinal;
            movimentos.push_back(Movimento(posicao,posicaoFinal));
            return movimentos;
        }
        if(tipo == vazia){
            vector<Movimento> movimentos;
            Movimento m1("-","-",vazio);
            movimentos.push_back(Movimento ("-","-",vazio));
            return movimentos;
        }
        if(tipo == rainha){
            string posicaoFinal;
            int letraPosicao = posicao[0];
            int numeroFinal = 0;
            vector<Movimento> movimentos;
            for(int i = -10; i<10;i++){
            if(i==0){
                continue;
            }
            numeroFinal = (int)(posicao[1]+i);
            posicaoFinal = "";
            posicaoFinal+=char(letraPosicao + i);
            posicaoFinal+=numeroFinal;
            movimentos.push_back(Movimento(posicao,posicaoFinal));
            posicaoFinal = "";
            posicaoFinal+=char(letraPosicao - i);
            posicaoFinal+=numeroFinal;
            movimentos.push_back(Movimento(posicao,posicaoFinal));            
        }
        
        return movimentos;
        }
    }
};

class Vazia:public Peca{
    public:
    Vazia(string posicao, bool lado):Peca(posicao,vazia,lado){}
    // vector<Movimento> movimentosPossiveis(){
        
    // }
};

class Simples:public Peca{
    public:
    Simples(string posicao,bool lado):Peca(posicao,simples,lado){}
    vector<Movimento> movimentosPossiveis(){
        vector<Movimento> movimentos;
        cout<<"entrei";
        int letraPosicao = posicao[0];
        int numeroFinal = posicao[1]+1;
        string posicaoFinal = "";
        posicaoFinal+=char(letraPosicao + 1);
        posicaoFinal+=numeroFinal;
        movimentos.push_back(Movimento(posicao,posicaoFinal));
        posicaoFinal = "";
        posicaoFinal+=char(letraPosicao - 1);
        posicaoFinal+=numeroFinal;
        movimentos.push_back(Movimento(posicao,posicaoFinal));
        
        return movimentos;
    }
};

class Rainha:public Peca{
    public:
    Rainha(string posicao,bool lado):Peca(posicao,rainha,lado){}
    // vector<Movimento> movimentosPossiveis(){
        
    // }
};




#endif