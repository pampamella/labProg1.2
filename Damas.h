#ifndef DAMAS_H
#define DAMAS_H

#include "Movimento.h"
#include "Pecas.h"
#include<iostream>
#include<vector>

using namespace std;

class Damas{
    vector<Movimento> movimentosPossiveis;
    vector<vector<Peca>> tabuleiro;
    public:
    void mostrarTabuleiro(){
        for(int linha = 0;linha<10;linha++){
            cout<<(10-linha)<<" ";
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
                }else if(tabuleiro[linha][coluna].getLado()==false){
                    if(tabuleiro[linha][coluna].getTipo()==rainha){
                        cout<<"B";
                        continue;
                    }
                    cout<<"b";
                }
            }
            cout<<endl;
        }
        cout<<"  abcdefghij"<<endl;
    }
    void inicializarTabuleiro(){
        for(int i = 0;i<10;i++){
            tabuleiro.push_back(vector<Peca>(0,Vazia("a1",0)));
            if(i<4){
                
                for(int j = 0;j<10;j++){
                    string posicao = "";
                    if((i+j)%2){
                        posicao+=char(97+j);
                        posicao+=(10-i);
                        tabuleiro[i].push_back(Vazia(posicao,0));
                    }else{
                        posicao+=char(97+j);
                        posicao+=(10-i);
                        tabuleiro[i].push_back(Simples(posicao,false));
                    }
                }
            }else if(i>=4&&i<6){
                for(int j = 0; j<10;j++){
                    string posicao = "";
                    posicao+=char(97+j);
                    posicao+=(10-i);
                    tabuleiro[i].push_back(Vazia(posicao,0));
                }
            }else if(i>=6){
                for(int j = 0;j<10;j++){
                    string posicao = "";
                    if((i+j)%2){
                        posicao+=char(97+j);
                        posicao+=(10-i);
                        tabuleiro[i].push_back(Vazia(posicao,0));
                    }else{
                        posicao+=char(97+j);
                        posicao+=(10-i);
                        tabuleiro[i].push_back(Simples(posicao,true));
                    }
                }
            }
            

            
        }
    }
};



#endif