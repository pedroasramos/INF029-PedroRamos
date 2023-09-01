#include "geral.h"
#define TAM_PROFESSOR 3
#define CAD_PROFESSOR_SUCESSO -7
#define EXCLUIR_PROFESSOR_SUCESSO -8
#define ATUALIZACAO_PROFESSOR_SUCESSO -9
#define LISTA_PROFESSOR_CHEIA -15
#define MATRICULA_PROFESSOR_INVALIDA -17
#define MATRICULA_PROFESSOR_INEXISTE -18

typedef struct pro {
  int matricula;
  char nome[TAM_NOME];
  char sexo;
  char dataNascimento[TAM_DATA_NASCIMENTO];
  char cpf[TAM_CPF];
  int ativo;
} Professor;

int menuProfessor();
int cadastrarProfessor(Professor listaProfessores[], int qtdProfessores);
void listarProfessor(Professor listaProfessores[], int qtdProfessores);
int atualizarProfessor(Professor listaProfessores[], int qtdProfessores);
int excluirProfessor(Professor listaProfessores[], int qtdProfessores);