
#define FUNC
#include <stdbool.h>

typedef struct{
 int l;
 int c;
}dimensoes;

typedef struct{
    bool jogar;
    bool achou;
    char** mat;
    char* frase;
    char* palavra;
}jogo;

void coleta_tamanho(dimensoes *tam);
char** aloca_matriz(dimensoes tam);
char* aloca_vetor(dimensoes *tam);
void le_frase(jogo *dados_jogo, dimensoes *tam);
char* tira_espaco(jogo *dados_jogo, dimensoes *tam);
void colocaMatriz(jogo *dados_jogo, dimensoes *tam);
void procura_frase(jogo *dados_jogo, dimensoes *tam);
void inicializa_matriz_branco(jogo *dados_jogo, dimensoes *tam);
void coleta_palavra(jogo *dados_jogo, dimensoes *tam);
void procura_matriz(jogo *dados_jogo, dimensoes *tam);