/*
 * pd.c
 *
 *  Created on: 12/05/2011
 *      Author: fams
 */
#include <stdio.h>
#include <stdlib.h>
#include "../util/debug.h"


void mostrapassos(int *comp,int *tab, int n);

void pdbastao(int n, int *tabela, int dim){
	//int tabela[11] = {0,1,5,8,9,10,17,17,20,24,25};
	int j,i;
	int *componentes;
	int maxlocal,ganho;

	componentes = malloc(sizeof (int) * n * 2);
	for(i=0;i<n;i++)
		componentes[i*2]=i;

	for (i=1;i<(n+1);i++){
		maxlocal=0;
		for(j=0;j<i;j++){
			ganho = tabela[j] + tabela[i-j];
			if(ganho>maxlocal){
				maxlocal =ganho;
				componentes[i*2]=i-j;
				componentes[(i*2)+1]=j;
			}
		}
		if(tabela[i]<maxlocal){
			verb2p(printf("Maximo ganho para %i eh %i\n",i,maxlocal),2);
			verb2p(mostrapassos(componentes,tabela,i),2);
			verb2p(printf("\n"),2);
			tabela[i]=maxlocal;
		}
	}
	verb2p(printf("O ganho eh: %i\nCortes:",tabela[n]),1);
	mostrapassos(componentes,tabela,n);
}

void mostrapassos(int *comp,int *tab, int n){
	if( comp[n*2] != n ){
		mostrapassos(comp, tab, comp[n*2]);
		mostrapassos(comp,tab,comp[(n*2)+1]);
	}else{
		verb2p(printf("%i,",n),1);
	}
}
