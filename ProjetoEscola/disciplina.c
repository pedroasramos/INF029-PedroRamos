#include <stdio.h>
#include <string.h>
#include "disciplina.h"


int menuDisciplina() {
  int menu;
  printf("0 - Voltar\n");
  printf("1 - Cadastrar Disciplina\n");
  printf("2 - Listar Disciplina\n");
  printf("3 - Atualizar Disciplina\n");
  printf("4 - Excluir Disciplina\n");

  scanf("%d", &menu);

  return menu;
}

int cadastrarDisciplina(Disciplina listaDisciplinas[], int qtdDisciplinas) {
  printf("1 - Cadastrar Disciplina\n");
  if (qtdDisciplinas == TAM_DISCIPLINA) {
    return LISTA_DISCIPLINA_CHEIA;
  } else {
    printf("Informe a disciplina:\n");
    char nomeDisciplina[TAM_NOME_DISCIPLINA];
//    fgets(nomeDisciplina, 20, stdin);
     scanf("%s", nomeDisciplina);
    if(strcmp(nomeDisciplina, " ") == 0){
      return DISCIPLINA_INVALIDA;
    }

    else{
      strcpy(listaDisciplinas[qtdDisciplinas].nome, nomeDisciplina);
      listaDisciplinas[qtdDisciplinas].ativo = 1;
    
      // codDisciplina++;
      // listaDisciplinas[qtdDisciplinas].codigo = codDisciplina;

      return CAD_DISCIPLINA_SUCESSO;
    }
  }
}

void listarDisciplina(Disciplina listaDisciplinas[], int qtdDisciplinas) {
  printf("Listar Disciplinas\n");
  if (qtdDisciplinas == 0) {
    printf("Lista vazia\n");
  } else {
    for (int i = 0; i < qtdDisciplinas; i++) {
      if (listaDisciplinas[i].ativo == 1) {
        //printf("Disciplina: %d\n", listaDisciplinas[i].codigo);
        printf("Disciplina: %s\n", listaDisciplinas[i].nome);
      }
    }
  }
}

int atualizarDisciplina(Disciplina listaDisciplinas[], int qtdDisciplinas) {
 printf("3 - Atualizar Disciplina\n");
 printf("Informe o nome da disciplina:\n");
 char discipli[TAM_NOME_DISCIPLINA];
 int achou = 0;
 scanf("%s", discipli);
 if(strcmp(discipli, " ") == 0){
      return DISCIPLINA_INVALIDA;
    } else {
   for (int i = 0; i < qtdDisciplinas; i++) {
     if (!strcmp(listaDisciplinas[i].nome, discipli) && listaDisciplinas[i].ativo) {
       printf("Informe o novo nome da disciplina:\n");
       char novoNomeDisciplina[TAM_NOME_DISCIPLINA];
       scanf("%s", novoNomeDisciplina);
       strcpy(listaDisciplinas[i].nome, novoNomeDisciplina);
       achou = 1;  
     }   
   }
 }
  if(achou){
    return ATUALIZACAO_DISCIPLINA_SUCESSO;
  }else{
    return DISCIPLINA_INEXISTE;
  }
}

int excluirDisciplina(Disciplina listaDisciplinas[], int qtdDisciplinas){
  printf("4 - Excluir Disciplina\n");
  printf("Informe a disciplina\n");
  char disciplina[TAM_NOME_DISCIPLINA];
  scanf("%s", disciplina);
  int achou = 0;
  if(strcmp(disciplina, " ") == 0){
    return DISCIPLINA_INVALIDA;
  }else{
    for(int i = 0; i < qtdDisciplinas; i++){
      if(!strcmp(listaDisciplinas[i].nome, disciplina) && listaDisciplinas[i].ativo){
        listaDisciplinas[i].ativo = 0;
        for (int j = i; j < qtdDisciplinas - 1; j++) {
          strcpy(listaDisciplinas[j].nome, listaDisciplinas[j+1].nome);
          listaDisciplinas[j].ativo = listaDisciplinas[j+1].ativo;
          achou = 1;
        }
      }
    }
    if(achou){
      return EXCLUIR_DISCIPLINA_SUCESSO;
    }else{
      return DISCIPLINA_INEXISTE;
    }
  }
}