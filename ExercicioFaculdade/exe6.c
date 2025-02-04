#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_RANGE 100000

typedef struct Node{
  struct Node *direita, *esquerda, *pai;
  int val;
}Node;

typedef struct Arvore{
  Node *raiz;
}Arvore;

Node *cria_node(int val){
  Node *p = malloc(sizeof(Node));
  p->direita = p->esquerda = p->pai = NULL;
  p->val = val;
  return p;
}

Arvore *cria_arvore(){
  Arvore *arv = malloc(sizeof(Arvore));
  arv->raiz = NULL;
  return arv;
}

void insere_node(Arvore *arvore, Node *node){
  if(arvore->raiz == NULL) arvore->raiz = node;
  else{
    Node *buscador = arvore->raiz;
    Node *pai;
    while(buscador != NULL){
      pai = buscador;
      if(buscador->val < node->val) buscador = buscador->esquerda;
      else buscador = buscador->direita;
    }
    if(pai->val < node->val) pai->esquerda = node;
    else pai->direita = node;
    node->pai = pai;
  }
}

int main(){
  FILE *fp_in = fopen("L2Q1.in", "r");
  FILE *fp_out = fopen("L2Q1.out", "w");
  if(!fp_in || !fp_out){
    printf("Não foi possível ler os arquivos!");
    return EXIT_FAILURE;
  }

  Arvore *arvore = cria_arvore();
  char linhas[MAX_RANGE];
  int numero;
  Node *ponteiro;

  while(fgets(linhas, sizeof(linhas), fp_in)){
    char *valor = strtok(linhas, " ");
    while(valor){
      numero = atoi(valor);
      ponteiro = cria_node(numero);
      insere_node(arvore, ponteiro);



      valor = strtok(NULL, " ");
    }
    
    void imprime_arvore(Node *node){
      if(node != NULL){
        imprime_arvore(node->esquerda);
        printf("%d - ", node->val);
        imprime_arvore(node->direita);
      }
    }
    
    
    
  }










  fclose(fp_in);
  fclose(fp_out);
  return 0;
}