#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#define tam 8// Tamanho da média
#define taxa 0.0000000000005

int main()
{
    FILE *in_file, *out_file;
    int i, n, n_amost;

    short entrada, saida;
    short sample[tam] = {0x0};
    double coef_adaptativos[tam];

    //Saida do sistema desconhecida
    double sd = 0.0;

    //Saida do filtro FIR
    double y = 0.0;

    //Erro quando levado em consideração o desejado e o que foi obtido
    double erro = 0.0;


    // Carregando os coeficientes
    float coef[tam] =
    {
        #include "coef_8.dat"
    };

    /* abre os arquivos de entrada e saida */
    if ((in_file = fopen("ruido_branco.pcm", "rb")) == NULL)
    {
        printf("\nErro: Nao abriu o arquivo de entrada\n");
        return 0;
    }
    if ((out_file = fopen("FA_saida_erro.pcm", "wb")) == NULL)
    {
        printf("\nErro: Nao abriu o arquivo de saida\n");
        return 0;
    }

    // zera vetor de amostras
    for (i = 0; i < tam; i++)
    {
        sample[i] = 0;

    }

    // execução do filtro
    do
    {
        //Zera saída do filtro
        sd = 0;
        y = 0;

        //Lê dado do arquivo
        n_amost = fread( & entrada, sizeof(short), 1, in_file);
        sample[0] = entrada;

        //Convolução e acumulação da entrada desconhecido
        for (n = 0; n < tam; n++)
        {
            sd += coef[n] * sample[n];
        }

        //Convolução e acumulação Y
        for (n = 0; n < tam; n++)
        {
            y += coef_adaptativos[n] * sample[n];
        }

        //Calculo do erro
        erro = sd - y;

        printf("erro %f\n", erro);

        //Atualiza coeficientes
        for (n = 0; n < tam; n++)
        {
            coef_adaptativos[n] = coef_adaptativos[n] + 2.0 * taxa * erro * sample[n];
        }

        //Desloca amostra
        for (n = tam - 1; n > 0; n--)
        {
            sample[n] = sample[n - 1];
        }

        //Salvando saida
        saida = (short) erro;
        //saida = (short) erro;

        //Escreve no arquivo de saída
        fwrite( & saida, sizeof(short), 1, out_file);
    }
    while (n_amost);

    // fecha os arquivos de entrada de saída
    fclose(out_file);
    fclose(in_file);
    return 0;
}
