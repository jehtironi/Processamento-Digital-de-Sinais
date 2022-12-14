/* Implementa??o de um filtro M?dia M?vel
L? um arquivo bin?rio com amostras em 16bits
Salva arquivo filtrado tamb?m em 16 bits
Walter vers?o 1.0
*/
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <math.h>
#define tam 320 // Tamanho da m?dia

int main()
{
    FILE *in_file, *out_file;
    int i, n, n_amost;

    short entrada, saida;
    short sample[tam] = {0x0};
    int y;

    //Carregando os coeficientes do filtro pb
    float coef[tam] = {
        #include "coefPF.dat" // tam
    };

    /* abre os arquivos de entrada e saida */
    if ((in_file = fopen("sweep.pcm", "rb")) == NULL)
    {
        printf("\nErro: Nao abriu o arquivo de entrada\n");
        return 0;
    }
    if ((out_file = fopen("Saida_PF.pcm", "wb")) == NULL)
    {
        printf("\nErro: Nao abriu o arquivo de saida\n");
        return 0;
    }

    // zera vetor de amostras
    for (i = 0; i < tam; i++)
    {
        sample[i] = 0;
    }

    // execu??o do filtro
    do
    {
        y = 0; // zera sa?da do filtro;

        n_amost = fread(&entrada, sizeof(short), 1, in_file); // l? dado do arquivo

        sample[0] = entrada;

        for (n = 0; n < tam; n++) // Convolu??o

        {

            y += coef[n] * sample[n];
        }
        for (n = tam - 1; n > 0; n--) // desloca vetor de amostras

        {
            sample[n] = sample[n - 1];
        }

        saida = (short)y;

        fwrite(&saida, sizeof(short), 1, out_file); // escreve no arquivo de sa?da
    }
    while (n_amost);

    // fecha os arquivos de entrada de sa?da
    fclose(out_file);
    fclose(in_file);
    return 0;
}
