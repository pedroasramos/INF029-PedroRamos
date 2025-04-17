#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#define MAX_RANGE 250


float distance(float *vetorX, float *vetorY, int size){
  float vetorDist[size];
  memset(vetorDist, 0, sizeof(vetorDist));
  float dist = 0;
  for(int i = 0; i < size-1; i++){
    vetorDist[i] = sqrt(pow(vetorX[i+1] - vetorX[i],2) + pow(vetorY[i+1] - vetorY[i],2));
  }
  for(int i = 0; i < size; i++){
    dist += vetorDist[i];
  }
  return dist;
}

float shortcut(float *vetorX, float *vetorY, int size){
  float shortc = sqrt(pow(vetorX[size-1] - vetorX[0],2) + pow(vetorY[size-1] - vetorY[0],2));
  return shortc;
}

float distancia_origem(int vetorX, int vetorY){
  return sqrt(pow(vetorX, 2) + pow(vetorY, 2));
}

void ordena_vetor(int *vetorX, int *vetorY, int size){
  for(int i=1; i<size; i++){
    int xAtual = vetorX[i];
    int yAtual = vetorY[i];
    float distAtual = distancia_origem(xAtual, yAtual);
    int j = i-1;

    while(j >= 0){
      float distAnterior = distancia_origem(vetorX[j], vetorY[j]);
      if(distAtual >= distAnterior){
        break;
      }
      vetorX[j +1] = vetorX[j];
      vetorY[j +1] = vetorY[j];
      j--;
    }
    vetorX[j +1] = xAtual;
    vetorY[j +1] = yAtual;    
  }
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

  FILE *fp_in = fopen("L0Q1.in", "r");
  FILE *fp_out = fopen("L0Q1.out", "w");

  if(fp_in == NULL || fp_out == NULL){
    printf("\nArquivo indisponível");
    return EXIT_FAILURE;
  }

  char arquivo[MAX_RANGE];
  char delimitadores_externos[] = "\t\n";
  char delimitadores_internos[] = "(,) ";
  char *contexto_externo = NULL;
  char *contexto_interno = NULL;
  char *valor_externo;
  int contador = 1;
  int total_linhas = contador_linhas("L0Q1.in");
  int cont =0;
  int contX =0;
  int contY =0;
  float vetor[MAX_RANGE];
  float ladoX[MAX_RANGE], ladoY[MAX_RANGE];
  int copiaX[MAX_RANGE], copiaY[MAX_RANGE];

  while(fgets(arquivo, sizeof(arquivo), fp_in) != NULL){
    valor_externo = strtok_r(arquivo, delimitadores_externos, &contexto_externo);

    while(valor_externo != NULL){
      char *valor_interno = strtok_r(valor_externo, delimitadores_internos, &contexto_interno);

      while(valor_interno != NULL){
        vetor[cont] = atoi(valor_interno);
        cont++;
        valor_interno = strtok_r(NULL, delimitadores_internos, &contexto_interno);
      }

      for(int i=0; i<cont; i++){
        if(i % 2 == 0){
          ladoX[contX] = vetor[i];
          contX++;
        }
        else{
          ladoY[contY] = vetor[i];
          contY++;
        }
      }

      for(int i = 0; i<contX; i++){
        copiaX[i] = ladoX[i];
        copiaY[i] = ladoY[i];
      }

      float distancia = distance(ladoX, ladoY, contX);
      float shortc = shortcut(ladoX, ladoY, contX);
      
      fprintf(fp_out, "points");
      for(int i =0; i<contX; i++){
        copiaX[i] = (int)ladoX[i];
        copiaY[i] = (int)ladoY[i];
      }
      ordena_vetor(copiaX, copiaY, contX);
      
      for(int i =0; i<contX; i++){
        fprintf(fp_out," (%d,%d)", copiaX[i], copiaY[i]);
      }
      fprintf(fp_out, " distance");      
      fprintf(fp_out, " %.2f",distancia);
      fprintf(fp_out, " shortcut");      
      fprintf(fp_out, " %.2f", shortc);
      if(contador < total_linhas) fprintf(fp_out, "\n");
      contador++;
      
      contX = 0;
      contY = 0;
      cont = 0;
      
      valor_externo = strtok_r(NULL, delimitadores_externos, &contexto_externo);
    }
  }  
  return 0;
}