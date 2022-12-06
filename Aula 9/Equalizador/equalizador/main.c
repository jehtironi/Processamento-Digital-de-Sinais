#include <stdio.h>
#include <fcntl.h>
#include <io.h>

// quantidade de coeficientes
#define NSAMPLES 200

int main() {
  FILE * in_file, * out_file;
  int i, n, n_amost;

  short entrada, saida;
  short sample[NSAMPLES] = {
    0x0
  };

  float y_pb = 0;
  float y_pf = 0;
  float y_pa = 0;
  float y = 0;

  // Definicao dos ganhos dos filtros
  float g_pb = 0.7;
  float g_pf = 0.6;
  float g_pa = 0.5;


  //Carregando os coeficientes do filtro pb
  float coef_pb[NSAMPLES] = {
        #include "coefPB.dat" // NSAMPLES
  };

  //Carregando os coeficientes do filtro pb
  float coef_pf[NSAMPLES] = {
        #include "coefPF.dat" // NSAMPLES
  };

  //Carregando os coeficientes do filtro pb
  float coef_pa[NSAMPLES] = {
        #include "coefPA.dat" // NSAMPLES
  };

  /* abre os arquivos de entrada e saida */
  if ((in_file = fopen("sweep.pcm", "rb")) == NULL) {
    printf("\nErro: Nao abriu o arquivo de entrada\n");
    return 0;
  }
  if ((out_file = fopen("sweepSaida4.pcm", "wb")) == NULL) {
    printf("\nErro: Nao abriu o arquivo de saida\n");
    return 0;
  }

  // zera vetor de amostras
  for (i = 0; i < NSAMPLES; i++) {
    sample[i] = 0;
  }

  // execução do filtro
  do {

    //zera saída do filtro
    y_pb = 0;
    y_pf = 0;
    y_pa = 0;

    //lê dado do arquivo
    n_amost = fread( & entrada, sizeof(short), 1, in_file);
    sample[0] = entrada;

    //Convolução e acumulação PB
    for (n = 0; n < NSAMPLES; n++) {
      y_pb += coef_pb[n] * sample[n];
    }

    //Convolução e acumulação PF
    for (n = 0; n < NSAMPLES; n++) {
      y_pf += coef_pf[n] * sample[n];
    }

    //Convolução e acumulação PA
    for (n = 0; n < NSAMPLES; n++) {
      y_pa += coef_pa[n] * sample[n];
    }

    // soma as saidas
    y = g_pb*y_pb + g_pf*y_pf + g_pa*y_pa;

    //desloca amostra
    for (n = NSAMPLES - 1; n > 0; n--) {
      sample[n] = sample[n - 1];
    }

    saida = (short) y;

    //escreve no arquivo de saída
    fwrite( & saida, sizeof(short), 1, out_file);

  } while (n_amost);

  //fecha os arquivos de entrada de saída
  fclose(out_file);
  fclose(in_file);
  return 0;
}
