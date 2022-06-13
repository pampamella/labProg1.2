#ifndef DAMAS_H
#define DAMAS_H

#include "Movimento.h"
#include "Pecas.h"
#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

class Damas
{
private:
    bool jogadorAtual;
    vector<vector<Peca>> tabuleiro;
    vector<Movimento> movimentosPossiveisA;
    vector<Movimento> movimentosPossiveisB;
public:
    Damas() : jogadorAtual(true) {}
    void Jogar()
    {
        srand(unsigned(time(0)));
        vector<Movimento> movimentosPrioritarios(movimentosPossiveisB.size());
        copy_if(movimentosPossiveisB.begin(), movimentosPossiveisB.end(), movimentosPrioritarios.begin(), [](Movimento i)
                { return i.getCategoria() == captura || i.getCategoria() == convertRainha; });
        if (movimentosPrioritarios[0].getPosicaoInicial() != " ")
        {
            random_shuffle(movimentosPrioritarios.begin(), movimentosPrioritarios.end());
            movimentar(movimentosPrioritarios);
        }
        else{
            random_shuffle(movimentosPossiveisB.begin(), movimentosPossiveisB.end());
            movimentar(movimentosPossiveisB);
        }
    }
    bool verificaMovimento(string posicaoInicial, string posicaoFinal){
        return true;
    }
    void Jogar(string posicaoInicial, string posicaoFinal){
        bool movimentoPossivel = verificaMovimento(posicaoInicial, posicaoFinal);
        if(movimentoPossivel){
            int x = posicaoInicial[0] - 97;
            int y = posicaoInicial[1];
            Peca pecaMovimentada = tabuleiro[x][y];
            Peca pecaVazia(posicaoInicial, vazia, true);
            tabuleiro[x][y] = pecaVazia;
            x = posicaoFinal[0] - 97;
            y = posicaoFinal[1];
            pecaMovimentada.setPosicao(posicaoFinal);
            tabuleiro[x][y] = pecaMovimentada;
        }
        else{
            cout << "Jogada invalida!" << endl;
        }
    }
    void movimentar(vector<Movimento> &vetor){
        Movimento movimentoSorteado(vetor[0]);
        string posInicial = movimentoSorteado.getPosicaoInicial();
        int x = posInicial[0] - 97;
        int y = posInicial[1];
        Peca pecaMovimentada = tabuleiro[x][y];
        Peca pecaVazia(posInicial, vazia, false);
        tabuleiro[x][y] = pecaVazia;
        string posFinal = movimentoSorteado.getPosicaoFinal();
        x = posFinal[0] - 97;
        y = posFinal[1];
        pecaMovimentada.setPosicao(posFinal);
        tabuleiro[x][y] = pecaMovimentada;
    }
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
    bool fimJogo(){
        int contadorA = 0;
        int contadorB = 0;
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                tiposDePeca tipo = tabuleiro[i][j].getTipo();
                bool pecaJogador = tabuleiro[i][j].getLado();
                if(tipo == vazia){
                    continue;
                }
                else if(pecaJogador){
                    contadorA++;
                }
                else if(!pecaJogador){
                    contadorB++;
                }
            }
        }
        if(!contadorA){
            cout << "FIM DE JOGO ---- Vitoria Computador!" << endl;
            return true;
        }
        if(!contadorB){
            cout << "FIM DE JOGO ---- Vitoria Jogador!" << endl;
            return true;
        }
        return false;
    }
    
};

#endif