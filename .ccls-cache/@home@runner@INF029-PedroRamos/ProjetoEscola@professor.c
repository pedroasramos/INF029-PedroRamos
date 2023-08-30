#include "escola.c"

int menuProfessor(){
  int menu;
  printf("0 - Voltar\n");
  printf("1 - Cadastrar Professor\n");
  printf("2 - Listar Professor\n");
  printf("3 - Atualizar Professor\n");
  printf("4 - Excluir Professor\n");

  scanf("%d", &menu);

  return menu;
}