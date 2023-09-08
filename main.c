#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "func.h"

int main(){
    char jogar;
    dimensoes tam;
    jogo dados_jogo;
    dados_jogo.jogar = true;
    coleta_tamanho(&tam);
    dados_jogo.mat = aloca_matriz(tam);
    dados_jogo.frase = aloca_vetor(&tam);
    le_frase(&dados_jogo, &tam);
    dados_jogo.frase = tira_espaco(&dados_jogo, &tam);
    inicializa_matriz_branco(&dados_jogo, &tam);
    colocaMatriz(&dados_jogo, &tam);
    while(dados_jogo.jogar){
       coleta_palavra(&dados_jogo, &tam);
       procura_matriz(&dados_jogo, &tam);
    }
}