#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void preencher_lista(long *lista, int tamanho, int maximo) {
  for (int i = 0; i < tamanho; i++) {
    lista[i] = rand() % (maximo + 1);
  }
}

int main(int argc, char *argv[]) {
  long quantidade, numeroMaximo, tipoArquivo;
  char nomeArquivo[100];

  quantidade = atol(argv[1]);

  numeroMaximo = atol(argv[2]);

  strcpy(nomeArquivo, argv[3]);

  // faz os arquivos de teste com numeros aleatorios
  FILE *file = fopen(nomeArquivo, "w");
  if (file == NULL) {
    printf("Erro escrevendo o arquivo!\n");
    return 1;
  }

  srand(time(NULL));
  long lista[quantidade];
  preencher_lista(lista, quantidade, numeroMaximo);

  for (long i = 0; i < quantidade; i++) {
    if (i == 0) {
      printf("%ld, \n", lista[i]);
    }
    fprintf(file, "%ld\n", lista[i]);
  }

  fclose(file);
  return 0;
}
