#include <stdio.h> 
#define TAM_ALUNO 3
#define CAD_ALUNO_SUCESSO -1
#define MATRICULA_INVALIDA -2
#define LISTA_CHEIA -3
#define ATUALIZACAO_ALUNO_SUCESSO -4
#define MATRICULA_INEXISTE -5
#define EXCLUIR_ALUNO_SUCESSO -6

typedef struct alu{
int matricula;
char sexo;
int ativo;
}Aluno;

int menuGeral();
int menuAluno();
int cadastrarAluno(Aluno listaAlunos[], int qtdAlunos);
void listarAluno(Aluno listaAlunos[], int qtdAlunos);
int atualizarAluno(Aluno listaAlunos[], int qtdAlunos);
int excluirAluno(Aluno listaAlunos[], int qtdAlunos);



int main(void){

  Aluno listaAlunos[TAM_ALUNO];
  int qtdAlunos = 0;
  int opcaoGeral;
  int sair = 0;

  while(!sair){
    opcaoGeral = menuGeral();
    switch(opcaoGeral){
      case 0:{
        sair = 1;
        break;
      }
      case 1:{
        printf("Módulo Aluno\n");
        int opcaoAluno;
        int sairAluno = 0;

        while(!sairAluno){
          opcaoAluno = menuAluno();
          switch(opcaoAluno){
            case 0:{
              sairAluno = 1;
              break;
            }
            case 1:{
              int retorno = cadastrarAluno(listaAlunos, qtdAlunos);
              if(retorno == LISTA_CHEIA)
                printf("Lista de alunos cheia\n"); 
              else if(retorno == MATRICULA_INVALIDA)
                printf("Matricula Inválida\n");
              else
                printf("Cadastrado com sucesso!\n");
                qtdAlunos++;
             
              break;
            }
            
            case 2:{
              listarAluno(listaAlunos, qtdAlunos);
              break;
            }
            
            case 3:{
              int retorno = atualizarAluno(listaAlunos, qtdAlunos);
              switch (retorno){
                case MATRICULA_INVALIDA:{
                  printf("Matricula Inválida\n");
                  break;
                }
                case ATUALIZACAO_ALUNO_SUCESSO:{
                  printf("Aluno atualizado com sucesso\n");
                  break;
                }
                case MATRICULA_INEXISTE:{
                  printf("Matricula inexiste\n");
                  break;
                }
              }
              break;
            }
            case 4:{
              int retorno = excluirAluno(listaAlunos, qtdAlunos);
              switch (retorno){
                case MATRICULA_INVALIDA:{
                  printf("Matricula Inválida\n"); 
                  break;
                }
                case EXCLUIR_ALUNO_SUCESSO:{
                  printf("Aluno excluído com sucesso\n");
                  qtdAlunos--;
                  break;
                }
                case MATRICULA_INEXISTE:{
                  printf("Matrícula inexistente\n");
                  break;
                }
              }
              break;
            }
            default:{
              printf("Opção Inválida\n");
            } 
            
          }
      }
        
        break;
      }
      case 2:{
        printf("Módulo Professor\n");
        break;
      }
      case 3:{
        printf("Módulo Disciplina\n");
        break;
      }
      default:{
        printf("Opção inválida!\n");
      }
    }
    
  }
  
}

int menuGeral(){
  int menu;
  printf("Projeto Escola\n");
  printf("0 - Sair\n");
  printf("1 - Aluno\n");
  printf("2 - Professor\n");
  printf("3 - Disciplina\n");

  scanf("%d", &menu);

  return menu;
}

int menuAluno(){
  int menu;
  printf("0 - Voltar\n");
  printf("1 - Cadastrar Aluno\n");
  printf("2 - Listar Aluno\n");
  printf("3 - Atualizar Aluno\n");
  printf("4 - Excluir Aluno\n");

  scanf("%d", &menu);

  return menu;
}

int cadastrarAluno(Aluno listaAlunos[], int qtdAlunos){
  printf("1 - Cadastrar Aluno\n");
  if(qtdAlunos == TAM_ALUNO){
      return LISTA_CHEIA; 
    }else{
      printf("Informe a matricula:\n");
      int matricula;
      scanf("%d", &matricula);
      if(matricula < 0){
        return MATRICULA_INVALIDA;  
      } 
      else{
      listaAlunos[qtdAlunos].matricula = matricula;
      listaAlunos[qtdAlunos].ativo = 1;
        
      return CAD_ALUNO_SUCESSO;  
        
                       
      }
    }
}

void listarAluno(Aluno listaAlunos[], int qtdAlunos){
  printf("2 - Listar Aluno\n");
  if (qtdAlunos == 0){
    printf("Lista de alunos vazia\n");
  }else{
    for (int i = 0; i < qtdAlunos; i++){
      if(listaAlunos[i].ativo)
        printf("Matrícula: %d\n", listaAlunos[i].matricula);
    }
  }
}

int atualizarAluno(Aluno listaAlunos[], int qtdAlunos){
  printf("3 - Atualizar Aluno\n");
  printf("Informe a matricula:\n");
  int matricula;
  int achou = 0;
  scanf("%d", &matricula);
  if(matricula < 0){
    return MATRICULA_INVALIDA;  
  }else{
    for (int i = 0; i < qtdAlunos; i++){
      if(matricula == listaAlunos[i].matricula && listaAlunos[i].ativo){
        printf("Informe a nova matricula:\n");
        int novaMatricula;
        scanf("%d", &novaMatricula);
        listaAlunos[i].matricula = novaMatricula;
        achou = 1;
        break;
      }
    }
    if(achou)
      return ATUALIZACAO_ALUNO_SUCESSO;
    else
      return MATRICULA_INEXISTE;
  }
}

int excluirAluno(Aluno listaAlunos[], int qtdAlunos){
  printf("4 - Excluir Aluno\n");
  printf("Informe a matricula:\n");
  int matricula;
  int achou = 0;
  scanf("%d", &matricula);
  if(matricula < 0){
    return MATRICULA_INVALIDA;
  }else{
    for (int i = 0; i < qtdAlunos; i++){
      if(matricula == listaAlunos[i].matricula){
        listaAlunos[i].ativo = 0;
        for(int j = i; j < qtdAlunos -1; j++){
          listaAlunos[j].matricula = listaAlunos[j+1].matricula;
          listaAlunos[j].sexo = listaAlunos[j+1].sexo;
          listaAlunos[j].ativo = listaAlunos[j+1].ativo;
        }
        
        achou = 1;
        break;
      }
    }
    if(achou)
      return EXCLUIR_ALUNO_SUCESSO;
    else
      return MATRICULA_INEXISTE;
  }
}