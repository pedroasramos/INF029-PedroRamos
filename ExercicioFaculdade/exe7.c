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
  if(node == NULL) return;
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

Node *procura_node(Node *node, int val){
  if(node == NULL || node->val == val) return node;
  else{
    if(val < node->val) return procura_node(node->esquerda, val);
    else return procura_node(node->direita, val);
  }
}

void ordena_arvore(Lista *lista, Node *node){
  if(node != NULL){
    ordena_arvore(lista, node->esquerda);
    insere_lista(lista, node);
    ordena_arvore(lista, node->direita);
  }
}

int somador(Node *node){
  if(node == NULL) return 0;
  return node->val + somador(node->esquerda) + somador(node->direita);
}

void imprime_lista(Lista *lista, FILE *fp_out){
  Node *posicao = lista->begin;
  int somaEsquerda = 0, somaDireita = 0;
  while(posicao != NULL){
    somaEsquerda = somador(posicao->esquerda);
    somaDireita = somador(posicao->direita);
    fprintf(fp_out, "%d (%d) ", posicao->val, somaDireita - somaEsquerda);
    posicao = posicao->prox;
  }
}

void liberar_lista(Lista *lista) {
    Node *atual = lista->begin;
    while (atual != NULL) {
        Node *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(lista);
}

int main(){
  FILE *fp_in = fopen("L2Q2.in", "r");
  FILE *fp_out = fopen("L2Q2.out", "w");
  if(!fp_in || !fp_out){
    printf("Não foi possível ler os arquivos!");
    return EXIT_FAILURE;
  }

  char linhas[MAX_RANGE];
  int numeros;
  Node *ponteiro;

  while(fgets(linhas, sizeof(linhas), fp_in)){
    Arvore *arvore = cria_arvore();
    Lista *lista = cria_lista();
    char *valor = strtok(linhas, " ");
    while(valor){
      numeros = atoi(valor);
      ponteiro = cria_node(numeros);
      if(!procura_node(arvore->raiz, ponteiro->val)){
        insere_node(arvore, cria_node(numeros));
      }
      valor = strtok(NULL, " ");
    }
    ordena_arvore(lista, arvore->raiz);
    imprime_lista(lista, fp_out);

    liberar_lista(lista);
    free(arvore);
    fprintf(fp_out, "\n");
  }

  fclose(fp_in);
  fclose(fp_out);
  return 0;
}


