#include <string.h>
#include "aluno.h"


int menuAluno() {
  int menu;
  printf("0 - Voltar\n");
  printf("1 - Cadastrar Aluno\n");
  printf("2 - Listar Aluno\n");
  printf("3 - Atualizar Aluno\n");
  printf("4 - Excluir Aluno\n");

  scanf("%d", &menu);

  return menu;
}

int cadastrarAluno(Aluno listaAlunos[], int qtdAlunos) {
  printf("1 - Cadastrar Aluno\n");
  if (qtdAlunos == TAM_ALUNO) {
    return LISTA_ALUNO_CHEIA;
  } else {
    char nome[TAM_NOME];
    char sexo;
    char dataNasc[TAM_DATA_NASCIMENTO];
    char cpf[TAM_CPF];
    printf("Informe o nome do aluno\n");
    scanf("%s", nome);
    printf("Informe o sexo do aluno\n");
    scanf("%s", &sexo);
    printf("Informe a data de nascimento do aluno\n");
    scanf("%s", dataNasc);
    printf("Informe o cpf do aluno\n");
    scanf("%s", cpf);
    
    if (strcmp(nome, " ")) {
      return MATRICULA_ALUNO_INVALIDA;
    } else {
      strcpy(listaAlunos[qtdAlunos].nome, nome);
      // listaAlunos[qtdAlunos].matricula = criaMatriculasAlunos();
      strcpy(&listaAlunos[qtdAlunos].sexo, &sexo);
      strcpy(listaAlunos[qtdAlunos].dataNascimento, dataNasc);
      strcpy(listaAlunos[qtdAlunos].cpf, cpf);
      listaAlunos[qtdAlunos].ativo = 1;

      return CAD_ALUNO_SUCESSO;
    }
  }
}

void listarAlunos(Aluno listaAlunos[], int qtdAlunos) {
  printf("2 - Listar Aluno\n");
  if (qtdAlunos == 0) {
    printf("Lista de alunos vazia\n");
  } else {
    for (int i = 0; i < qtdAlunos; i++) {
      if (listaAlunos[i].ativo)
        printf("Matrícula: %s\n", listaAlunos[i].nome);
    }
  }
}

int atualizarAluno(Aluno listaAlunos[], int qtdAlunos) {
  char nome[TAM_NOME];
  int achou = 0;
  printf("3 - Atualizar Aluno\n");
  printf("Informe o nome:\n");
  scanf("%s", nome);
  if (strcmp(nome, " ")) {
    return MATRICULA_ALUNO_INVALIDA;
  } else {
    for (int i = 0; i < qtdAlunos; i++) {
      if (!strcmp(listaAlunos[i].nome, nome) && listaAlunos[i].ativo) {
        char nomeAtualizado[TAM_NOME];
        char sexoAtualizado;
        char dataNascAtualizada[TAM_DATA_NASCIMENTO];
        char cpfAtualizado[TAM_CPF];
        printf("Informe o novo nome:\n");
        scanf("%s", nomeAtualizado);
        printf("Informe o sexo:\n");
        scanf("%s", &sexoAtualizado);
        printf("Informe a data de nascimento:\n");
        scanf("%s", dataNascAtualizada);
        printf("Informe o cpf:\n");
        scanf("%s", cpfAtualizado);
        strcpy(listaAlunos[qtdAlunos].nome, nomeAtualizado);
        strcpy(&listaAlunos[qtdAlunos].sexo, &sexoAtualizado);
        strcpy(listaAlunos[qtdAlunos].dataNascimento, dataNascAtualizada);
        strcpy(listaAlunos[qtdAlunos].cpf, cpfAtualizado);
        achou = 1;
        break;
      }
    }
    if (achou)
      return ATUALIZACAO_ALUNO_SUCESSO;
    else
      return MATRICULA_ALUNO_INEXISTE;
  }
}

int excluirAluno(Aluno listaAlunos[], int qtdAlunos) {
  printf("4 - Excluir Aluno\n");
  printf("Informe o nome:\n");
  char nome[TAM_NOME];
  int achou = 0;
  scanf("%s", nome);
  if (strcmp(nome, " ")) {
    return MATRICULA_ALUNO_INVALIDA;
  } else {
    for (int i = 0; i < qtdAlunos; i++) {
      if (!strcmp(listaAlunos[i].nome, nome) && listaAlunos[i].ativo) {
        listaAlunos[i].ativo = 0;
        for (int j = i; j < qtdAlunos - 1; j++) {
          strcpy(listaAlunos[j].nome, listaAlunos[j+1].nome);
          listaAlunos[j].matricula = listaAlunos[j + 1].matricula;
          listaAlunos[j].sexo = listaAlunos[j + 1].sexo;
          strcpy(listaAlunos[j].dataNascimento, listaAlunos[j+1].dataNascimento);
          strcpy(listaAlunos[j].cpf, listaAlunos[j+1].cpf);
          listaAlunos[j].ativo = listaAlunos[j + 1].ativo;
        }

        achou = 1;
        break;
      }
    }
    if (achou)
      return EXCLUIR_ALUNO_SUCESSO;
    else
      return MATRICULA_ALUNO_INEXISTE;
  }
}