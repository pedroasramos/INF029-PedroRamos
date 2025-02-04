#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "professor.h"

int menuProfessor() {
  int menu;
  printf("0 - Voltar\n");
  printf("1 - Cadastrar Professor\n");
  printf("2 - Listar Professor\n");
  printf("3 - Atualizar Professor\n");
  printf("4 - Excluir Professor\n");

  scanf("%d", &menu);

  return menu;
}

int cadastrarProfessor(Professor listaProfessores[], int qtdProfessores) {
  printf("1 - Cadastrar Professor\n");
  if (qtdProfessores == TAM_PROFESSOR) {
    return LISTA_PROFESSOR_CHEIA;
  } else {
    char nome[TAM_NOME];
    char sexo;
    char dataNasc[TAM_DATA_NASCIMENTO];
    char cpf[TAM_CPF];
    printf("Informe o nome do professor\n");
    scanf("%s", nome);
    printf("Informe o sexo do professor\n");
    scanf("%s", &sexo);
    printf("Informe a data de nascimento do professor\n");
    scanf("%s", dataNasc);
    printf("Informe o cpf do professor\n");
    scanf("%s", cpf);
    if (strcmp(nome, " ")) {
      return MATRICULA_PROFESSOR_INVALIDA;
    } else {
      strcpy(listaProfessores[qtdProfessores].nome, nome);
      // listaProfessores[qtdProfessores].matricula = criaMatriculasProfessores();
      strcpy(&listaProfessores[qtdProfessores].sexo, &sexo);
      strcpy(listaProfessores[qtdProfessores].dataNascimento, dataNasc);
      strcpy(listaProfessores[qtdProfessores].cpf, cpf);
      listaProfessores[qtdProfessores].ativo = 1;

      return CAD_PROFESSOR_SUCESSO;
    }
  }
}

void listarProfessor(Professor listaProfessores[], int qtdProfessores) {
  printf("2 - Listar Professor\n");
  if (qtdProfessores == 0) {
    printf("Lista de Professores vazia\n");
  } else {
    for (int i = 0; i < qtdProfessores; i++) {
      if (listaProfessores[i].ativo)
        printf("Matrícula: %d Nome: %s\n", listaProfessores[i].matricula, listaProfessores[i].nome);
    }
  }
}

int atualizarProfessor(Professor listaProfessores[], int qtdProfessores) {
  printf("3 - Atualizar Professor\n");
  printf("Informe a matricula:\n");
  int matricula;
  int achou = 0;
  scanf("%d", &matricula);
  if (matricula < 0) {
    return MATRICULA_PROFESSOR_INVALIDA;
  } else {
    for (int i = 0; i < qtdProfessores; i++) {
      if (matricula == listaProfessores[i].matricula &&
          listaProfessores[i].ativo) {
        printf("Informe a nova matricula:\n");
        int novaMatricula;
        scanf("%d", &novaMatricula);
        listaProfessores[i].matricula = novaMatricula;
        achou = 1;
        break;
      }
    }
    if (achou)
      return ATUALIZACAO_PROFESSOR_SUCESSO;
    else
      return MATRICULA_PROFESSOR_INEXISTE;
  }
}

int excluirProfessor(Professor listaProfessores[], int qtdProfessores) {
  printf("4 - Excluir Professor\n");
  printf("Informe a matricula:\n");
  int matricula;
  int achou = 0;
  scanf("%d", &matricula);
  if (matricula < 0) {
    return MATRICULA_PROFESSOR_INVALIDA;
  } else {
    for (int i = 0; i < qtdProfessores; i++) {
      if (matricula == listaProfessores[i].matricula) {
        listaProfessores[i].ativo = 0;
        for (int j = i; j < qtdProfessores - 1; j++) {
          listaProfessores[j].matricula = listaProfessores[j + 1].matricula;
          listaProfessores[j].sexo = listaProfessores[j + 1].sexo;
          listaProfessores[j].ativo = listaProfessores[j + 1].ativo;
        }

        achou = 1;
        break;
      }
    }
    if (achou)
      return EXCLUIR_PROFESSOR_SUCESSO;
    else
      return MATRICULA_PROFESSOR_INEXISTE;
  }
}