/*
 * greedy.h
 *
 *  Created on: 23/05/2011
 *      Author: fams
 */

typedef struct  { int codigo;
				  int peso;
				  int valor;
} titem;

int gdmochila (titem *tabela, int nitems, int capmochila, int abordagem, titem *mochila, int *itensmochila );
