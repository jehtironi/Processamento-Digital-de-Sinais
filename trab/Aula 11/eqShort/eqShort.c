/* Implementa��o de um filtro FIR 
L� um arquivo bin�rio com amostras em 16bits
Salva arquivo filtrado tamb�m em 16 bits
Walter vers�o 1.0 
 */
#include <stdio.h>
//#include <fcntl.h>
//#include <io.h>
#include <cycles.h>


#define NSAMPLES       320

int main()
{
	cycle_stats_t stats;
	FILE *in_file, *out_file;
    int i, n, n_amost;
   
	float saidaPB = 0;
	float saidaPF = 0;
	float saidaPA = 0;

	// Definicao dos ganhos dos filtros
	float ganhoPB = 0.7;
	float ganhoPF = 0.6;
	float ganhoPA = 0.5;
	
	/*float ganhoPB = 0.0;
	float ganhoPF = 0.0;
	float ganhoPA = 1.0;*/
	
	/*float ganhoPB = 0.0;
	float ganhoPF = 1.0;
	float ganhoPA = 0.0;*/
	
	/*float ganhoPB = 1.0;
	float ganhoPF = 0.0;
	float ganhoPA = 0.0;*/
  
    short entrada, saida;
    short sample[NSAMPLES] = {0x0};

    float y = 0;
   
    float coefPB[NSAMPLES]={
    	#include "coefPB.dat" // tam
    };
   
    float coefPA[NSAMPLES]={
    	#include "coefPA.dat" // tam
    };
   
    float coefPF[NSAMPLES]={
    	#include "coefPF.dat" // tam
    };
    
    
	// inicializando a estrutura de cycles
	CYCLES_INIT(stats);
	/* abre os arquivos de entrada e saida */
	if ((in_file = fopen("..//sweep.pcm","rb"))==NULL)
	{
		printf("\nErro: Nao abriu o arquivo de entrada\n");
    	return 0;
	}
  
	if ((out_file = fopen("..//sai_sweep_eq4.pcm","wb"))==NULL)
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
    	y=0;

        //l� dado do arquivo
        n_amost = fread(&entrada,sizeof(short),1,in_file);
        
        //zera sa�da do filtro
    	saidaPB = 0;
    	saidaPA = 0;
    	saidaPF = 0;
    
		CYCLES_START(stats);
        sample[0] = entrada;

        

	//Convolu��o e acumula��o PB
    for (n = 0; n < NSAMPLES; n++) {
    	saidaPB += coefPB[n] * sample[n];
    }

    //Convolu��o e acumula��o PF
    for (n = 0; n < NSAMPLES; n++) {
		saidaPF += coefPF[n] * sample[n];
    }

    //Convolu��o e acumula��o PA
    for (n = 0; n < NSAMPLES; n++) {
    	saidaPA += coefPA[n] * sample[n];
    }

    // soma as saidas
    y = ganhoPB * saidaPB + ganhoPF * saidaPF + ganhoPA * saidaPA;

    //desloca amostra
    for (n = NSAMPLES - 1; n > 0; n--) {
      sample[n] = sample[n - 1];
    }

	saida = (short) y;
	CYCLES_STOP(stats);

    //escreve no arquivo de sa�da
    fwrite(&saida,sizeof(short),1,out_file);

	}while (n_amost);
 
 	CYCLES_PRINT(stats);

   //fecha os arquivos de entrada de sa�da
   fclose(out_file);
   fclose(in_file);
   return 0;
}
