#include <stdio.h> 
#define TAM_ALUNO 3

int main(void){

  int listaAlunos[TAM_ALUNO];
  int qtdAlunos = 0;
  int menu;
  int sair = 0;

  while(!sair){
  
    printf("Projeto Escola\n");
    printf("0 - Sair\n");
    printf("1 - Aluno\n");
    printf("2 - Professor\n");
    printf("3 - Disciplina\n");
  
    scanf("%d", &menu);

    switch(menu){
      case 0:{
        sair = 1;
        break;
      }
      case 1:{
        printf("Módulo Aluno\n");
        int menuAluno;
        int sairAluno = 0;

        while(!sair){
          printf("0 - Voltar\n");
          printf("1 - Cadastrar Aluno\n");
          printf("2 - Listar Aluno\n");
          printf("3 - Atualizar Aluno\n");
          printf("4 - Excluir Aluno\n");
  
          scanf("%d", &menuAluno);

          switch(menuAluno){
            case 0:{
              sairAluno = 1;
              break;
            }
            case 1:{
              printf("1 - Cadastrar Aluno\n");
              printf("Informe a matricula:\n");
              int matricula;
              scanf("%d", &matricula);
              if(matricula > 0){
                printf("Matricula Inválida\n");  
              } else {
                if(qtdAlunos == TAM_ALUNO){
                  printf("Lista de alunos cheia\n");  
                }else{
                  listaAlunos[qtdAlunos] = matricula;
                  qtdAlunos++;
                }
              }
              break;
            }
            
            case 2:{
              printf("2 - Listar Aluno\n");
              break;
            }
            case 3:{
              printf("3 - Atualizar Aluno\n");
              break;
            }
            case 4:{
              printf("4 - Excluir Aluno\n");
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