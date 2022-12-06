#include <stdio.h>
#include <string.h>
#include <cycles.h>


#define NSAMPLES 320

float coefPB[NSAMPLES] = {
	#include "CoefPB.dat" // Coeficiente Passa Baixa 
}; 
float coefPA[NSAMPLES] = {
	#include "CoefPA.dat" // Coeficiente Passa Alta 
};
float coefBP[NSAMPLES] = {
	#include "CoefBP.dat" // Coeficiente Passa Faixa 
};


int main(int argc,char *argv[])
{
 	cycle_stats_t stats;   
	FILE *fin,*fout;
	
	short entrada, saida;
	float saidaPB, saidaPA, saidaBP, saidaT; 

  	short Vet_entr[NSAMPLES]= {0x0};
  	
  	int PB_input = 1, PA_input = 1, BP_input = 1;
	int i;
	
	printf("***************************************************************\n");
	printf("* 						EQUALIZADOR							  *\n");
	printf("*                                                             *\n");
	printf("***************************************************************\n");
	printf("\n");
	
	
	fin = fopen("..\\sweep_100_3k4.pcm","rb");
    if ((fin)==NULL){
    	printf("\nErro: nao abriu o arquivo de Entrada\n");
    	return 0;
  	}
    fout = fopen("..\\sai_PBPABP.pcm","wb");
    if ((fout)== NULL){
    	printf("\nErro: nao abriu o arquivo de Saida\n");
    	return 0;
  	}
  	
  	CYCLES_INIT(stats);
  		
	printf("Processando ...\n ");
	  
	while (fread(&entrada,sizeof(short),1,fin) == 1){
	  	saidaPB = 0;
		saidaBP = 0;
		saidaPA = 0;
  		
		CYCLES_START(stats);
		
		Vet_entr[0] = entrada;
	
		int n = 0;
        for(n = 0; n < NSAMPLES; n++){
            saidaPB += coefPB[n] * Vet_entr[n] * PB_input;
            saidaBP += coefBP[n] * Vet_entr[n] * BP_input;
            saidaPA += coefPA[n] * Vet_entr[n] * PA_input;

            saidaT = saidaPB + saidaBP + saidaPA;
        }
        for(n = NSAMPLES-1; n>0; n--){
            Vet_entr[n] = Vet_entr[n-1];
        }	
		
		saida = saidaT;

		CYCLES_STOP(stats);
		fwrite(&saida,sizeof(short),1,fout);	
			
	}

	printf("terminado!\n");
		
    
	CYCLES_PRINT(stats);
	fclose(fin);
	fclose(fout);
		
	return 0;
}