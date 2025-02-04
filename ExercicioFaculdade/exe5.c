#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Node{
  int chaveInt;
  float *sublista;
  int sublista_size;
  struct Node *next;
}Node;

Node* create_node(int chaveInt){
  Node *node = (Node*)malloc(sizeof(Node));
  node->chaveInt = chaveInt;
  node->sublista = NULL;
  node->sublista_size = 0;
  node->next = NULL;
  return node;
}

int ja_tem_na_sublista(Node *node, float valor){
  for(int i = 0; i < node->sublista_size; i++){
    if(fabs(node->sublista[i] - valor) < 1e-6){
      return 1;
    }
  }
  return 0;
}

void adiciona_sublista(Node *node, float valor){
  if(ja_tem_na_sublista(node, valor)){
    return;
  }

  node->sublista = realloc(node->sublista, (node->sublista_size + 1) * sizeof(float));
  node->sublista[node->sublista_size] = valor;
  node->sublista_size++;

  for(int i = 0; i < node->sublista_size - 1; i++){
    for(int j = 0; j < node->sublista_size - i - 1; j++){
      if(node->sublista[j] > node->sublista[j + 1]){
        float temporario = node->sublista[j];
        node->sublista[j] = node->sublista[j + 1];
        node->sublista[j + 1] = temporario;
      }
    }
  }
}

Node* insert_node(Node *node, int chaveInt){
  Node *itemNode = node;
  while(itemNode){
    if(itemNode->chaveInt == chaveInt){
      return node;
    }
    itemNode = itemNode->next;
  }

  Node *new_node = create_node(chaveInt);
  if(!node || chaveInt < node->chaveInt){
    new_node->next = node;
    return new_node;
  }

  itemNode = node;
  while (itemNode->next && itemNode->next->chaveInt < chaveInt){
    itemNode = itemNode->next;
  }

  new_node->next = itemNode->next;
  itemNode->next = new_node;

  return node;
}

void verifica_float(Node *node, float valor){
  int parte_inteira = (int)valor;
  Node *itemNode = node;
  Node *melhor_node = NULL;
  float menor_diferenca = 1.0;

  while(itemNode){
    if (itemNode->chaveInt == parte_inteira){
      adiciona_sublista(itemNode, valor);
      return;
    }
    float diferenca = fabs(itemNode->chaveInt - valor);
    if(diferenca < 1.0 && diferenca < menor_diferenca){
      melhor_node = itemNode;
      menor_diferenca = diferenca;
    }
    itemNode = itemNode->next;
  }

  if(melhor_node){
    adiciona_sublista(melhor_node, valor);
  }
}

void imprime_lista(Node *node, FILE *fp_out){
  fprintf(fp_out, "[");
  while(node){
    fprintf(fp_out, "%d(", node->chaveInt);
    for(int i = 0; i < node->sublista_size; i++){
      fprintf(fp_out, "%g", node->sublista[i]);
      if(i < node->sublista_size - 1){
        fprintf(fp_out, "->");
      }
    }
    fprintf(fp_out, ")");
    if(node->next) {
      fprintf(fp_out, "->");
    }
    node = node->next;
  }
  fprintf(fp_out, "]\n");
}

void limpa_lista(Node *node){
  while(node){
    Node *temporario = node;
    free(temporario->sublista);
    node = node->next;
    free(temporario);
  }
}

int main(){
  char linha[256];
  FILE *fp_in = fopen("L1Q3.in", "r");
  FILE *fp_out = fopen("L1Q3.out", "w");
  if(!fp_in || !fp_out){
    printf("Erro ao abrir o arquivo");
    return EXIT_FAILURE;
  }

  Node *node = NULL;

  while(fgets(linha, sizeof(linha), fp_in)){
    char *token = strtok(linha, " ");
    while(token){
      if(strcmp(token, "LE") == 0){
        token = strtok(NULL, " ");
        while(token && strcmp(token, "LI") != 0){
          int chaveInt = atoi(token);
          node = insert_node(node, chaveInt);
          token = strtok(NULL, " ");
        }
      }else if(strcmp(token, "LI") == 0){
        token = strtok(NULL, " ");
        while(token){
          if(strchr(token, '.')){
            float valor = atof(token);
            verifica_float(node, valor);
          }
          token = strtok(NULL, " ");
        }
      }
    }

    imprime_lista(node, fp_out);

    limpa_lista(node);
    node = NULL;
  }

  fclose(fp_in);
  fclose(fp_out);

  return 0;
}
