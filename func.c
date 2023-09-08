#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "func.h"

void corl(int r, int g, int b){printf("\e[38;2;%d;%d;%dm", r, g, b);}
void corn(void){printf("\e[m");}
void pos(int lin, int col){printf("\e[%d;%dH", lin, col);}
void limpa(void){printf("\e[2J");}


void coleta_tamanho(dimensoes *tam){
    printf("Digite a quantidade de linhas: ");
    scanf("%d", &tam->l);
    printf("Digite a quantidade de colunas: ");
    scanf("%d", &tam->c);
}
char** aloca_matriz(dimensoes tam){
    char** mat;
    mat = (char**)malloc(tam.l*sizeof(char*));
    for (int i = 0; i < tam.l; i++){
        mat[i] = (char*)malloc(tam.c*sizeof(char));
    }
    return mat;
}
char* aloca_vetor(dimensoes *tam){
    char* vet;
    vet = (char*)malloc(tam->l*tam->c*sizeof(char));
    return vet;
}

void le_frase(jogo *dados_jogo, dimensoes *tam){
    int n_carac;
    n_carac = tam->l*tam->c;
    printf("Digite uma frase de %d caracteres\n", n_carac);
    scanf(" %[^\n]s", dados_jogo->frase);
    printf("\n");
}

char* tira_espaco(jogo *dados_jogo, dimensoes *tam){
    dimensoes aux;
    int n_carac = tam->l*tam->c;
    aux.l = tam->l;
    aux.c = tam->c;
    int j = 0;
    char* vet_aux = aloca_vetor(&aux);
    for(int i = 0; i < n_carac; i++){
        if(dados_jogo->frase[i+j] == ' '){
            j++;
        }
        vet_aux[i] = dados_jogo->frase[i+j];
        if(dados_jogo->frase[i] == '\0'){
            break;
        }
    }
    return vet_aux;
}

void inicializa_matriz_branco(jogo *dados_jogo, dimensoes *tam){
    for(int j = 0; j < tam->l; j++){
        for(int i = 0; i < tam->c; i++){
            dados_jogo->mat[j][i] = ' ';
        }
    }
}

void colocaMatriz(jogo *dados_jogo, dimensoes *tam){
    int aux = 0;
    for (int j = 0; j < tam->l; j++){
        for (int i = 0; i < tam->c; i++){
            if(dados_jogo->mat[j][i] != '\0'){
                if(dados_jogo->frase[aux] != '\0' && dados_jogo->frase[aux] != ' '){
                    dados_jogo->mat[j][i] = dados_jogo->frase[aux];
                    aux++;
                }
            }
            printf("%c", dados_jogo->mat[j][i]);
        }
        printf("\n");
    }
}

void coleta_palavra(jogo *dados_jogo, dimensoes *tam){
    dimensoes dimensao;
    dimensao.l = tam->l;
    dimensao.c = tam->c;
    dados_jogo->palavra = aloca_vetor(&dimensao);
    printf("Digite uma palavra pra achar na matriz\n");
    scanf(" %[^\n]s", dados_jogo->palavra);
}

void printa_colorido_horizontal(jogo *dados_jogo, dimensoes *tam, int linha, int coluna, int aux, bool reversa){
    for(int i = 0; i < tam->l; i++){
        for(int j = 0; j < tam->c; j++){
            if(reversa == true){
                if(j >= coluna-aux+1 && j <= coluna && i == linha){
                    corl(0,255,0);
                    printf("%c", dados_jogo->mat[i][j]);
                    corn();
                }else{
                    printf("%c", dados_jogo->mat[i][j]);
                }
            }else{
                if(j >= coluna && j < coluna+aux && i == linha){
                    corl(0,255,0);
                    printf("%c", dados_jogo->mat[i][j]);
                    corn();
                }else{
                    printf("%c", dados_jogo->mat[i][j]);
                }
            }
        }
        printf("\n");
    }
}

void printa_colorido_vertical(jogo *dados_jogo, dimensoes *tam, int linha, int coluna, int aux, bool reversa){
    for(int i = 0; i < tam->l; i++){
        for(int j = 0; j < tam->c; j++){
            if(reversa == true){
                if(i >= linha-aux+1 && i <= linha && j == coluna){
                    corl(0,255,0);
                    printf("%c", dados_jogo->mat[i][j]);
                    corn();
                }else{
                    printf("%c", dados_jogo->mat[i][j]);
                }
            }else{
                if(i >= linha && i < linha+aux && j == coluna){
                    corl(0,255,0);
                    printf("%c", dados_jogo->mat[i][j]);
                    corn();
                }else{
                    printf("%c", dados_jogo->mat[i][j]);
                }
            }
        }
        printf("\n");
    }
}

void printa_colorido_diagonal_principal(jogo *dados_jogo, dimensoes *tam, int linha, int coluna, int aux, bool reversa, int tam_palavra){
    int auxiliar = 0;
    int controle = 0;
    for(int i = 0; i < tam->l; i++){
        for(int j = 0; j < tam->c; j++){
            if(reversa == true){
                if(controle == 0){
                    linha = linha+1 - tam_palavra;
                    coluna = coluna+1 - tam_palavra;
                    controle++;
                }
                if(i == linha && j == coluna){
                    corl(0,255,0);
                    if(auxiliar < tam_palavra){
                        printf("%c", dados_jogo->mat[i][j]);
                        linha++;
                        coluna++;
                        corn();
                    }else{
                        corn();
                        printf("%c", dados_jogo->mat[i][j]);
                    }
                    auxiliar++;
                }else{
                    printf("%c", dados_jogo->mat[i][j]);
                }
            }else{
                if(i == linha && j == coluna){
                    corl(0,255,0);
                    if(auxiliar < tam_palavra){
                        printf("%c", dados_jogo->mat[i][j]);
                        linha++;
                        coluna++;
                        corn();
                    }else{
                        corn();
                        printf("%c", dados_jogo->mat[i][j]);
                    }
                    auxiliar++;
                }else{
                    printf("%c", dados_jogo->mat[i][j]);
                }
            }
        }
        printf("\n");
    }
}


void printa_colorido_diagonal_secundaria(jogo *dados_jogo, dimensoes *tam, int linha, int coluna, int aux, bool reversa, int tam_palavra){
    int auxiliar = 0;
    int controle = 0;
    for(int i = 0; i < tam->l; i++){
        for(int j = 0; j < tam->c; j++){
            if(reversa == true){
                if(controle == 0){
                    linha = linha+1 - tam_palavra;
                    coluna = coluna-1 + tam_palavra;
                    controle++;
                }
                if(i == linha && j == coluna){
                    corl(0,255,0);
                    if(auxiliar < tam_palavra){
                        printf("%c", dados_jogo->mat[i][j]);
                        linha++;
                        coluna--;
                        corn();
                    }else{
                        corn();
                        printf("%c", dados_jogo->mat[i][j]);
                    }
                    auxiliar++;
                }else{
                    printf("%c", dados_jogo->mat[i][j]);
                }
            }else{
                if(i == linha && j == coluna){
                    corl(0,255,0);
                    if(auxiliar < tam_palavra){
                        printf("%c", dados_jogo->mat[i][j]);
                        linha++;
                        coluna--;
                        corn();
                    }else{
                        corn();
                        printf("%c", dados_jogo->mat[i][j]);
                    }
                    auxiliar++;
                }else{
                    printf("%c", dados_jogo->mat[i][j]);
                }
            }
        }
        printf("\n");
    }
}


void procura_vertical(jogo *dados_jogo, dimensoes *tam, int i, int j){
    int aux = 0;
    int tam_palavra = strlen(dados_jogo->palavra);
    while (aux < tam_palavra)
    {     
        if(dados_jogo->mat[i+aux][j] == dados_jogo->palavra[aux]){
            aux++;
            if(aux == tam_palavra){
                limpa();
                pos(1, 1);
                printf("Achou na vertical de (%d,%d) ate (%d,%d) \n",i+1, j+1, i+aux, j+1);
                printf("\n");
                printa_colorido_vertical(dados_jogo, tam, i, j, aux, false);
                dados_jogo->achou = true;
                break;
            }
        }else{
            break;
        }
    }
}

void procura_vertical_inversa(jogo *dados_jogo, dimensoes *tam, int i, int j){
    int aux = 0;
    int tam_palavra = strlen(dados_jogo->palavra);
    while (aux < tam_palavra)
    {     
        if(i-aux >= 0 && dados_jogo->mat[i-aux][j] == dados_jogo->palavra[aux]){
            aux++;
            if(aux == tam_palavra){
                limpa();
                pos(1, 1);
                printf("Achou na vertical inversa de (%d,%d) ate (%d,%d) \n",i+1, j+1, i+1-aux+1, j+1);
                printf("\n");
                printa_colorido_vertical(dados_jogo, tam, i, j, aux, true);
                dados_jogo->achou = true;
                break;
            }
        }else{
            break;
        }
    }
}

void procura_horizontal(jogo *dados_jogo, dimensoes *tam, int i, int j){
    int aux = 0;
    int tam_palavra = strlen(dados_jogo->palavra);
    while (aux < tam_palavra)
    {     
        if(dados_jogo->mat[i][j+aux] == dados_jogo->palavra[aux]){
            aux++;
            if(aux == tam_palavra){
                limpa();
                pos(1, 1);
                printf("Achou na horizontal de (%d,%d) ate (%d,%d) \n",i+1, j+1, i+1, j+aux);
                printf("\n");
                printa_colorido_horizontal(dados_jogo, tam, i, j, aux, false);
                dados_jogo->achou = true;
                break;
            }
        }else{
            break;
        }
    }
}

void procura_horizontal_inversa(jogo *dados_jogo, dimensoes *tam, int i, int j){
    int aux = 0;
    int tam_palavra = strlen(dados_jogo->palavra);
    while (aux < tam_palavra)
    {     
        if(dados_jogo->mat[i][j-aux] == dados_jogo->palavra[aux]){
            aux++;
            if(aux == tam_palavra){
                limpa();
                pos(1, 1);
                printf("Achou na horizontal inversa de (%d,%d) ate (%d,%d) \n",i+1, j+1, i+1, j+1-aux+1);
                printf("\n");
                printa_colorido_horizontal(dados_jogo, tam, i, j, aux, true);
                dados_jogo->achou = true;
                break;
            }
        }else{
            break;
        }
    }
}

void procura_diagonal_principal(jogo *dados_jogo, dimensoes *tam, int i, int j){
    int aux = 0;
    int tam_palavra = strlen(dados_jogo->palavra);
    while (aux < tam_palavra)
    {     
        if(dados_jogo->mat[i+aux][j+aux] == dados_jogo->palavra[aux]){
            aux++;
            if(aux == tam_palavra){
                limpa();
                pos(1, 1);
                printf("Achou na diagonal principal de (%d,%d) ate (%d,%d) \n",i+1, j+1, i+aux, j+aux);
                printf("\n");
                printa_colorido_diagonal_principal(dados_jogo, tam, i, j, aux, false, tam_palavra);
                dados_jogo->achou = true;
                break;
            }
        }else{
            break;
        }
    }
}

void procura_diagonal_secundaria(jogo *dados_jogo, dimensoes *tam, int i, int j){
    int aux = 0;
    int tam_palavra = strlen(dados_jogo->palavra);
    while (aux < tam_palavra)
    {     
        if( j-aux >= 0 && dados_jogo->mat[i+aux][j-aux] == dados_jogo->palavra[aux]){
            aux++;
            if(aux == tam_palavra){
                limpa();
                pos(1, 1);
                printf("Achou na diagonal secundaria de (%d,%d) ate (%d,%d) \n",i+1, j+1, i+aux, j+1-aux+1);
                printf("\n");
                printa_colorido_diagonal_secundaria(dados_jogo, tam, i, j, aux, false, tam_palavra);
                dados_jogo->achou = true;
                break;
            }
        }else{
            break;
        }
    }
}

void procura_diagonal_principal_inversa(jogo *dados_jogo, dimensoes *tam, int i, int j){
    int aux = 0;
    int tam_palavra = strlen(dados_jogo->palavra);
    while (aux < tam_palavra)
    {     
        if(i-aux >= 0 && j-aux >=0 && dados_jogo->mat[i-aux][j-aux] == dados_jogo->palavra[aux]){
            aux++;
            if(aux == tam_palavra){
                limpa();
                pos(1, 1);
                printf("Achou na diagonal principal inversa de (%d,%d) ate (%d,%d) \n",i+1, j+1, i+1-aux+1, j+1-aux+1);
                printf("\n");
                printa_colorido_diagonal_principal(dados_jogo, tam, i, j, aux, true, tam_palavra);
                dados_jogo->achou = true;
                break;
            }
        }else{
            break;
        }
    }
}

void procura_diagonal_secundaria_inversa(jogo *dados_jogo, dimensoes *tam, int i, int j){
    int aux = 0;
    int tam_palavra = strlen(dados_jogo->palavra);
    while (aux < tam_palavra)
    {     
        if(i-aux >= 0 && dados_jogo->mat[i-aux][j+aux] == dados_jogo->palavra[aux]){
            aux++;
            if(aux == tam_palavra){
                limpa();
                pos(1, 1);
                printf("Achou na diagonal secundaria inversa de (%d,%d) ate (%d,%d) \n",i+1, j+1, i+1-aux+1, j+aux);
                printf("\n");
                printa_colorido_diagonal_secundaria(dados_jogo, tam, i, j, aux, true, tam_palavra);
                dados_jogo->achou = true;
                break;
            }
        }else{
            break;
        }
    }
}

void procura_matriz(jogo *dados_jogo, dimensoes *tam){
    bool valido = false;
    char tentar_novamente;
    dados_jogo->achou = false;
    for(int i = 0; i < tam->l; i++){
        for(int j = 0; j < tam->c; j++){
            if(dados_jogo->achou == false){
                procura_horizontal(dados_jogo, tam, i, j);
                procura_horizontal_inversa(dados_jogo, tam, i, j);
                procura_vertical(dados_jogo, tam, i, j);
                procura_vertical_inversa(dados_jogo, tam, i, j);
                procura_diagonal_principal(dados_jogo, tam, i, j);
                procura_diagonal_principal_inversa(dados_jogo, tam, i, j);
                procura_diagonal_secundaria(dados_jogo, tam, i, j);
                procura_diagonal_secundaria_inversa(dados_jogo, tam, i, j);
            }
        }
    }
    
    if(dados_jogo->achou == false){
        do{
            printf("Nao achou, quer tentar novamente? s/n ");
            scanf(" %c", &tentar_novamente);
            if(tentar_novamente != 's' && tentar_novamente != 'n'){
                valido = false;
            }else{
                valido = true;
            }
        }while (!valido);
        if(tentar_novamente == 'n'){
            dados_jogo->jogar = false;
        }
    }else if(dados_jogo->achou == true){
    do{
            printf("Achou, quer procurar novamente? s/n ");
            scanf(" %c", &tentar_novamente);
            if(tentar_novamente != 's' && tentar_novamente != 'n'){
                valido = false;
            }else{
                valido = true;
            }
        }while (!valido);
        if(tentar_novamente == 'n'){
            dados_jogo->jogar = false;
        } 
    }
    dados_jogo->achou = false;
}