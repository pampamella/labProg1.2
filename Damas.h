#ifndef DAMAS_H
#define DAMAS_H

#include "Movimento.h"
#include "Pecas.h"
#include<iostream>
#include<vector>

using namespace std;

class Damas{
    vector<Movimento> movimentosPossiveis;
    public:
    vector<vector<Peca>> tabuleiro;
    void mostrarTabuleiro(){
        for(int linha = 0;linha<10;linha++){
            for(int coluna = 0; coluna<10;coluna++){
                if(tabuleiro[linha][coluna].getTipo()==vazia){
                    cout<<"_";
                    continue;
                }
                if(tabuleiro[linha][coluna].getLado()==true){
                    if(tabuleiro[linha][coluna].getTipo()==rainha){
                        cout<<"A";
                        continue;
                    }
                    cout<<"a";
                }else{
                    if(tabuleiro[linha][coluna].getTipo()==rainha){
                        cout<<"B";
                        continue;
                    }
                    cout<<"b";
                }
            }
            cout<<endl;
        }
    }
};



#endif