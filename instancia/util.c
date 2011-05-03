#include <stdio.h>




void TrocaValVet(int * A, int a, int b){
	int aux;
	aux  = A[a];
	A[a] = A[b];
	A[b] = aux;
}
/*
 Método Knuth de geração de números aleatórios em vetor
 */

void embaralha(int tamanho, int *A, int entropia){
    int i,j,falta=0,ponto;
    //random
    srandomdev();
    falta = tamanho ;
    for (j=0;j<tamanho;j++){
        ponto=(int)((random()%(falta))+j);
              //Entropia percentual
        if((int)(random()%(100)) < entropia)
        	//printf("Troca A[%i] = %i com A[%i] = %i\n",j,A[j],ponto,A[ponto]);
            TrocaValVet(A ,j, ponto);
        falta--;
        //for(i=0;i<tamanho;i++)
        	//printf("%i,",A[i]);
        	//printf("\n");
    }
}

int Insoluvel(int *A, int n){
int i,j,errados=0;
    for(i=0;i<n*n;i++){
        if(A[i] == 0)
            continue;
        for(j=i+1;j<(n * n);j++){
            if(A[j] == 0)
                continue;
            if(A[i] > A[j])
                errados++;
        }
    }
    return errados % 2;
}

        
