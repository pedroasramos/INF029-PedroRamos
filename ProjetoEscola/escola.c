#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_ALUNO 3
#define CAD_ALUNO_SUCESSO -1
#define MATRICULA_ALUNO_INVALIDA -2
#define LISTA_ALUNO_CHEIA -3
#define ATUALIZACAO_ALUNO_SUCESSO -4
#define MATRICULA_ALUNO_INEXISTE -5
#define EXCLUIR_ALUNO_SUCESSO -6

#define TAM_PROFESSOR 3
#define CAD_PROFESSOR_SUCESSO -7
#define EXCLUIR_PROFESSOR_SUCESSO -8
#define ATUALIZACAO_PROFESSOR_SUCESSO -9
#define LISTA_PROFESSOR_CHEIA -15
#define MATRICULA_PROFESSOR_INVALIDA -17
#define MATRICULA_PROFESSOR_INEXISTE -18

#define TAM_DISCIPLINA 3
#define TAM_NOME_DISCIPLINA 20
#define CAD_DISCIPLINA_SUCESSO -10
#define DISCIPLINA_INVALIDA -11
#define ATUALIZACAO_DISCIPLINA_SUCESSO -12
#define DISCIPLINA_INEXISTE -13
#define EXCLUIR_DISCIPLINA_SUCESSO -14
#define LISTA_DISCIPLINA_CHEIA -16

typedef struct alu {
  int matricula;
  char sexo;
  int ativo;
} Aluno;

typedef struct pro {
  int matricula;
  char sexo;
  int ativo;
} Professor;

typedef struct dis {
  char nome[TAM_NOME_DISCIPLINA];
  int codigo;
  int ativo;
} Disciplina;

int menuGeral();
int menuAluno();
int cadastrarAluno(Aluno listaAlunos[], int qtdAlunos);
void listarAluno(Aluno listaAlunos[], int qtdAlunos);
int atualizarAluno(Aluno listaAlunos[], int qtdAlunos);
int excluirAluno(Aluno listaAlunos[], int qtdAlunos);

int menuProfessor();
int cadastrarProfessor(Professor listaProfessores[], int qtdProfessores);
void listarProfessor(Professor listaProfessores[], int qtdProfessores);
int atualizarProfessor(Professor listaProfessores[], int qtdProfessores);
int excluirProfessor(Professor listaProfessores[], int qtdProfessores);

int menuDisciplina();
int cadastrarDisciplina(Disciplina listaDisciplinas[], int qtdDisciplinas);
void listarDisciplina(Disciplina listaDisciplinas[], int qtdDisciplinas);
int atualizarDisciplina(Disciplina listaDisciplinas[], int qtdDisciplinas);
int excluirDisciplina(Disciplina listaDisciplinas[], int qtdDisciplinas);

int main(void) {

  Aluno listaAlunos[TAM_ALUNO];
  int qtdAlunos = 0;

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
          int retorno = cadastrarAluno(listaAlunos, qtdAlunos);
          if (retorno == LISTA_ALUNO_CHEIA)
            printf("Lista de alunos cheia\n");
          else if (retorno == MATRICULA_ALUNO_INVALIDA)
            printf("Matricula Inválida\n");
          else
            printf("Cadastrado com sucesso!\n");
          qtdAlunos++;

          break;
        }

        case 2: {
          listarAluno(listaAlunos, qtdAlunos);
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
      opcaoDisciplina = menuDisciplina();
      while (!sairDisciplina) {
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
            printf("Cadaaaaaaaastrada com sucesso!\n");
            qtdDisciplinas++;
            break;
          }
          default: {
            printf("Erroooooo");
          }
          }
          break;
        }
        case 2: {
          listarDisciplina(listaDisciplinas, qtdDisciplinas);
          break;
        }
        case 3: {
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

int menuGeral() {
  int menu;
  printf("Projeto Escola\n");
  printf("0 - Sair\n");
  printf("1 - Aluno\n");
  printf("2 - Professor\n");
  printf("3 - Disciplina\n");

  scanf("%d", &menu);

  return menu;
}

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
    printf("Informe a matricula:\n");
    int matricula;
    scanf("%d", &matricula);
    if (matricula < 0) {
      return MATRICULA_ALUNO_INVALIDA;
    } else {
      listaAlunos[qtdAlunos].matricula = matricula;
      listaAlunos[qtdAlunos].ativo = 1;

      return CAD_ALUNO_SUCESSO;
    }
  }
}

void listarAluno(Aluno listaAlunos[], int qtdAlunos) {
  printf("2 - Listar Aluno\n");
  if (qtdAlunos == 0) {
    printf("Lista de alunos vazia\n");
  } else {
    for (int i = 0; i < qtdAlunos; i++) {
      if (listaAlunos[i].ativo)
        printf("Matrícula: %d\n", listaAlunos[i].matricula);
    }
  }
}

int atualizarAluno(Aluno listaAlunos[], int qtdAlunos) {
  printf("3 - Atualizar Aluno\n");
  printf("Informe a matricula:\n");
  int matricula;
  int achou = 0;
  scanf("%d", &matricula);
  if (matricula < 0) {
    return MATRICULA_ALUNO_INVALIDA;
  } else {
    for (int i = 0; i < qtdAlunos; i++) {
      if (matricula == listaAlunos[i].matricula && listaAlunos[i].ativo) {
        printf("Informe a nova matricula:\n");
        int novaMatricula;
        scanf("%d", &novaMatricula);
        listaAlunos[i].matricula = novaMatricula;
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
  printf("Informe a matricula:\n");
  int matricula;
  int achou = 0;
  scanf("%d", &matricula);
  if (matricula < 0) {
    return MATRICULA_ALUNO_INVALIDA;
  } else {
    for (int i = 0; i < qtdAlunos; i++) {
      if (matricula == listaAlunos[i].matricula) {
        listaAlunos[i].ativo = 0;
        for (int j = i; j < qtdAlunos - 1; j++) {
          listaAlunos[j].matricula = listaAlunos[j + 1].matricula;
          listaAlunos[j].sexo = listaAlunos[j + 1].sexo;
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
    printf("Informe a matricula:\n");
    int matricula;
    scanf("%d", &matricula);
    if (matricula < 0) {
      return MATRICULA_PROFESSOR_INVALIDA;
    } else {
      listaProfessores[qtdProfessores].matricula = matricula;
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
        printf("Matrícula: %d\n", listaProfessores[i].matricula);
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
// FAZER TUDO BASEADO NO CODIGO DA DISCIPLINA CADAS LIS ATUA EXCL
// ==============================================================
int cadastrarDisciplina(Disciplina listaDisciplinas[], int qtdDisciplinas) {
  printf("1 - Cadastrar Disciplina\n");
  if (qtdDisciplinas == TAM_DISCIPLINA) {
    return LISTA_DISCIPLINA_CHEIA;
  } else {
    printf("Informe a disciplina:\n");
    char nomeDisciplina[TAM_NOME_DISCIPLINA];
    // fgets(nomeDisciplina, 20, stdin);
    scanf("%s", nomeDisciplina);
    if(strcmp(nomeDisciplina, " ") == 0){
      return DISCIPLINA_INVALIDA;
    }

    else{
      strcpy(nomeDisciplina, listaDisciplinas[qtdDisciplinas].nome);
      listaDisciplinas[qtdDisciplinas].ativo = 1;
    
      // codDisciplina++;
      // listaDisciplinas[qtdDisciplinas].codigo = codDisciplina;

      return CAD_DISCIPLINA_SUCESSO;
    }
  }
}

void listarDisciplina(Disciplina listaDisciplinas[], int qtdDisciplinas) {
  printf("Listar Disciplinas");
  if (qtdDisciplinas == 0) {
    printf("Lista vazia");
  } else {
    for (int i = 0; i < qtdDisciplinas; i++) {
      if (listaDisciplinas[i].ativo == 1) {
        printf("Disciplina: %d\n", listaDisciplinas[i].codigo);
        printf("Disciplina: %d\n", listaDisciplinas[i].nome);
      }
    }
  }
}

int atualizarDisciplina(Disciplina listaDisciplinas[], int qtdDisciplinas) {
  printf("3 - Atualizar Disciplina\n");
  printf("Informe o nome da disciplina:\n");
  int discipli;
  int achou = 0;
  scanf("%d", &discipli);
  if (discipli < 0) {
    return DISCIPLINA_INVALIDA;
  } else {
    for (int i = 0; i < qtdDisciplinas; i++) {
      if (discipli == listaDisciplinas[i].nome && listaDisciplinas[i].ativo) {
        printf("Informe o novo nome da disciplina:\n");
        int novoNomeDisciplina;
        scanf("%d", &novoNomeDisciplina);
        // listaDisciplinas[i].nome = novoNomeDisciplina;
        achou = 1;
        break;
      } else {
        printf("Disciplina não localizada");
        break;
      }
    }
  }
}
  // int excluirDisciplina(Disciplina listaDisciplinas[], int qtdDisciplinas){}

