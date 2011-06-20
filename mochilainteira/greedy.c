/*
 * greedy.c
 *
 *  Created on: 22/05/2011
 *      Author: fams
 */

#include "../util/es.h"
#include "greedy.h"
#include "../util/debug.h"
#include <stdio.h>


void OrdenaItems( titem *items, int t, int abordagem ){
   int i,j;
   titem chave;
   verb2p(printf("OI\n"),1);
   for(j=1;j<t;++j){
	   chave= items[j];
	   i=j-1;
	   switch (abordagem){
	   case 0: //Densidade
		   while(i>=0 && ((float)(items[i].valor/items[i].peso)) < ((float)(chave.valor/chave.peso))){
			   items[i+1]=items[i];
			   i--;
		   }
			   break;
	   case 1: //Maior VAlor
	   		   while(i>=0 && ((float)items[i].valor) < ((float)chave.valor)){
	   			   items[i+1]=items[i];
	   			   i--;
	   		   }
	   			   break;
	   case 2: //Menor Peso
	   		   while(i>=0 && ((float)items[i].peso) > ((float)chave.peso)){
	   			   items[i+1]=items[i];
	   			   i--;
	   		   }
	   			   break;
	   }
	   items[i+1]=chave;
   }
}


int gdmochila (titem *tabela, int nitems, int capmochila, int abordagem, titem *mochila, int *itensmochila ){
	int i, j=0, usomochila=0,valor=0;
	//Ordenação para abordagem Gulosa
	//Somente alteramos forma de ordenar os items
	verb2p(printf("Ordenando itens abordagem %i\n",abordagem),1);
	OrdenaItems (tabela , nitems, abordagem);

	//Percorrer todos os items e guardar o que couber
	for (i=0;i<nitems;i++){
		verb2p(printf("Examinando item %i, peso %i, valor %i\n Capacidade mochila %i\nValor atual:%i \n",tabela[i].codigo,tabela[i].peso, tabela[i].valor, capmochila,valor),2);
		if( (tabela[i].peso + usomochila) <= capmochila){
			capmochila -= tabela[i].peso;
			mochila[j] = tabela[i];
			valor += tabela[i].valor;
			verb2p(printf("Levando: item %i, peso %i, valor %i\n Capacidade mochila %i\nValor atual:%i \n",tabela[i].codigo,tabela[i].peso, tabela[i].valor, capmochila,valor),1);
			j++;
		}
	}
	*itensmochila = j;
	return valor;
}
