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
  if(!posicao) return;
  fprintf(fp_out, "%d (%d)", posicao->val, posicao->altura);
  posicao = posicao->prox;
  while(posicao != NULL){
    fprintf(fp_out, " %d (%d)", posicao->val, posicao->altura);
    posicao = posicao->prox;
  }
}

Node *menor_valor(Node *raiz){
  Node *buscador = raiz;
  while(buscador->esquerda != NULL){
    buscador = buscador->esquerda;
  }
  return buscador;
}

Node *remover_node(Node **raiz, Node *node){
  if(node->esquerda == NULL && node->direita == NULL){
    if(node->pai){
      if(node->pai->esquerda == node) node->pai->esquerda = NULL;
      else node->pai->direita = NULL;
    }
    else{
      if(*raiz == node) *raiz = NULL;
    }
    free(node);
    return NULL;
  }

  if(node->direita == NULL || node->esquerda == NULL){
    Node *filho = (node->esquerda != NULL) ? node->esquerda : node->direita;
    if(node->pai){
      if(node->pai->esquerda == node) node->pai->esquerda = filho;
      else node->pai->direita = filho;
    }
    else *raiz = filho;
    filho->pai = node->pai;
    free(node);
    return filho;
  }

  Node *sucessor = menor_valor(node->direita);
  node->val = sucessor->val;
  if(sucessor->pai->esquerda == sucessor) sucessor->pai->esquerda = sucessor->direita;
  else sucessor->pai->direita = sucessor->direita;
  if(sucessor->direita) sucessor->direita->pai = sucessor->pai;
  free(sucessor);
  return node;
}

void liberar_lista(Lista *lista) {
    Node *atual = lista->begin;
    while (atual != NULL) {
        Node *prox = atual->prox;
        atual->prox = NULL;
        atual = prox;
    }
    free(lista);
}

void liberar_arvore(Node *node){
    if(node == NULL) return;
    liberar_arvore(node->esquerda);
    liberar_arvore(node->direita);
    node->direita = node->esquerda = node->pai = node->prox = NULL;
    free(node);
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
  FILE *fp_in = fopen("L2Q3.in", "r");
  FILE *fp_out = fopen("L2Q3.out", "w");
  if(!fp_in || !fp_out){
    printf("Não foi possível ler os arquivos!");
    return EXIT_FAILURE;
  }

  char linhas[MAX_RANGE];
  int numeros;
  int contador = 1;
  int total_linhas = contador_linhas("L2Q3.in");
  while(fgets(linhas, sizeof(linhas), fp_in)){
    Arvore *arvore = cria_arvore();
    Lista *lista =cria_lista();
    char *valor = strtok(linhas, " ");
    while(valor != NULL){
      if(strcmp(valor, "a") == 0){
        valor = strtok(NULL, " ");
        numeros = atoi(valor);
        insere_node(arvore, cria_node(numeros));
      }
      if(strcmp(valor, "r") == 0){
        valor = strtok(NULL, " ");
        if(valor){
          numeros = atoi(valor);
          Node *achei = procura_node(arvore->raiz, numeros);
          if(achei) remover_node(&arvore->raiz, achei);
          else insere_node(arvore, cria_node(numeros));
        }
      }
      valor = strtok(NULL, " ");
    }
    
    altura_node(arvore->raiz);
    ordena_arvore(lista, arvore->raiz);
    imprime_lista(lista, fp_out);
    if(contador < total_linhas) fprintf(fp_out, "\n");
    contador++;
    
    liberar_arvore(arvore->raiz);
    liberar_lista(lista);
    free(arvore);
  }

  fclose(fp_in);
  fclose(fp_out);
  return 0;
}