#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"
#include "professor.h"
#include "disciplina.h"
#include "geral.h"

int main(void) {
  Aluno listaAlunos[TAM_ALUNO];
  int qtdAlunos = 0;
  int matriAlunos = 0;

  Professor listaProfessores[TAM_PROFESSOR];
  int qtdProfessores = 0;

  Disciplina listaDisciplinas[TAM_DISCIPLINA];
  int qtdDisciplinas = 0;

  int opcaoGeral;
  int sair = 0;

  while (!sair) {
    opcaoGeral = menuGeral();
    switch (opcaoGeral) {
    case 0: {
      sair = 1;
      break;
    }
    case 1: {
      printf("Módulo Aluno\n");
      int opcaoAluno;
      int sairAluno = 0;

      while (!sairAluno) {
        opcaoAluno = menuAluno();
        switch (opcaoAluno) {
        case 0: {
          sairAluno = 1;
          break;
        }
        case 1: {
          int retorno = cadastrarAluno(listaAlunos, &qtdAlunos, &matriAlunos);
          if (retorno == LISTA_ALUNO_CHEIA)
            printf("Lista de alunos cheia\n");
          else if (retorno == MATRICULA_ALUNO_INVALIDA)
            printf("Nome aluno Inválido\n");
          else{
            printf("Cadastrado com sucesso!\n");
            qtdAlunos++;
          }
          break;
        }

        case 2: {
          listarAlunos(listaAlunos, &qtdAlunos);
          break;
        }

        case 3: {
          int retorno = atualizarAluno(listaAlunos, qtdAlunos);
          switch (retorno) {
          case MATRICULA_ALUNO_INVALIDA: {
            printf("Matricula Inválida\n");
            break;
          }
          case ATUALIZACAO_ALUNO_SUCESSO: {
            printf("Aluno atualizado com sucesso\n");
            break;
          }
          case MATRICULA_ALUNO_INEXISTE: {
            printf("Matricula inexiste\n");
            break;
          }
          }
          break;
        }
        case 4: {
          int retorno = excluirAluno(listaAlunos, qtdAlunos);
          switch (retorno) {
          case MATRICULA_ALUNO_INVALIDA: {
            printf("Matricula Inválida\n");
            break;
          }
          case EXCLUIR_ALUNO_SUCESSO: {
            printf("Aluno excluído com sucesso\n");
            qtdAlunos--;
            break;
          }
          case MATRICULA_ALUNO_INEXISTE: {
            printf("Matrícula inexistente\n");
            break;
          }
          }
          break;
        }
        default: {
          printf("Opção Inválida\n");
        }
        }
      }

      break;
    }
    case 2: {
      printf("Módulo Professor\n");
      int opcaoProfessor;
      int sairProfessor = 0;

      while (!sairProfessor) {
        opcaoProfessor = menuProfessor();
        switch (opcaoProfessor) {
        case 0: {
          sairProfessor = 1;
          break;
        }
        case 1: {
          int retorno = cadastrarProfessor(listaProfessores, qtdProfessores);
          switch (retorno) {
            case LISTA_PROFESSOR_CHEIA: {
              printf("Lista de professores cheia\n");
              break;
            }
            case MATRICULA_PROFESSOR_INVALIDA: {
              printf("Matricula Inválida\n");
              break;
            }
            case CAD_PROFESSOR_SUCESSO: {
              printf("Cadastrado com sucesso!\n");
              qtdProfessores++;
              break;
            }
          }
          break;
        }
        case 2: {
          listarProfessor(listaProfessores, qtdProfessores);
          break;
        }
        case 3: {
          int retorno = atualizarProfessor(listaProfessores, qtdProfessores);
          switch (retorno) {
          case MATRICULA_PROFESSOR_INVALIDA: {
            printf("Matricula Inválida\n");
            break;
          }
          case ATUALIZACAO_PROFESSOR_SUCESSO: {
            printf("Professor atualizado com sucesso\n");
            break;
          }
          case MATRICULA_PROFESSOR_INEXISTE: {
            printf("Matricula inexiste\n");
            break;
          }
          }
        }
        case 4: {
          int retorno = excluirProfessor(listaProfessores, qtdProfessores);
          switch (retorno) {
          case MATRICULA_PROFESSOR_INVALIDA: {
            printf("Matricula Inválida\n");
            break;
          }
          case EXCLUIR_PROFESSOR_SUCESSO: {
            printf("Professor excluído com sucesso\n");
            qtdProfessores--;
            break;
          }
          case MATRICULA_PROFESSOR_INEXISTE: {
            printf("Matrícula inexistente\n");
            break;
          }
          }
          break;
        }
        }
      }

      break;
    }
    case 3: {
      printf("Módulo Disciplina\n");
      int opcaoDisciplina;
      int sairDisciplina = 0;
      
      while (!sairDisciplina) {
      	opcaoDisciplina = menuDisciplina();
        switch (opcaoDisciplina) {
          case 0: {
            sairDisciplina = 1;
            break;
          }
          case 1: {
            // int codDisciplina = 100;
            int retorno = cadastrarDisciplina(listaDisciplinas, qtdDisciplinas);
            switch (retorno) {
              case LISTA_DISCIPLINA_CHEIA: {
                printf("Lista de disciplinas cheia\n");
                break;
              }
              case DISCIPLINA_INVALIDA: {
                printf("Disciplina Inválida\n");
                break;
              }
              case CAD_DISCIPLINA_SUCESSO: {
                printf("Cadastrada com sucesso!\n");
                qtdDisciplinas++;
                break;
              }          
            }
            break;
          }
          case 2: {
            listarDisciplina(listaDisciplinas, qtdDisciplinas);
            break;
          }
          case 3: {
            int retorno = atualizarDisciplina(listaDisciplinas, qtdDisciplinas);
            switch(retorno){
              case DISCIPLINA_INVALIDA:{
                printf("Disciplina inválida\n");
                break;
              }
              case ATUALIZACAO_DISCIPLINA_SUCESSO:{
                printf("Disciplina atualizada com sucesso\n");
                break;
              }
              case DISCIPLINA_INEXISTE:{
                printf("Disciplina inexistente\n");
                break;
              }
            }
            break;
          }
          case 4:{
            int retorno = excluirDisciplina(listaDisciplinas, qtdDisciplinas);
            switch(retorno){
              case DISCIPLINA_INVALIDA:{
                printf("Disciplina Inválida\n");
                break;
              }
              case EXCLUIR_DISCIPLINA_SUCESSO:{
                printf("Disciplina excluida com sucesso\n");
                qtdDisciplinas--;
                break;
              }
              case DISCIPLINA_INEXISTE:{
                printf("Disciplina inexistente\n");
                break;
              }
            }
          }
        }
      }
      break;
    }
    default: {
      printf("Opção inválida!\n");
    }
    }
  }
}