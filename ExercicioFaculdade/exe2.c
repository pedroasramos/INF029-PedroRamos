#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAX_RANGE 1000
#define MAX_STRING 50

void ordena_strings(char vetor[][MAX_STRING], int n){
  for(int i = 1; i < n; i++){
    char chave[MAX_STRING];
    strcpy(chave, vetor[i]);
    int j = i - 1;

    while (j >= 0 && strcmp(vetor[j], chave) > 0) {
      strcpy(vetor[j + 1], vetor[j]);
      j--;
    }
    strcpy(vetor[j + 1], chave);
  }
}

void ordena_inteiros(int vetor[], int n){
  for(int i = 1; i < n; i++){
    int chave = vetor[i];
    int j = i - 1;

    while (j >= 0 && vetor[j] > chave){
      vetor[j + 1] = vetor[j];
      j--;
    }
    vetor[j + 1] = chave;
  }
}

void ordena_floats(float vetor[], int n){
  for(int i = 1; i < n; i++){
    float chave = vetor[i];
    int j = i - 1;

    while(j >= 0 && vetor[j] > chave){
      vetor[j + 1] = vetor[j];
      j--;
    }
    vetor[j + 1] = chave;
  }
}

float distancia_ponto(float x, float y){
  return sqrt(pow(x,2) + pow(y,2));
}

void ordena_pontos(float pontos[][2], int n){
  for(int i = 1; i < n; i++){
    float chave_x = pontos[i][0];
    float chave_y = pontos[i][1];
    float chave_distancia = distancia_ponto(chave_x, chave_y);
    int j = i - 1;

    while(j >= 0 && distancia_ponto(pontos[j][0], pontos[j][1]) > chave_distancia){
      pontos[j + 1][0] = pontos[j][0];
      pontos[j + 1][1] = pontos[j][1];
      j--;
    }
    pontos[j + 1][0] = chave_x;
    pontos[j + 1][1] = chave_y;
  }
}

bool verifica_ponto(const char *valor, float *x, float *y){
  if(valor[0] == '(' && valor[strlen(valor) - 1] == ')'){
    char temp[MAX_STRING];
    strncpy(temp, valor + 1, strlen(valor) - 2);
    temp[strlen(valor) - 2] = '\0';

    char *token = strtok(temp, ",");
    if(token != NULL){
      *x = atof(token);

      token = strtok(NULL, ",");
      if(token != NULL){
        *y = atof(token);
        return true;
      }
    }
  }
  return false;
}

void identifica_tipo(char *arquivo, int *vetorInt, float *vetorFlo, char vetorStr[][MAX_STRING], float vetorPontos[][2], int *contI, int *contF, int *contS, int *contP){
  char *endptr;
  float x, y;

  if(verifica_ponto(arquivo, &x, &y)){
    vetorPontos[*contP][0] = x;
    vetorPontos[*contP][1] = y;
    (*contP)++;
    return;
  }

  int inteiro = strtol(arquivo, &endptr, 10);
  if(*endptr == '\0'){
    vetorInt[*contI] = inteiro;
    (*contI)++;
    return;
  }

  float flutuante = strtof(arquivo, &endptr);
  if(*endptr == '\0'){
    vetorFlo[*contF] = flutuante;
    (*contF)++;
    return;
  }

  strncpy(vetorStr[*contS], arquivo, MAX_STRING - 1);
  vetorStr[*contS][MAX_STRING - 1] = '\0';
  (*contS)++;
}

int contador_linhas(char *arvivo_entrada){
  FILE *arquivo = fopen(arvivo_entrada, "r");
  if(!arquivo) return -1;
  int linhas = 0;
  char tamanho[MAX_RANGE];

  while(fgets(tamanho, sizeof(tamanho), arquivo)){
    linhas++;
  }
  free(arquivo);
  return linhas;
}

int main(){
  FILE *fp_in = fopen("L0Q2.in", "r");
  FILE *fp_out = fopen("L0Q2.out", "w");

  if(fp_in == NULL || fp_out == NULL){
    printf("\nArquivo indisponível");
    return EXIT_FAILURE;
  }

  char arquivo[MAX_RANGE];
  char delimitadores_externos[] = "\t\n";
  char delimitadores_internos[] = " ";
  char *contexto_externo = NULL;
  char *contexto_interno = NULL;
  int contador = 1;
  int total_linhas = contador_linhas("L0Q2.in");

  while(fgets(arquivo, sizeof(arquivo), fp_in) != NULL){
    int vetorInt[MAX_RANGE], contInt = 0;
    float vetorFloat[MAX_RANGE], vetorPontos[MAX_RANGE][2];
    int contFlo = 0, contPon = 0;
    char vetorStr[MAX_RANGE][MAX_STRING];
    int contStr = 0;
    bool flag = false;

    char *valor_externo = strtok_r(arquivo, delimitadores_externos, &contexto_externo);

    while(valor_externo != NULL){
      char *valor_interno = strtok_r(valor_externo, delimitadores_internos, &contexto_interno);

      while(valor_interno != NULL){
        identifica_tipo(valor_interno, vetorInt, vetorFloat, vetorStr, vetorPontos, &contInt, &contFlo, &contStr, &contPon);
        valor_interno = strtok_r(NULL, delimitadores_internos, &contexto_interno);
      }

      valor_externo = strtok_r(NULL, delimitadores_externos, &contexto_externo);
    }

        
    if(contStr > 0){
      ordena_strings(vetorStr, contStr);
    } 
    if(contInt > 0){
      ordena_inteiros(vetorInt, contInt);
    } 
    if(contFlo > 0){
      ordena_floats(vetorFloat, contFlo);
    } 
    if(contPon > 0){
      ordena_pontos(vetorPontos, contPon);
    } 

    fprintf(fp_out, "str:");
    for (int i = 0; i < contStr; i++) {
      fprintf(fp_out, "%s%s", vetorStr[i], i < contStr - 1 ? " " : "");
    }
  
    fprintf(fp_out, " int:");
    for(int i = 0; i < contInt; i++){
      fprintf(fp_out, "%d%s", vetorInt[i], i < contInt - 1 ? " " : "");
    }
  
    fprintf(fp_out, " float:");
    for(int i = 0; i < contFlo; i++){
      fprintf(fp_out, "%g%s", vetorFloat[i], i < contFlo - 1 ? " " : "");
    }

    fprintf(fp_out, " p:");
    for(int i = 0; i < contPon; i++){
      fprintf(fp_out, "(%g,%g)%s", vetorPontos[i][0], vetorPontos[i][1], i < contPon - 1 ? " " : "");
    }
    
    if(contador < total_linhas) fprintf(fp_out, "\n");
    contador++;
  }

  fclose(fp_in);
  fclose(fp_out);

  return 0;
}
