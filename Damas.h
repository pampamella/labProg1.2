#ifndef DAMAS_H
#define DAMAS_H

#include "Movimento.h"
#include "Pecas.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <set>
#define ESC "\033["
#define RED_TXT "31"
#define GREEN_TXT "32"
#define RESET "\033[m"

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
        if(fimJogo()){
            return;
        }
        cout<<"Jogada do computador:"<<endl;
        srand(unsigned(time(0)));
        vector<Movimento> movimentosPrioritarios(movimentosPossiveisB.size());
        random_shuffle(movimentosPossiveisB.begin(), movimentosPossiveisB.end());
        copy_if(movimentosPossiveisB.begin(), movimentosPossiveisB.end(), movimentosPrioritarios.begin(), [](Movimento i)
                { return i.getCategoria() == captura || i.getCategoria() == convertRainha; });

        if (movimentosPrioritarios[0].getPosicaoInicial() != " "){
            movimentar(movimentosPrioritarios);
        }else{
            movimentar(movimentosPossiveisB);
        }
        calcularMovimentosPossiveis();
        limparSobreposicoes();
        categoriaDosMovimentosSimples();
        mostrarTabuleiro();
    }
    void JogarA()
    {
        if(fimJogo()){
            return;
        }

        cout<<"Jogada do computador A:"<<endl;
        srand(unsigned(time(0)));
        vector<Movimento> movimentosPrioritarios(movimentosPossiveisA.size());
        random_shuffle(movimentosPossiveisA.begin(), movimentosPossiveisA.end());
        copy_if(movimentosPossiveisA.begin(), movimentosPossiveisA.end(), movimentosPrioritarios.begin(), [](Movimento i)
                { return i.getCategoria() == captura || i.getCategoria() == convertRainha; });

        if (movimentosPrioritarios[0].getPosicaoInicial() != " "){
            movimentar(movimentosPrioritarios);
        }else{
            movimentar(movimentosPossiveisA);
        }
        calcularMovimentosPossiveis();
        limparSobreposicoes();
        categoriaDosMovimentosSimples();
        mostrarTabuleiro();
    }

    bool verificaMovimento(string posicaoInicial, string posicaoFinal){
        Movimento tentativaMovimento(posicaoInicial, posicaoFinal);
        vector<Movimento>::iterator it;
        it = find_if(movimentosPossiveisA.begin(), movimentosPossiveisA.end(), [&tentativaMovimento](Movimento i) {
            return i.getPosicaoInicial() == tentativaMovimento.getPosicaoInicial() && i.getPosicaoFinal() == tentativaMovimento.getPosicaoFinal();
        });
        if(it != movimentosPossiveisA.end()){
            return true;
        }
        cout << "Movimento invalido!" << endl;
        return false;
    }

    bool Jogar(string posicaoInicial, string posicaoFinal){
        if(fimJogo()){
            return false;
        }
        bool movimentoPossivel = verificaMovimento(posicaoInicial, posicaoFinal);
        Movimento movimentoEscolhido(posicaoInicial, posicaoFinal);

        vector<Movimento>::iterator it;
        it = find_if(movimentosPossiveisA.begin(), movimentosPossiveisA.end(), [&movimentoEscolhido](Movimento i) {
            return i.getPosicaoInicial() == movimentoEscolhido.getPosicaoInicial() && i.getPosicaoFinal() == movimentoEscolhido.getPosicaoFinal();
        });
       
        if(movimentoPossivel){
            cout<<"Jogada do jogador:"<<endl;
            int x = posicaoInicial[0] - 97;
            int y = posicaoInicial[1] - 48;
            Peca pecaMovimentada = tabuleiro[9-y][x];
            Peca pecaVazia(posicaoInicial, vazia, true);
            tabuleiro[9-y][x] = pecaVazia;
            x = posicaoFinal[0] - 97;
            y = posicaoFinal[1] - 48;
            pecaMovimentada.setPosicao(posicaoFinal);
            tabuleiro[9-y][x] = pecaMovimentada;
             if((*it).getCategoria()==convertRainha){
                converterRainha(posicaoFinal);
            }
            if((*it).getCategoria()==captura){
                capturarPeca(posicaoInicial, posicaoFinal);
            }
        }
        calcularMovimentosPossiveis();
        limparSobreposicoes();
        categoriaDosMovimentosSimples();
        mostrarTabuleiro();
        return movimentoPossivel;
    }
    void movimentar(vector<Movimento> vetor){
        Movimento movimentoSorteado(vetor[0]);
        string posInicial = movimentoSorteado.getPosicaoInicial();
        string posFinal = movimentoSorteado.getPosicaoFinal();
        int x = posInicial[0] - 97;
        int y = posInicial[1] - 48;
        Peca pecaMovimentada = tabuleiro[9-y][x];
        Peca pecaVazia(posInicial, vazia, false);
        tabuleiro[9-y][x] = pecaVazia;
        x = posFinal[0] - 97;
        y = posFinal[1] - 48;
        pecaMovimentada.setPosicao(posFinal);
        tabuleiro[9-y][x] = pecaMovimentada;
        if(movimentoSorteado.getCategoria()==convertRainha){
            converterRainha(posFinal);
        }
        if(movimentoSorteado.getCategoria()==captura){
            capturarPeca(posInicial,posFinal);
        }
    }
    void capturarPeca(string posInicial,string posFinal){
        int xInicial = posInicial[0] ;
        int yInicial = posInicial[1];
        int xFinal = posFinal[0] ;
        int yFinal = posFinal[1] ;
        int varX = (xFinal-xInicial)/abs(xFinal-xInicial);
        int varY = (yFinal-yInicial)/abs(yFinal-yInicial);
        string posCaptura = "";
        posCaptura+=char(xFinal+varX);
        posCaptura+=yFinal+varY;
        vector<Movimento> movCaptura;
        Movimento mov(posFinal,posCaptura);
        if(yFinal+varY-48==9||yFinal+varY-48==0){
            if(tabuleiro[9-yFinal][xFinal].getTipo()!=rainha);
            mov.setCategoria(convertRainha);
        }
        movCaptura.push_back(mov);
        movimentar(movCaptura);

    }
    void converterRainha(string posicao){
        int x = posicao[0] - 97;
        int y = posicao[1] - 48;
        if(tabuleiro[9-y][x].getTipo() == rainha){
            return;
        }
        tabuleiro[9-y][x].setTipo(rainha); 
    }
    void mostrarTabuleiro(){
        for(int linha = 0;linha<10;linha++){
            cout<<(9-linha)<<" ";
            for(int coluna = 0; coluna<10;coluna++){
                if(tabuleiro[linha][coluna].getTipo()==vazia){
                    cout<<" _ ";
                    continue;
                }
                if(tabuleiro[linha][coluna].getLado()==true){
                    if(tabuleiro[linha][coluna].getTipo()==rainha){
                        cout << ESC << ";" << RED_TXT <<"m"<< " O " << RESET;
                        continue;
                    }
                    cout << ESC << ";" << RED_TXT <<"m"<< " o " << RESET;
                }else if(tabuleiro[linha][coluna].getLado()==false){
                    if(tabuleiro[linha][coluna].getTipo()==rainha){
                        cout << ESC << ";" << GREEN_TXT <<"m"<< " O " << RESET;
                        continue;
                    }
                    cout << ESC << ";" << GREEN_TXT <<"m"<< " o " << RESET;
                }
            }
            cout<<endl;
            cout<<endl;

        }
        cout<<"   a  b  c  d  e  f  g  h  i  j"<<endl;
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
        movimentosPossiveisA.clear();
        movimentosPossiveisB.clear();
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
            cout<<movimentosPossiveisB[i].getPosicaoInicial()<<"->"<<movimentosPossiveisB[i].getPosicaoFinal()<<movimentosPossiveisB[i].getCategoria()<<endl;
        }
    }

    vector<int> posicaoStringInt(string posicao){
        vector<int> vetor;
        int letra = posicao[0];
        int numero = posicao[1];
        vetor.push_back(57-numero);
        vetor.push_back(letra-97);
        return vetor;
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
                    vector<int> posInicial = posicaoStringInt(movimentosPossiveisA[j].getPosicaoInicial());
                    vector<int> posFinal = posicaoStringInt(movimentosPossiveisA[j].getPosicaoFinal());
                    int difLetra = (posFinal[1]-posInicial[1])/abs(posFinal[1]-posInicial[1]);
                    int difNumero = (posFinal[0]-posInicial[0])/abs(posFinal[0]-posInicial[0]);
                    int contador = 0;
                    if(tabuleiro[posInicial[0]][posInicial[1]].getTipo()==rainha){
                        while(movimentosPossiveisA[j+1].getPosicaoFinal()==posicoesIniciaisA[i]){
                            vector<int> checkPos = posicaoStringInt(movimentosPossiveisA[j+contador].getPosicaoFinal());
                            int checkDifNumero = (checkPos[0]-posInicial[0])/abs(checkPos[0]-posInicial[0]);
                            int checkDifLetra = (checkPos[1]-posInicial[1])/abs(checkPos[1]-posInicial[1]);
                            if(difNumero!=checkDifNumero || difLetra!=checkDifLetra){
                                contador++;
                                continue;
                            }
                            movimentosPossiveisA.erase(movimentosPossiveisA.begin()+j+contador);
                        }
                    }
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
            bool quebra = true;
            int coluna = (int)movimentosPossiveisA[i].getPosicaoFinal()[0]-97;
            int linha = 57-movimentosPossiveisA[i].getPosicaoFinal()[1];
            if(tabuleiro[linha][coluna].getTipo()==vazia){
                movimentosPossiveisA[i].setCategoria(normal);
            }
            else if(tabuleiro[linha][coluna].getTipo()==simples||tabuleiro[linha][coluna].getTipo()==rainha){
                if(linha - 1>=0 && coluna + 1<10 && tabuleiro[linha-1][coluna+1].getTipo() == vazia){
                    movimentosPossiveisA[i].setCategoria(captura);
                    quebra=false;
                    }
                else if(linha - 1>=0 && coluna-1>=0 && tabuleiro[linha-1][coluna-1].getTipo() == vazia && !quebra){
                    movimentosPossiveisA[i].setCategoria(captura);
                    }
                else{
                    movimentosPossiveisA.erase(movimentosPossiveisA.begin()+i);
                }
            }
            else if(linha==0){
                 movimentosPossiveisA[i].setCategoria(convertRainha);
            }
        }
        for(int i = 0;i<movimentosPossiveisB.size();i++){
            bool quebra=true;
            int coluna = (int)movimentosPossiveisB[i].getPosicaoFinal()[0]-97;
            int linha = 57-movimentosPossiveisB[i].getPosicaoFinal()[1];
            int colunaInicial = (int)movimentosPossiveisB[i].getPosicaoInicial()[0]-97;
            int linhaInicial = 57-movimentosPossiveisB[i].getPosicaoInicial()[1];
            int varColuna = (coluna-colunaInicial)/abs(coluna-colunaInicial);
            if(tabuleiro[linha][coluna].getTipo()==vazia){
                movimentosPossiveisB[i].setCategoria(normal);
            }
            else if(tabuleiro[linha][coluna].getTipo()==simples){
                if(linha+1<10&&coluna+varColuna<10&&tabuleiro[linha+1][coluna+varColuna].getTipo()==vazia){
                    movimentosPossiveisB[i].setCategoria(captura);
                    }
                else{
                    movimentosPossiveisB.erase(movimentosPossiveisB.begin()+i);
                }    
            }
            else if(linha==9){
                 movimentosPossiveisB[i].setCategoria(convertRainha);
            }
        }
    }
    void categoriaDosMovimentosRainha(){
        for(int i = 0;i<movimentosPossiveisA.size();i++){
            int linha = (int)movimentosPossiveisA[i].getPosicaoFinal()[0]-97;
            int coluna = 57-movimentosPossiveisA[i].getPosicaoFinal()[1];
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