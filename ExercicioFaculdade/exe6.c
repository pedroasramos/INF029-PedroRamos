#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_RANGE 100000

typedef struct Node{
  struct Node *direita, *esquerda, *pai, *prox;
  int val, altura, cont;
}Node;

typedef struct Arvore{
  Node *raiz;
  int cont;
}Arvore;

typedef struct Lista{
  Node *begin;
}Lista;

Node *cria_node(int val){
  Node *p = malloc(sizeof(Node));
  p->direita = p->esquerda = p->pai = p->prox = NULL;
  p->altura = p->cont = 0;
  p->val = val;
  return p;
}

Arvore *cria_arvore(){
  Arvore *arv = malloc(sizeof(Arvore));
  arv->raiz = NULL;
  arv->cont = -1;
  return arv;
}

Lista *cria_lista(){
  Lista *lista = malloc(sizeof(Lista));
  lista->begin = NULL;
  return lista;
}

void insere_lista(Lista *lista, Node *node){
  if(lista->begin == NULL) lista->begin = node;
  else{
    Node *posicao = lista->begin;
    while(posicao->prox != NULL){
      posicao = posicao->prox;
    }
    posicao->prox = node;
  }
}

void definir_altura(Node *node, int altura){
  if(node == NULL) return;
  node->altura = altura;
  definir_altura(node->esquerda, altura +1);
  definir_altura(node->direita, altura +1);
}

void altura_node(Node *raiz){
  definir_altura(raiz, 0);
}

void insere_node(Arvore *arvore, Node *node){
  if(arvore->raiz == NULL) arvore->raiz = node;
  else{
    Node *buscador = arvore->raiz;
    Node *pai = NULL;
    while(buscador != NULL){
      pai = buscador;
      if(buscador->val > node->val) buscador = buscador->esquerda;
      else buscador = buscador->direita;
    }
    if(pai->val > node->val) pai->esquerda = node;
    else pai->direita = node;
    node->pai = pai;
  }
  arvore->cont++;
  node->cont = arvore->cont;
}

void imprime_arvore(Node *node){
  if(node != NULL){
    imprime_arvore(node->esquerda);
    printf("(%d) = ", node->val);
    imprime_arvore(node->direita);
  }
}

void imprime_lista(Lista *lista, FILE *fp_out){
  Node *posicao = lista->begin;
  while(posicao != NULL){
    fprintf(fp_out, "%d ", posicao->altura);
    posicao = posicao->prox;
  }
}

Node *maior_valor(Node *raiz){
  Node *buscador = raiz;
  while(buscador->direita != NULL){
    buscador = buscador->direita;
  }
  return buscador;
}

Node *menor_valor(Node *raiz){
  Node *buscador = raiz;
  while(buscador->esquerda != NULL){
    buscador = buscador->esquerda;
  }
  return buscador;
}

Node *predecessor(Node *node){
  if(node == NULL) return NULL;
  if(node->esquerda != NULL){
    Node *pred = node->esquerda;
    while(pred->direita != NULL){
      pred = pred->direita;
    }
    return pred;
  }
  Node *pred = node->pai;
  while(pred != NULL && node == pred->esquerda){
    node = pred;
    pred = pred->pai;
  }
  return pred;
}

int main(){
  FILE *fp_in = fopen("L2Q1.in", "r");
  FILE *fp_out = fopen("L2Q1.out", "w");
  if(!fp_in || !fp_out){
    printf("Não foi possível ler os arquivos!");
    return EXIT_FAILURE;
  }
  
  char linhas[MAX_RANGE];
  int numero;
  Node *ponteiro;

  while(fgets(linhas, sizeof(linhas), fp_in)){
    Arvore *arvore = cria_arvore();
    Lista *lista = cria_lista();
    char *valor = strtok(linhas, " ");
    while(valor){
      numero = atoi(valor);
      ponteiro = cria_node(numero);
      insere_node(arvore, ponteiro);
      insere_lista(lista, ponteiro);

      valor = strtok(NULL, " ");
    }
    
    altura_node(arvore->raiz);
    Node *maior_node = maior_valor(arvore->raiz);
    int maior = maior_node->val;
    int altura = maior_node->altura;
    Node *pred = predecessor(maior_node);
    int prede = pred->val;
    imprime_lista(lista, fp_out);
    fprintf(fp_out,"max %d alt %d pred %d\n", maior, altura, prede);
    
    free(arvore);
    free(lista);
    printf("\n");
    
  }

  fclose(fp_in);
  fclose(fp_out);
  return 0;
}