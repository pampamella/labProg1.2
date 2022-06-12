#ifndef DAMAS_H
#define DAMAS_H

#include <Movimento.h>
#include <Pecas.h>
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
    void movimentar(vector<Movimento> &vetor){
        Movimento movimentoSorteado(vetor[0]);
        string posInicial = movimentoSorteado.getPosicaoInicial();
        int x = posInicial[0] - 97;
        int y = posInicial[1];
        Peca pecaMovimentada = tabuleiro[x][y];
        Peca pecaVazia(posInicial, vazia);
        tabuleiro[x][y] = pecaVazia;
        string posFinal = movimentoSorteado.getPosicaoFinal();
        x = posFinal[0] - 97;
        y = posFinal[1];
        tabuleiro[x][y] = pecaMovimentada;
    }
};

#endif