/*
 * backtrack.c
 *
 *  Created on: 28/04/2011
 *      Author: fams
 */
#include "../util/es.h"
#include <stdio.h>
#include "../util/debug.h"
#include <stdlib.h>
typedef struct  { int distancia;
				  char movimento ;
				} posf;
extern int MaxProf;

int calculo_distancia(int n, int p, int v){
    int             io, jo, i, j;
    i = p / n;
    j = p % n;
    io = (v-1) / n;
    jo = (v-1) % n;
    return abs(jo - j) + abs(io - i);
}
void QueuePrio(int t, posf *fila  ){
   int i,j;
   posf chave;
   for(j=1;j<t;++j){
       chave= fila[j];
       i=j-1;
       while(i>=0 && fila[i].distancia > chave.distancia){
           fila[i+1]=fila[i];
           i--;
       }
       fila[i+1]=chave;
   }
}


void mostraPassos(int *M, int pos, int n);

void ReStore(int *A,int *M,int pos,int n){
	int i;
	verb2p(printf("Desfazendo movimento e retornando para %i\n",pos),1);
	for (i=0;i<(n*n);i++){
		verb2p(printf("%i,%s",M[i+(pos*n*n)],(((i % n) == (n-1))?"\n":"")),2);
		A[i] = M[i+(pos*n*n)];
	}
}

void Store(int *A,int *M,int pos,int n){
	int i;
	verb2p(printf("Armazenando passo %i\n",pos),2);
	for (i=0;i<(n*n);i++){
		M[i+(pos*n*n)] = A[i];
		verb2p(printf("%i,%s",A[i],(((i % n) == (n-1))?"\n":"")),2);
	}
}

int compara(int *A,int  *B, int n){
	int i;
	for (i=0;i<(n*n);i++)
		if(A[i] != B[i])
			return 0;
	return 1;
}

//Testa Solu‹o
int Solved(int n,int *A){
	int i;
	for(i=0;i<((n*n)-1);i++)
		if(A[i] != i+1)
			return 0;
	return 1;
}

//Testa inviabilidade
int Invalid(int *A, int *Mem, int pos, int n){
		int i;
		for (i=0;i<pos;i++)
			if (compara(A, Mem+(n*n*i),n)){
				//verb2p(mostraMatInt2(n, n, A, 0, 0),2);
				return 1;
			}
	return 0;
}

//Move para um estado
void Move(int *A, //Estado Atual
		int *p,    //Vazio
		int *pos	  //Destino
		){
	int aux;
	aux    = A[*p];
	A[*p]   = A[*pos];
	A[*pos] = aux;
}

int bs_puzzle(int n, int *A, int *Mem, int *p,int pos){
	int *ant, destino, validos=0,i;	/* implementando um Branch and bound */
	posf fila[4];

	if(pos>MaxProf){
		printf("Profundidade maxima da arvore de pesquisa alcancado: %i\n",MaxProf);
		exit(1);
	}
	if((*p / n) != 0 ){
		destino = *p -n;
		fila[validos].distancia =  calculo_distancia(n,*p,A[destino]) - calculo_distancia(n,destino,A[destino]);
		fila[validos].movimento = 'c';
		validos++;
	}
	if((*p % n) != (n-1) ){
		destino = *p + 1;
		fila[validos].distancia =  calculo_distancia(n,*p,A[destino]) - calculo_distancia(n,destino,A[destino]);
		fila[validos].movimento = 'd';
		validos++;
	}
	if((*p / n) != (n-1) ){
		destino = *p + n;
		fila[validos].distancia =  calculo_distancia(n,*p,A[destino]) - calculo_distancia(n,destino,A[destino]);
		fila[validos].movimento = 'b';
		validos++;
	}
	if((*p % n) != 0 ){
		destino = *p -1;
		fila[validos].distancia =  calculo_distancia(n,*p,A[destino]) - calculo_distancia(n,destino,A[destino]);
		fila[validos].movimento = 'e';
		validos++;
	}

	//Poucos elementos, vou sortear com insertion
	QueuePrio(validos,fila);

	/* fim do Branch and Bound*/

	ant = malloc(sizeof(int));
	verb2p(printf("Movimento n:%i\n",pos),1);
	//verb2p(mostraMatInt2(n, n, A, 0, 0),2);
	if(Solved(n,A)){
		Store(A,Mem,pos,n);
    	verb2p(printf("Encontrei uma resposta com %i movimentos\n",pos),2);
    	verb2p(mostraPassos(Mem,pos,n),4);
    	return 1;
	}
	Store(A,Mem,pos,n);
	for(i=0;i<validos+1;i++){
		verb2p(printf("Mov %c distancia %i\n",fila[i].movimento,fila[i].distancia),2);
		switch(fila[i].movimento){
		case 'c':{
			verb2p(printf("Movendo para cima:\n"),1);
			*ant=*p;
			*p -= n;
			Move(A,ant,p);
			verb2p(mostraMatInt2(n, n, A, 0, 0),2);
			if(Invalid(A,Mem,pos,n)){
				verb2p(printf("Movimento repetido passo %i:\n",pos),1);
				ReStore(A,Mem,pos,n);
				*p=*ant;
			}else{
				pos++;
				verb2p(printf("Movi para cima:\n"),1);
				if(bs_puzzle(n,A,Mem,p,pos)){
					return 1;
				}else{
					verb2p(printf("Desfazendo movimento %i",pos),1);
					pos--;
					*p=*ant;
					ReStore(A,Mem,pos,n);
				}
			}
		}
		break;
		case 'd':{
			verb2p(printf("Movendo para a direita:\n"),1);
			*ant = *p;
			*p 	+= 1;
			Move(A,ant,p);
			verb2p(mostraMatInt2(n, n, A, 0, 0),2);
			if(Invalid(A,Mem,pos,n)){
				verb2p(printf("Movimento repetido passo %i:\n",pos),1);
				ReStore(A,Mem,pos,n);
				*p=*ant;
			}else{
				verb2p(printf("Movi para direita:\n"),1);
				pos++;
				if(bs_puzzle(n,A,Mem,p,pos)){
					return 1;
				}else{
					verb2p(printf("Desfazendo movimento %i",pos),1);
					pos--;
					*p=*ant;
					ReStore(A,Mem,pos,n);
				}
			}
		}
		break;
		case 'b':{
			verb2p(printf("Movendo para baixo:\n"),1);
			*ant = *p;
			*p += n;
			Move(A,ant,p);
			verb2p(mostraMatInt2(n, n, A, 0, 0),2);
			if(Invalid(A,Mem,pos,n)){
				verb2p(printf("Movimento repetido passo %i:\n",pos),1);
				ReStore(A,Mem,pos,n);
				*p=*ant;
			}else{
				verb2p(printf("Movi para baixo:\n"),1);
				pos++;
				if(bs_puzzle(n,A,Mem,p,pos)){
					return 1;
				}else{
					verb2p(printf("Desfazendo movimento %i",pos),1);
					pos--;
					*p=*ant;
					ReStore(A,Mem,pos,n);
				}
			}
		}
		break;
		case 'e':{
			verb2p(printf("Movendo para a esquerda:\n"),2);
			*ant=*p;
			*p -=1;
			Move(A,ant,p);
			verb2p(mostraMatInt2(n, n, A, 0, 0),2);
			if(Invalid(A,Mem,pos,n)){
				verb2p(printf("Movimento repetido passo %i:\n",pos),1);
				ReStore(A,Mem,pos,n);
				*p=*ant;
			}else{
				verb2p(printf("Movi para esquerda:\n"),1);
				pos++;
				if(bs_puzzle(n,A,Mem,p,pos)){
					return 1;
				}else{
					verb2p(printf("Desfazendo movimento %i",pos),1);
					pos--;
					*p=*ant;
					ReStore(A,Mem,pos,n);
				}
			}
		}
		break;
		}
	}
	//free (fila);
	return 0;
}
void mostraPassos(int *M, int pos, int n){
	int i,j;
	for(i=0;i<pos+1;i++){
		printf("Passo %i\n",i);
		for(j=0;j<(n*n);j++){
			printf("%i,%s",M[j+(i*n*n)],(((j % n) == (n-1))?"\n":""));
		}
	}
}
