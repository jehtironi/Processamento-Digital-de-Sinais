#include <stdio.h>
#include <fcntl.h>
#include <io.h>

int main()
{
    FILE *in_file, *out_file;
    int i, n, n_amost;
    int tam = 0;

    //Declaração das variaveis utilizadas
    float a0, a1, a2;
    short y;
    y = 0;
    a0 = 0.5;
    a1 = 0.3;
    a2 = 0.2;
    int d1 = 5000; //distancia 1
    int d2 = 5500; //distancia 2

    short entrada;

    /* abre os arquivos de entrada e saida */
    if ((in_file = fopen("alo.pcm", "rb")) == NULL)
    {
        printf("\nErro: Nao abriu o arquivo de entrada\n");
        return 0;
    }
    if ((out_file = fopen("eco_saida.pcm", "wb")) == NULL)
    {
        printf("\nErro: Nao abriu o arquivo de saida\n");
        return 0;
    }

    while (fread(&entrada, sizeof(short), 1, in_file) > 0) // Calculando o tamanho do arquivo
    {
        tam++;
    }
    rewind(in_file); // Enviando cursor para o inicio do arquivo

    short sample[tam];

    // zera vetor de amostras
    for (i = 0; i < tam; i++)
    {
        sample[i] = 0;
    }

    // execução do filtro
    for(int i = 0; i < tam; i++) {
         y = 0;

         fread(&entrada, sizeof(short), 1, in_file); // entrada recebe dado na posicao do cursor
         sample[i] = entrada;

         //calcula o deslocamento
         y = sample[i] * a1 + sample[i-d1] * a1 + sample[1-d2]*a2;

         // escreve no arquivo de saída
         fwrite(&y, sizeof(short), 1, out_file);
    }

    // fecha os arquivos de entrada de saída
    fclose(out_file);
    fclose(in_file);
    return 0;
}
