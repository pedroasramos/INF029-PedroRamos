#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_RANGE 100000

typedef struct lista{
   int **vetor;
   int x;
   int y;
   int *soma;
   int *contY;
}Lista;

void normalize_line(char *line) {
   for (char *ptr = line; *ptr; ptr++) {
      if (*ptr == '\xE2' && *(ptr + 1) == '\x88' && *(ptr + 2) == '\x92') {
         *ptr = '-';
         memmove(ptr + 1, ptr + 3, strlen(ptr + 3) + 1);
      }
   }
}

void ordena_X(int **vetor, int *contY, int soma[],  int x){
  for(int i = 1; i <= x; i++){
    int chave_soma = soma[i];
    int *chave_vetor = vetor[i];
    int chave_contY = contY[i];
    int j = i - 1;

    while(j >= 0 && soma[j] > chave_soma){
      soma[j + 1] = soma[j];
      vetor[j + 1] = vetor[j];
      contY[j + 1] = contY[j];
      j--;
    }
    soma[j + 1] = chave_soma;
    vetor[j + 1] = chave_vetor;
    contY[j + 1] = chave_contY;
  }
}

void ordena_Y(int **vetorY, int tamX, int *tamY){
   for(int k = 1; k <= tamX; k++){
      for(int i = 1; i < tamY[k]; i++){
         int j = i - 1;
         int chave = vetorY[k][i];
         while(j >= 0 && vetorY[k][j] > chave){
            vetorY[k][j + 1] = vetorY[k][j];
            j--;
         }
         vetorY[k][j + 1] = chave;
      }
   }
}

int main() {
   FILE *fp_in = fopen("L1Q1.in", "r");
   FILE *fp_out = fopen("L1Q1.out", "w");
   if(!fp_in || !fp_out){
      printf("Erro ao abrir o arquivo!");
      return EXIT_FAILURE;
   }
   
   Lista *lista = malloc(sizeof(Lista));
   lista->vetor = malloc(MAX_RANGE * sizeof(int *));
   lista->contY = malloc(MAX_RANGE * sizeof(int));
   lista->soma = malloc(MAX_RANGE * sizeof(int));
   for(int i =0; i<MAX_RANGE; i++){
      lista->vetor[i] = malloc(MAX_RANGE * sizeof(int));
      lista->contY[i] = 0;
      lista->soma[i] = 0;
   }
   
   char linha[MAX_RANGE];
   char *valor_externo;
   char *valor_interno;
   char delimitador_externo[] = "start";
   char delimitador_interno[] = " ";
   char *contexto_externo = NULL;
   char *contexto_interno = NULL;

   while(fgets(linha, sizeof(linha), fp_in) != NULL){
      valor_externo = strtok_r(linha, delimitador_externo, &contexto_externo);
      lista->x = 0;
      
      while(valor_externo != NULL){

         valor_interno = strtok_r(valor_externo, delimitador_interno, &contexto_interno);
         lista->x++;
         lista->y = 0;
         
         while(valor_interno != NULL){
               
            normalize_line(valor_interno);
            if(isdigit(*valor_interno) || (*valor_interno == '-' && isdigit(*(valor_interno+1)))){
               int numero;
               sscanf(valor_interno, "%d", &numero);
               lista->vetor[lista->x][lista->y] = numero;
               lista->y++;
               while(*valor_interno && (isdigit(*valor_interno) || *valor_interno == '-')){
                  valor_interno++;
               }
            }
            else{
               valor_interno++;
            }
            
            valor_interno = strtok_r(NULL, delimitador_interno, &contexto_interno);
         }
         lista->contY[lista->x] = lista->y;
         
         valor_externo = strtok_r(NULL, delimitador_externo, &contexto_externo);
      }
      for(int i = 1; i <= lista->x; i++){
         lista->soma[i] = 0;
         int cont = 0;
         while(cont < lista->contY[i]){
            lista->soma[i] += lista->vetor[i][cont];
            cont++;
         }
      }

      ordena_Y(lista->vetor, lista->x, lista->contY);
      ordena_X(lista->vetor, lista->contY, lista->soma, lista->x);
      
      for (int i = 1; i <= lista->x; i++) {
         fprintf(fp_out, "start ");
         for (int j = 0; j < lista->contY[i]; j++) {
            fprintf(fp_out, "%d ", lista->vetor[i][j]);
         }
         // fprintf(fp_out, "Soma = %d ",lista->soma[i]);
      }
      fprintf(fp_out,"\n");
   }

   for (int i = 0; i < MAX_RANGE; i++) {
      free(lista->vetor[i]);
   }
   free(lista->vetor);
   free(lista->contY);
   free(lista->soma);
   free(lista);
   fclose(fp_in);
   fclose(fp_out);
   
   return EXIT_SUCCESS;
}
