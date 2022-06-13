#ifndef DAMAS_H
#define DAMAS_H

#include "Movimento.h"
#include "Pecas.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <set>

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
        calcularMovimentosPossiveis();
        limparSobreposicoes();
    }
    bool verificaMovimento(string posicaoInicial, string posicaoFinal){
        return true;
    }
    void Jogar(string posicaoInicial, string posicaoFinal){
        bool movimentoPossivel = verificaMovimento(posicaoInicial, posicaoFinal);
        if(movimentoPossivel){
            int x = posicaoInicial[0] - 97;
            int y = posicaoInicial[1] - 48;
            Peca pecaMovimentada = tabuleiro[9-y][x];
            Peca pecaVazia(posicaoInicial, vazia, true);
            tabuleiro[9-y][x] = pecaVazia;
            x = posicaoFinal[0] - 97;
            y = posicaoFinal[1] - 48;
            pecaMovimentada.setPosicao(posicaoFinal);
            tabuleiro[9-y][x] = pecaMovimentada;
        }
        else{
            cout << "Jogada invalida!" << endl;
        }
        calcularMovimentosPossiveis();
        limparSobreposicoes();
    }
    void movimentar(vector<Movimento> &vetor){
        Movimento movimentoSorteado(vetor[0]);
        string posInicial = movimentoSorteado.getPosicaoInicial();
        int x = posInicial[0] - 97;
        int y = posInicial[1] - 48;
        Peca pecaMovimentada = tabuleiro[9-y][x];
        Peca pecaVazia(posInicial, vazia, false);
        tabuleiro[9-y][x] = pecaVazia;
        string posFinal = movimentoSorteado.getPosicaoFinal();
        x = posFinal[0] - 97;
        y = posFinal[1] - 48;
        pecaMovimentada.setPosicao(posFinal);
        tabuleiro[9-y][x] = pecaMovimentada;
    }
    void mostrarTabuleiro(){
        for(int linha = 0;linha<10;linha++){
            cout<<(9-linha)<<" ";
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
                        posicao=char(97+j);
                        posicao+=to_string(9-i);
                        tabuleiro[i].push_back(Vazia(posicao,0));
                    }else{
                        posicao=char(97+j);
                        posicao+=to_string(9-i);
                        tabuleiro[i].push_back(Simples(posicao,false));
                    }
                }
            }else if(i>=4&&i<6){
                for(int j = 0; j<10;j++){
                    string posicao = "";
                    posicao=char(97+j);
                    posicao+=to_string(9-i);
                    tabuleiro[i].push_back(Vazia(posicao,false));
                }
            }else if(i>=6){
                for(int j = 0;j<10;j++){
                    string posicao = "";
                    if((i+j)%2){
                        posicao=char(97+j);
                        posicao+=to_string(9-i);
                        tabuleiro[i].push_back(Vazia(posicao,false));
                    }else{
                        posicao=char(97+j);
                        posicao+=to_string(9-i);
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

    void calcularMovimentosPossiveis(){
        vector<Movimento> movimentosReais;
        for(int linha = 0;linha<10;linha++){
            for(int coluna = 0; coluna<10;coluna++){
                for(int i = 0; i<tabuleiro[linha][coluna].movimentosPossiveis().size();i++){
                    string posicao = tabuleiro[linha][coluna].movimentosPossiveis()[i].getPosicaoFinal();
                    if(posicao[0]<'a'||posicao[0]>'j'){
                        continue;
                    }
                    if(posicao[1]<'0'||posicao[1]>'9'){
                        continue;
                    }
                    if(tabuleiro[linha][coluna].getLado()){
                        movimentosPossiveisA.push_back(tabuleiro[linha][coluna].movimentosPossiveis()[i]);
                    }else{
                        movimentosPossiveisB.push_back(tabuleiro[linha][coluna].movimentosPossiveis()[i]);
                    }
                }
            }
        }
    }

    void imprimirMovimentos(){
        cout<<"Movimentos jogador A"<<endl;
        for(int i = 0; i<movimentosPossiveisA.size();i++){
            cout<<movimentosPossiveisA[i].getPosicaoInicial()<<"->"<<movimentosPossiveisA[i].getPosicaoFinal()<<movimentosPossiveisA[i].getCategoria()<<endl;
        }
        cout<<"Movimentos jogador B"<<endl;
        for(int i = 0; i<movimentosPossiveisB.size();i++){
            cout<<movimentosPossiveisB[i].getPosicaoInicial()<<"->"<<movimentosPossiveisB[i].getPosicaoFinal()<<movimentosPossiveisA[i].getCategoria()<<endl;
        }
    }

    void limparSobreposicoes(){
        vector<string> posicoesIniciaisA;
        vector<string> posicoesIniciaisB;    
        for(int i = 0;i<movimentosPossiveisA.size();i++){
            posicoesIniciaisA.push_back(movimentosPossiveisA[i].getPosicaoInicial());
        }
        for(int i = 0;i<posicoesIniciaisA.size();i++){
            for(int j = 0;j<movimentosPossiveisA.size();j++){
                if(posicoesIniciaisA[i]==movimentosPossiveisA[j].getPosicaoFinal()){
                    movimentosPossiveisA.erase(movimentosPossiveisA.begin()+j);
                }
            }
        }
        for(int i = 0;i<movimentosPossiveisB.size();i++){
            posicoesIniciaisB.push_back(movimentosPossiveisB[i].getPosicaoInicial());
        }
        for(int i = 0;i<posicoesIniciaisB.size();i++){
            for(int j = 0;j<movimentosPossiveisB.size();j++){
                if(posicoesIniciaisB[i]==movimentosPossiveisB[j].getPosicaoFinal()){
                    movimentosPossiveisB.erase(movimentosPossiveisB.begin()+j);
                }
            }
        }
    }
    void categoriaDosMovimentosSimples(){
        for(int i = 0;i<movimentosPossiveisA.size();i++){
            int linha = (int)movimentosPossiveisA[i].getPosicaoFinal()[0]-97;
            int coluna = 57-movimentosPossiveisA[i].getPosicaoFinal()[1];
            cout<<linha<<" "<<coluna<<endl;
            if(tabuleiro[linha][coluna].getTipo()==vazia){
                movimentosPossiveisA[i].setCategoria(normal);
            }
            if(tabuleiro[linha][coluna].getTipo()==simples){
                if(tabuleiro[linha-1][coluna+1].getTipo()==simples){continue;}
                if(tabuleiro[linha-1][coluna-1].getTipo()==simples){continue;}
                movimentosPossiveisA[i].setCategoria(captura);
            }
        }
        for(int i = 0;i<movimentosPossiveisB.size();i++){
            int linha = (int)movimentosPossiveisB[i].getPosicaoFinal()[0]-97;
            int coluna = 57-movimentosPossiveisB[i].getPosicaoFinal()[1];
            cout<<linha<<" "<<coluna<<endl;
            if(tabuleiro[linha][coluna].getTipo()==vazia){
                movimentosPossiveisB[i].setCategoria(normal);
            }
            if(tabuleiro[linha][coluna].getTipo()==simples){
                if(tabuleiro[linha+1][coluna+1].getTipo()==simples){continue;}
                if(tabuleiro[linha+1][coluna-1].getTipo()==simples){continue;}
                movimentosPossiveisB[i].setCategoria(captura);
            }
        }
    }
    void categoriaDosMovimentosRainha(){
        for(int i = 0;i<movimentosPossiveisA.size();i++){
            int linha = (int)movimentosPossiveisA[i].getPosicaoFinal()[0]-97;
            int coluna = 57-movimentosPossiveisA[i].getPosicaoFinal()[1];
            cout<<linha<<" "<<coluna<<endl;
            if(tabuleiro[linha][coluna].getTipo()==vazia){
                movimentosPossiveisA[i].setCategoria(normal);
            }
            if(tabuleiro[linha][coluna].getTipo()==simples){
                if(tabuleiro[linha-1][coluna+1].getTipo()==simples){continue;}
                if(tabuleiro[linha-1][coluna-1].getTipo()==simples){continue;}
                movimentosPossiveisA[i].setCategoria(captura);
            }
        }
        for(int i = 0;i<movimentosPossiveisB.size();i++){
            int linha = (int)movimentosPossiveisB[i].getPosicaoFinal()[0]-97;
            int coluna = 57-movimentosPossiveisB[i].getPosicaoFinal()[1];
            cout<<linha<<" "<<coluna<<endl;
            if(tabuleiro[linha][coluna].getTipo()==vazia){
                movimentosPossiveisB[i].setCategoria(normal);
            }
            if(tabuleiro[linha][coluna].getTipo()==simples){
                if(tabuleiro[linha+1][coluna+1].getTipo()==simples){continue;}
                if(tabuleiro[linha+1][coluna-1].getTipo()==simples){continue;}
                movimentosPossiveisB[i].setCategoria(captura);
            }
        }
    }
};

#endif