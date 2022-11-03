/* Implementação de um filtro Média Móvel
Lê um arquivo binário com amostras em 16bits
Salva arquivo filtrado também em 16 bits
Walter versão 1.0
 */
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#define tam 16000

int main()
{
    FILE *in_file, *out_file;
    int i, n, n_amost;
    short entrada, saida;
    short sample[tam];
    float t1 = 100 * 0.001;
    float t2 = 150 * 0.001;
    float fs = 8000;
    float a0 = 0.5;
    float a1 = 0.3;
    float a2 = 0.2;
    int n1 = (int)(t1 * fs);
    int n2 = (int)(t2 * fs);
    float y;



    /* abre os arquivos de entrada e saida */
    if ((in_file = fopen("alo.pcm","rb"))==NULL)
    {
        printf("\nErro: Nao abriu o arquivo de entrada\n");
        return 0;
    }
    if ((out_file = fopen("alo_saida.pcm","wb"))==NULL)
    {
        printf("\nErro: Nao abriu o arquivo de saida\n");
        return 0;
    }

    i = 0;

    // execução do filtro
    do
    {


        //lê dado do arquivo
        n_amost = fread(&entrada,sizeof(short),1,in_file);
        sample[i] = entrada;

        if(i-n1<0)
        {
            y = a0 * sample[i];
        }
        else if(i-n2<0)
        {
            y = a0 * sample[i] + a1 * sample[i - n1];
        }
        else
        {
            y = a0 * sample[i] + a1 * sample[i - n1] + a2 * sample[i - n2];
        }

        saida = (short) y;
        //escreve no arquivo de saída
        fwrite(&saida,sizeof(short),1,out_file);
        i++;

    }
    while (n_amost);

    //fecha os arquivos de entrada de saída
    fclose(out_file);
    fclose(in_file);
    return 0;
}
