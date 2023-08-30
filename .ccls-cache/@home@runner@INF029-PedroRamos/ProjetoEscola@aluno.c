#include "escola.c"

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