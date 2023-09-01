#include <stdio.h>
#include "geral.h"

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