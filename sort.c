#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void merge(long vetor[], long esquerda, long meio, long direita) {
  long i, j, k;
  long tamanho1 = meio - esquerda + 1;
  long tamanho2 = direita - meio;

  long vetorEsquerda[tamanho1], vetorDireita[tamanho2];

  for (i = 0; i < tamanho1; i++)
    vetorEsquerda[i] = vetor[esquerda + i];
  for (j = 0; j < tamanho2; j++)
    vetorDireita[j] = vetor[meio + 1 + j];

  i = 0;
  j = 0;
  k = esquerda;

  while (i < tamanho1 && j < tamanho2) {
    if (vetorEsquerda[i] <= vetorDireita[j]) {
      vetor[k] = vetorEsquerda[i];
      i++;
    } else {
      vetor[k] = vetorDireita[j];
      j++;
    }
    k++;
  }

  while (i < tamanho1) {
    vetor[k] = vetorEsquerda[i];
    i++;
    k++;
  }
  while (j < tamanho2) {
    vetor[k] = vetorDireita[j];
    j++;
    k++;
  }
}

void mergeSort(long vetor[], long esquerda, long direita) {
  if (esquerda < direita) {
    long meio = esquerda + (direita - esquerda) / 2;
    mergeSort(vetor, esquerda, meio);
    mergeSort(vetor, meio + 1, direita);
    merge(vetor, esquerda, meio, direita);
  }
}

void insertionSort(long vetor[], long tamanho) {
  long i, chave, j;

  for (i = 1; i < tamanho; i++) {
    chave = vetor[i];
    j = i - 1;

    while (j >= 0 && vetor[j] > chave) {
      vetor[j + 1] = vetor[j];
      j = j - 1;
    }
    vetor[j + 1] = chave;
  }
}

void bubbleSort(long vetor[], long tamanho) {
  long i, j, temp;
  for (i = 0; i < tamanho - 1; i++) {
    for (j = 0; j < tamanho - i - 1; j++) {
      if (vetor[j] > vetor[j + 1]) {
        temp = vetor[j];
        vetor[j] = vetor[j + 1];
        vetor[j + 1] = temp;
      }
    }
  }
}

void trocar(long *a, long *b) {
  long temp = *a;
  *a = *b;
  *b = temp;
}

long particionarFixo(long vetor[], long inicio, long fim) {
  long pivo = vetor[fim];
  long i = (inicio - 1);

  for (long j = inicio; j <= fim - 1; j++) {
    if (vetor[j] <= pivo) {
      i++;
      trocar(&vetor[i], &vetor[j]);
    }
  }
  trocar(&vetor[i + 1], &vetor[fim]);
  return (i + 1);
}

void quickSortFixo(long vetor[], long inicio, long fim) {
  if (inicio < fim) {
    long indicePivo = particionarFixo(vetor, inicio, fim);
    quickSortFixo(vetor, inicio, indicePivo - 1);
    quickSortFixo(vetor, indicePivo + 1, fim);
  }
}

long particionarAleatorio(long vetor[], long inicio, long fim) {
  srand(time(NULL));
  long indiceAleatorio = inicio + rand() % (fim - inicio + 1);
  trocar(&vetor[indiceAleatorio], &vetor[fim]);

  long pivo = vetor[fim];
  long i = (inicio - 1);

  for (long j = inicio; j <= fim - 1; j++) {
    if (vetor[j] <= pivo) {
      i++;
      trocar(&vetor[i], &vetor[j]);
    }
  }
  trocar(&vetor[i + 1], &vetor[fim]);
  return (i + 1);
}

void quickSortAleatorio(long vetor[], long inicio, long fim) {
  if (inicio < fim) {
    long indicePivo = particionarAleatorio(vetor, inicio, fim);
    quickSortAleatorio(vetor, inicio, indicePivo - 1);
    quickSortAleatorio(vetor, indicePivo + 1, fim);
  }
}

void countSort(long vetor[], long tamanho) {
  long max = vetor[0];
  long min = vetor[0];

  for (long i = 1; i < tamanho; i++) {
    if (vetor[i] > max)
      max = vetor[i];
    if (vetor[i] < min)
      min = vetor[i];
  }

  long range = max - min + 1;
  long *count = (long *)calloc(range, sizeof(long));
  long *saida = (long *)malloc(tamanho * sizeof(long));

  for (long i = 0; i < tamanho; i++)
    count[vetor[i] - min]++;

  for (long i = 1; i < range; i++)
    count[i] += count[i - 1];

  for (long i = tamanho - 1; i >= 0; i--) {
    saida[count[vetor[i] - min] - 1] = vetor[i];
    count[vetor[i] - min]--;
  }

  memcpy(vetor, saida, tamanho * sizeof(long));

  free(count);
  free(saida);
}

int main(int argc, char *argv[]) {
  FILE *file = fopen(argv[1], "r");
  if (file == NULL) {
    printf("Erro abrindo arquivo\n");
    return 1;
  }

  long line_count = 0;
  char ch;
  while (!feof(file)) {
    ch = fgetc(file);
    if (ch == '\n') {
      line_count++;
    }
  }
  rewind(file);

  long *lista = malloc(line_count * sizeof(long));
  long count = 0;
  long num;

  while (fscanf(file, "%ld", &num) == 1) {
    lista[count] = num;
    count++;
  }
  fclose(file);

  printf("Medindo tempo do arquivo %s:\n\n", argv[1]);
  long tamanho = count - 1;

  long *listaMerge = malloc(line_count * sizeof(long));
  memcpy(listaMerge, lista, line_count * sizeof(long));
  clock_t inicio = clock();
  mergeSort(listaMerge, 0, tamanho);
  clock_t fim = clock();
  double tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
  printf("Tempo de execucao mergeSort: %f segundos\n", tempo_execucao);

  long *listaInsertion = malloc(line_count * sizeof(long));
  memcpy(listaInsertion, lista, line_count * sizeof(long));
  inicio = clock();
  insertionSort(listaInsertion, tamanho);
  fim = clock();
  tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
  printf("Tempo de execucao insertionSort: %f segundos\n", tempo_execucao);

  long *listaBubble = malloc(line_count * sizeof(long));
  memcpy(listaBubble, lista, line_count * sizeof(long));
  inicio = clock();
  bubbleSort(listaBubble, tamanho);
  fim = clock();
  tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
  printf("Tempo de execucao bubbleSort: %f segundos\n", tempo_execucao);

  long *listaQuickPivoFixo = malloc(line_count * sizeof(long));
  memcpy(listaQuickPivoFixo, lista, line_count * sizeof(long));
  inicio = clock();
  quickSortFixo(listaQuickPivoFixo, 0, tamanho);
  fim = clock();
  tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
  printf("Tempo de execucao quickSort pivo fixo: %f segundos\n",
         tempo_execucao);

  long *listaQuickPivoAleatorio = malloc(line_count * sizeof(long));
  memcpy(listaQuickPivoAleatorio, lista, line_count * sizeof(long));
  inicio = clock();
  quickSortAleatorio(listaQuickPivoAleatorio, 0, tamanho);
  fim = clock();
  tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
  printf("Tempo de execucao quickSort pivo aleatorio: %f segundos\n",
         tempo_execucao);

  long *listaCountSort = malloc(line_count * sizeof(long));
  memcpy(listaCountSort, lista, line_count * sizeof(long));
  inicio = clock();
  countSort(listaCountSort, tamanho);
  fim = clock();
  tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
  printf("Tempo de execucao countSort: %f segundos\n", tempo_execucao);

  printf("\n\n");
  return 0;
}
