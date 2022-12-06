/* Implementa��o de um filtro FIR 
L� um arquivo bin�rio com amostras em 16bits
Salva arquivo filtrado tamb�m em 16 bits
Walter vers�o 1.0 
 */
#include <stdio.h>
//#include <fcntl.h>
//#include <io.h>
#include <cycles.h>
#define taxa 0.000000000005




#define NSAMPLES       8

int main()
{
	cycle_stats_t stats;
	FILE *in_file, *out_file;
   	int i, n, n_amost;
  
    short entrada, saida;
    short sample[NSAMPLES] = {0x0};
	double coef_adaptativos[NSAMPLES];

    //Saida do sistema desconhecida
    double sd = 0.0;

    //Saida do filtro FIR
    double y = 0.0;

    //Erro quando levado em considera��o o desejado e o que foi obtido
    double erro = 0.0;
   
   float coef[NSAMPLES]={
        #include "coef_8.dat" // tam
   };
  
 
  // inicializando a estrutura de cycles
  CYCLES_INIT(stats);
   /* abre os arquivos de entrada e saida */
  if ((in_file = fopen("..//ruido_branco.pcm","rb"))==NULL)
  {
    printf("\nErro: Nao abriu o arquivo de entrada\n");
    return 0;
  }
  if ((out_file = fopen("..//sai_adaptativo.pcm","wb"))==NULL)
  {
    printf("\nErro: Nao abriu o arquivo de saida\n");
    return 0;
  }

   // zera vetor de amostras
   for (i=0; i<NSAMPLES; i++)
        {
        sample[i]=0;
        }

   // execu��o do filtro
 do {
        
 		
	   //zera sa�da do filtro
        sd = 0;
        y = 0;

        //l� dado do arquivo
        n_amost = fread(&entrada,sizeof(short),1,in_file);
		CYCLES_START(stats);
        sample[0] = entrada;

        //Convolu��o e acumula��o desconhecido
        for (n = 0; n < NSAMPLES; n++)
        {
            sd += coef[n] * sample[n];
        }

        //desloca amostra
        for (n=NSAMPLES-1; n>0; n--)
                {
                sample[n]=sample[n-1];
                }
                
        //Convolu��o e acumula��o Y
        for (n = 0; n < NSAMPLES; n++)
        {
            y += coef_adaptativos[n] * sample[n];
        }
        
        
		//Calculo do erro
        erro = sd - y;
        
        //Atualiza coeficientes
        for (n = 0; n < NSAMPLES; n++)
        {
            coef_adaptativos[n] = coef_adaptativos[n] + 2.0 * taxa * erro * sample[n];
        }
        
        
		saida = (short) y;
		CYCLES_STOP(stats);

        //escreve no arquivo de sa�da
        fwrite(&saida,sizeof(short),1,out_file);

 } while (n_amost);
 
 	CYCLES_PRINT(stats);


   //fecha os arquivos de entrada de sa�da
   fclose(out_file);
   fclose(in_file);
   return 0;
}
