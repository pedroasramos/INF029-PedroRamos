#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_RANGE 100000
#define TAM_STRING 50

typedef struct Pilha{
  char **S;
  int top;
  int size;
}Pilha;

void inicializador(Pilha * pilha){
  pilha->S = malloc(sizeof(char *));
  pilha->top = -1;
  pilha->size = TAM_STRING;
}

void push(Pilha *pilha, char *str){
  pilha->top++;
  char **temp = realloc(pilha->S, (pilha->top + 2) * sizeof(char *));
  if(temp == NULL){
    fprintf(stderr, "Erro ao realocar memória.\n");
    exit(EXIT_FAILURE);
  }
  pilha->S = temp;
  pilha->S[pilha->top] = malloc(pilha->size * sizeof(char));
  strcpy(pilha->S[pilha->top], str);
}

char *pop(Pilha * pilha){
  if(pilha->top == -1){
    return NULL;
  }
  char *val = pilha->S[pilha->top]  ;
  pilha->top--;
  return val;
}

void trim(char *str) {
  char *end;
  // Remove espaços no final
  end = str + strlen(str) - 1;
  while (end > str && (*end == '\n' || *end == '\r' || *end == ' ')) {
    *end = '\0';
    end--;
  }
  // Remove espaços no início (opcional)
  while (*str == ' ') {
    str++;
  }
}

int main(){

  FILE *fp_in = fopen("L1Q2.in", "r");
  FILE *fp_out = fopen("L1Q2.out", "w");
  if(!fp_in || !fp_out){
    printf("Erro ao abrir arquivo!");
    return EXIT_FAILURE;
  }
  Pilha *pilha = malloc(sizeof(Pilha));
  Pilha *cache = malloc(sizeof(Pilha));
  inicializador(pilha);
  inicializador(cache);
  char linha[MAX_RANGE];
  char *nome;
  char delimitador_externo[] = " ";
  char *contexto_externo = NULL;

  while(fgets(linha, sizeof(linha), fp_in) != NULL){
    trim(linha); // Remove espaços e quebras de linha extras

    if (strlen(linha) == 0) {
      continue; // Pula linhas vazias
    }
    nome = strtok_r(linha, delimitador_externo, &contexto_externo);
    while(nome != NULL){
      int contPop = 0;
      while(pilha->top >= 0 && strcmp(pilha->S[pilha->top], nome) > 0){
        push(cache, pop(pilha));
        contPop++;
      }
      if(contPop > 0){
        fprintf(fp_out, "%dx-pop ",contPop);
      }
      push(pilha, nome);
      fprintf(fp_out, "push-%s ", nome);
      while(cache->top >= 0){
        fprintf(fp_out, "push-%s ", cache->S[cache->top]);
        push(pilha, pop(cache));
      }

      nome = strtok_r(NULL, delimitador_externo, &contexto_externo);
    }
    fprintf(fp_out, "\n");
    while(pilha->top >= 0){
      free(pop(pilha));
    }
    while(cache->top >=0){
      free(pop(cache));
    }
  }
  fclose(fp_in);
  fclose(fp_out);
  
  free(pilha->S);
  free(pilha);
  free(cache->S);
  free(cache);

  return 0;
}