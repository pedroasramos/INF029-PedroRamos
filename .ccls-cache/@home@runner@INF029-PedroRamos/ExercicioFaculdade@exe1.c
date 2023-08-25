#include <stdio.h>

int main(void) {
  int num[3];
  int cont, flag;
  int flag2 = 0;
  for(int g = 0; g < 3; g++){
    scanf("%d", &num[g]);
  }
  scanf("%d", &cont);
  // for(int i = 0; i < 50; i++){
  //   if(num[i] > num[i+1]){
  //     flag = num[i];
  //     num[i] = num[i+1];
  //     num[i+1] = flag;      
  //   }
  // }
  for(int j = 0; j < 3; j++){
    if( cont == num[j]){
      flag2 = 1;
    }
    if(flag){
      printf("Achei");
    }else{
      printf("Não achei");
    }
  }
}