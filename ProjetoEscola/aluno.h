#ifndef ALUNO_H
#define ALUNO_H
#include "geral.h"

#define TAM_ALUNO 3


#define CAD_ALUNO_SUCESSO -1
#define MATRICULA_ALUNO_INVALIDA -2
#define LISTA_ALUNO_CHEIA -3
#define ATUALIZACAO_ALUNO_SUCESSO -4
#define MATRICULA_ALUNO_INEXISTE -5
#define EXCLUIR_ALUNO_SUCESSO -6

typedef struct alu {  
  int matricula;
  char nome[TAM_NOME];
  char sexo;
  char dataNascimento[TAM_DATA_NASCIMENTO];
  char cpf[TAM_CPF];
  int ativo;
} Aluno;

int menuAluno();
int cadastrarAluno(Aluno listaAlunos[], int *qtdAlunos, int *matriAlunos);
void listarAlunos(Aluno listaAlunos[], int *qtdAlunos);
int atualizarAluno(Aluno listaAlunos[], int qtdAlunos);
int excluirAluno(Aluno listaAlunos[], int qtdAlunos);

#endif