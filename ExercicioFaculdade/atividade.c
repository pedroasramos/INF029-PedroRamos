#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#define MAX_RANGE 255


bool ehinteiro(char *str){
  if(*str == '-' || *str == '+') str++;
  if(*str == '\0') return false;
  while(*str){
    if(!isdigit(*str)) return false;
    str++;
  }
  return true;
}

bool ehfloat(char *str){
  int temPonto = false;
  if(*str == '-' || *str == '+') str++;
  if(*str == '\0') return false;
  
  while(*str){
    if(*str == '.'){
      temPonto = true;
    }
    // else if(!isdigit(*str)){
    //   return false;
    // }
    str++;
  }
  return temPonto;
}

int ehponto222(char *str, float *vetorX, float *vetorY, int cont){
  int size = strlen(str);

  if(size < 5) return false;
  if(str[0] != '(' || str[size - 1] != ')') return false;

  char *virg = strchr(str, ',');
  if(!virg) return false;

  *virg = '\0';
  char *ladoX = str +1;
  char *ladoY = virg +1;
  ladoY[size -1] = '\0';

  bool ehValida = (ehinteiro(ladoX) || ehfloat(ladoX)) &&  (ehinteiro(ladoY) || ehfloat(ladoY));

  if(ehValida){
    vetorX[cont] = atof(ladoX);
    vetorY[cont] = atof(ladoY);
  }

  *virg =',';

  return ehValida;

}

bool ehponto(char *str){

  int size = strlen(str);

  if(size < 5 || str[0] != '(' || str[size-1] !+ ')') return false;

  char *virgula = strchr(str, ',');
  if(!virgula) return false;  
  *virgula = '\0';

  char *ladoX = str +1;
  char *ladoY = virgula +1;
  ladoY[strlen(ladoY -1)] = '\0';

  bool valida = (ehinteiro(ladoX) || ehfloat(ladoX)) && (ehinteiro(ladoY) || ehfloat(ladoY));

  *virgula = ',';

  return valida;
}


int main(){
  FILE *fp_in = fopen("L0Q2.in", "r");
  FILE *fp_out = fopen("L0Q2.out", "w");

  if(fp_in == NULL || fp_out == NULL){
    printf("Arquivo não pode ser aberto.");
    return EXIT_FAILURE;
  }

  char linha[MAX_RANGE];
  const char delimitadores_externos[] = "\t\n";
  const char delimitadores_internos[] = " ";
  char *contexto_externo;
  char *contexto_interno;
  

  char vetorStrings[MAX_RANGE];
  int vetorInteiro[MAX_RANGE];
  float vetorFloat[MAX_RANGE], 
  vetorX[MAX_RANGE], vetorY[MAX_RANGE];
  int contStr = 0; int contInt = 0; int contFlo = 0; int contPon = 0;

  while(fgets(linha, sizeof(linha), fp_in) != NULL){
    char *valor_externo = strtok_r(linha , delimitadores_externos, &contexto_externo);

    while(valor_externo != NULL){
      char *valor_interno  = strtok_r(valor_externo, delimitadores_internos, &contexto_interno);
      while(valor_interno != NULL){
        if(isdigit(valor_interno[0]) || valor_interno[0] == '-'){
          if(strchr(valor_interno, '.') != NULL){
            vetorFloat[contFlo] = atof(valor_interno);
            contFlo++;
          }
          else{
            vetorInteiro[contInt] = atoi(valor_interno);
            contInt++;
          }
        }
        else if(strchr(valor_interno, '(')){
          sscanf("(%f,%f)",vetorX[contPon], vetorY[contPon]);
          contPon++;
        }
        else{
          vetorStrings[contStr] = valor_interno;
        }
        valor_interno = strtok_r(NULL, delimitadores_internos, &contexto_interno);
      }
      
      valor_externo = strtok_r(NULL, delimitadores_externos, &contexto_externo);
    }
  }
  if(contInt){
    for(int i =0; i<contInt; i++){
      printf("vetorInteiro %d\n", vetorInteiro[i]);
    }
  }
  if(contFlo){
    for(int i =1; i<contFlo; i++){
      printf("vetorFloat %.1f\n", vetorFloat[i]);
    }
  }
  if(contStr){
    for(int i = 1; i<contStr; i++){
      printf("vetorStrings %s\n", vetorStrings[i]);
    }
  }
  if(contPon){
    for(int i =0;i<contPon; i++){
      printf("vetorPonto %.1f %.1f", vetorX[i], vetorY[i]);
    }
  }
}