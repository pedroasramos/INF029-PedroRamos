#include <stdio.h>

int main(void) {
  int num[8];
  int cont, flag;
  int flag2 = 0;
  num[0] = 7;
  num[1] = 1;
  num[2] = 3;
  num[3] = 2;
  num[4] = 5;
  num[5] = 8;
  num[6] = 4;
  num[7] = 6;

  for (int i = 0; i < 8; i++){
    for (int j = 1; j < i + 1; j++){
      if(num[j] > num[i]){
        cont = num[j];
        num[j] = num[i];
        num[i] = cont;
      }
    }
  }
  for (int i = 0; i < 8; i++){
    printf("%d", num[i]);
  }
}