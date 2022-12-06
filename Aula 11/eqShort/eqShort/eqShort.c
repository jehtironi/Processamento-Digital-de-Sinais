#include <stdio.h>
#include <string.h>
#include <cycles.h>



#define NSAMPLES       100

	short coefPA[NSAMPLES]={
   				#include "Coef_PA_short.dat"
   };
  
 	short coefPB[NSAMPLES]={
   				#include "Coef_PB_short.dat"
   };
   	short coefPF[NSAMPLES]={
   				#include "Coef_PF_short.dat"
   };
   
   short Coefs[NSAMPLES];
   
   
   
   
extern short proc_alg( short *, short *, int);

int main(int argc,char *argv[])
{
 	cycle_stats_t stats;   
	FILE *fin,*fout;
    int i, n_amost;;

	short entrada;
	short saida;
  	short sample[NSAMPLES];
    float ganhoPB = 0.8;
	float ganhoPF = 0.5;
	float ganhoPA = 0.2;
	
	//Calcula ganhos 
  	for(i=0;i<NSAMPLES;i++){
   		Coefs[i] = coefPB[i]*ganhoPB + coefPF[i]*ganhoPF + coefPA[i]*ganhoPA;
   	}
	
	//Abre arquivos
	fin = fopen("..\\sweep.pcm","rb");
    	if ((fin)==NULL)
  		{
    		printf("\nErro: nao abriu o arquivo de Entrada\n");
    		return 0;
  		}
    fout = fopen("..\\sai_audio_eq.pcm","wb");
    	if ((fout)==NULL)
  		{
    		printf("\nErro: nao abriu o arquivo de Saida\n");
    		return 0;
  		}
  	
  	CYCLES_INIT(stats);
	
  	//Calcula a saida utilizando a~biblioteca proc_alg
	while (fread(&entrada,sizeof(short),1,fin) == 1) 
	{
		sample[0] = entrada;
		
		CYCLES_START(stats);	
		
		saida = proc_alg( Coefs, sample, NSAMPLES);

		CYCLES_STOP(stats);
		fwrite(&saida,sizeof(short),1,fout);
	}

	CYCLES_PRINT(stats);
	fclose(fin);
	fclose(fout);
		
    return 0;
}
