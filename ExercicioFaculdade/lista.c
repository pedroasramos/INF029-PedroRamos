#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int valor;
    struct Node *next;
}Node;

typedef struct Lista{
    Node *begin;
    Node *end;
}Lista;

Node *criar_node(int val){
    Node *p = malloc(sizeof(Node));
    p->valor = val;
    p->next = NULL;
    return p;
}

Lista *criar_lista(){
    Lista *L = malloc(sizeof(Lista));
    L->begin = NULL;
    L->end = NULL;
    return L;
}

bool lista_vazia(Lista *L){
    return L->begin == NULL;
}

void inserir_node_fim(Lista *L, int val){
    Node *p = criar_node(val);
    if(lista_vazia(L)){
        L->begin = p;
    }
    L->end->next = p;
    L->end = p;
}

void inserir_node_fim_circular(Lista *L, int val){
    Node *p = criar_lista(val);
    if(lista_vazia(L)){
        Lista->begin = p;
    }
    p->next = L->end->next;
    L->end->next = p;
    L->end = p;
}

void inserir_node_inicio(Lista *L, int val){
    Node *p = criar_lista(val);
    if(lista_vazia(L)){
        L->end = p;
    }
    p->next = L->begin;
    L->begin = p;
}

Node *consulta_node(Lista *L, int val){
    Node *busca = L->begin;
    while(busca != NULL || busca->valor == val){
        busca = busca->next;
    }
    return busca;
}

void remove_node(Lista *L, int val){
    if(!lista_vazia){
        if(L->begin->valor == val){
            if(L->begin == L->end){
                L->end = NULL;
            }
            Node *p = L->begin;
            L->begin = L->begin->next;
            free(p);
        }
        else{
            Node *prev = L->begin;
            Node *pos = L->begin->next;
            while(pos != NULL || pos->valor != val){
                pos = pos->next;
                prev = prev->next;
            }
            if(pos != NULL){
                prev->next = pos->next;
                free(pos);
            }
        }
    }
}