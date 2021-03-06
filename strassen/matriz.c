#include <stdlib.h>
#include <stdio.h>
#include "../util/es.h"
#include "../util/debug.h"



int matriz_place(int size, int ***A, int ai, int aj, int ***C);

void free_matriz(int size, int ***A){
	int i;
	for (i=0;i<size;i++){
		free((*A)[i]);
	}
	free(*A);
}

int ** matriz_multi(int size, int ***A, int ***B){
    int i, j, k,**C;
    //Gerando Matriz com retorno e mult
    C = (int **) malloc(sizeof(int **)*size);
    for (i=0;i<size;i++){
    	C[i] = malloc(sizeof(int *)*size);
        for(j=0;j<size;j++){
            for (k=0;k<size;k++)
                C[i][j] += (*A)[i][k] * (*B)[k][j];
        }
    }
    verb2p(mostraMatInt(size,&C,0,0),1);
    return C;
}
int ** matriz_soma(int size, int ***A,int ai, int aj, int ***B,int bi, int bj){
    int i, j, **C;
    verb2p(printf("Executando %i+%i\n",size,size),1);
    verb2p(mostraMatInt(size,A,ai,aj),1);
    verb2p(mostraMatInt(size,B,bi,bj),1);
    //Gerando Matriz com retorno e mult
    C=(int **) malloc(size * sizeof(int **));
    for (i=0;i<size;i++){
    	C[i]=(int *) malloc(size *sizeof(int *));
        for(j=0;j<size;j++){
                C[i][j] = (*A)[ai+i][aj+j] + (*B)[bi+i][bj+j];
        }
    }
    verb2p(mostraMatInt(size,&C,0,0),1);
    return C;
}
int ** matriz_sub(int size, int ***A, int ai, int aj, int ***B, int bi, int bj){
	int i, j, **C;
	verb2p(printf("Executando %i-%i\n",size,size),1);
	verb2p(mostraMatInt(size,A,ai,aj),1);
	verb2p(mostraMatInt(size,B,bi,bj),1);
	//Gerando Matriz com retorno e mult
    C=malloc(size *sizeof(int *));
    for (i=0;i<size;i++){
    	C[i]=malloc(size *sizeof(int *));
	    	for(j=0;j<size;j++){
	                C[i][j] = (*A)[ai+i][aj+j] - (*B)[bi+i][bj+j];
	        }
	}
    verb2p(mostraMatInt(size,&C,0,0),1);
	return C;
}

int ** matriz_multi_strass(int size, int ***A, int ai, int aj, int ***B, int bi, int bj){
    int i, **C;
    //Matrizes Intermediarias
    int **S1, **S2, **S3, **S4, **T1, **T2, **T3, **T4;
    int **P1, **P2, **P3, **P4, **P5, **P6, **P7;
    int **U1, **U2, **U3, **U4, **U5, **U6, **U7;
/*
    C = malloc(size * sizeof(int*));
    for (i=0;i<size;i++)
    	C[i] = malloc(size * sizeof(int *));
*/
    verb2p(printf ("Executando %ix%i\n",size,size),1);
    verb2p(mostraMatInt(size,A,ai,aj),1);
    verb2p(printf ("x\n"),1);
    verb2p(mostraMatInt(size,B,bi,bj),1);

    if(size==1){
    	C = (int **) malloc(sizeof(int **));
    	*C = malloc(sizeof(int *));

   // 	if(hpad>0){
    //		(*C)[c][0] = 0;
    //		return C;
    //	}
    	**C = 	(*A)[ai][aj] * (*B)[bi][bj];
    	verb2p(mostraMatInt(1,&C,0,0),1);
    	return C;
    }
    else{
    	size >>= 1;
//Fase 1
    	S1 = matriz_soma(size,A,ai+size,aj, A,ai+size,aj+size); //A21 + A22
    	S2 = matriz_sub (size,&S1,0,0,A,ai,aj);					//S1  - A11
    	S3 = matriz_sub (size,A,ai,aj,A,ai+size,aj);			//A11 - A21
    	S4 = matriz_sub (size,A,ai,aj+size,&S2,0,0);			//A12 - S2
    	T1 = matriz_sub (size,B,bi,bj+size,B,bi,bj);			//B12 - B11
    	T2 = matriz_sub (size,B,bi+size,bj+size,&T1,0,0);		//B22 - T1
    	T3 = matriz_sub (size,B,bi+size,bj+size,B,bi,bj+size);	//B22 - B12
    	T4 = matriz_sub (size,B,bi+size,bj,&T2,0,0);			//B21 - T2

    	//Fase 2
    	P1 = matriz_multi_strass (size,A,ai,aj,B,bi,bj);			//A11 * B11
    	P2 = matriz_multi_strass (size,A,ai,aj+size,B,bi+size,bj);	//A12 * B21
    	P3 = matriz_multi_strass (size,&S1,0,0,&T1,0,0);			//S1  * T1
    	P4 = matriz_multi_strass (size,&S2,0,0,&T2,0,0);			//S2  * T2
    	P5 = matriz_multi_strass (size,&S3,0,0,&T3,0,0);			//S3  * T3
    	P6 = matriz_multi_strass (size,&S4,0,0,B,bi+size,bj+size);	//S4  * B22
    	P7 = matriz_multi_strass (size,A,ai+size,aj+size,&T4,0,0);	//A22 * T4

    	U1 = matriz_soma(size,&P1,0,0,&P2,0,0);						//P1 + P2
    	U2 = matriz_soma(size,&P1,0,0,&P4,0,0);						//P1 + P4
    	U3 = matriz_soma(size,&U2,0,0,&P5,0,0);						//U2 + P5
    	U4 = matriz_soma(size,&U3,0,0,&P7,0,0);						//U3 + P7
    	U5 = matriz_soma(size,&U3,0,0,&P3,0,0);						//U3 + P3
    	U6 = matriz_soma(size,&U2,0,0,&P3,0,0);						//U2 + P3
    	U7 = matriz_soma(size,&U6,0,0,&P6,0,0);						//U6 + P6

        C = malloc(2 * size * sizeof(int*));
        for (i=0;i<(2 * size);i++)
        	C[i] = malloc((2 * size) * sizeof(int *));

        verb2p(mostraMatInt(size,&U1,0,0),1);
        matriz_place(size,&C,0,0,&U1);			//C11

        verb2p(mostraMatInt(size,&U7,0,0),1);
        matriz_place(size,&C,0,size,&U7);  	//C12

        verb2p(mostraMatInt(size,&U4,0,0),1);
        matriz_place(size,&C,size,0,&U4);		//C21

        verb2p(mostraMatInt(size,&U5,0,0),1);
        matriz_place(size,&C,size,size,&U5);	//C22

        verb2p(mostraMatInt(2*size,&C,0,0),1);
        free_matriz(size,&S1);
        free_matriz(size,&S2);
        free_matriz(size,&S3);
        free_matriz(size,&S4);
        free_matriz(size,&T1);
        free_matriz(size,&T2);
        free_matriz(size,&T3);
        free_matriz(size,&T4);
        free_matriz(size,&P1);
        free_matriz(size,&P2);
        free_matriz(size,&P3);
        free_matriz(size,&P4);
        free_matriz(size,&P5);
        free_matriz(size,&P6);
        free_matriz(size,&P7);
        free_matriz(size,&U1);
        free_matriz(size,&U2);
        free_matriz(size,&U3);
        free_matriz(size,&U4);
        free_matriz(size,&U5);
        free_matriz(size,&U6);
        free_matriz(size,&U7);
        return C;
    }
}
   int matriz_place(int size, int ***A, int ai, int aj, int ***C){
	   int i,j;
	   for (i=0;i<size;i++){
		   for(j=0;j<size;j++){
			   (*A)[ai+i][aj+j] = (*C)[i][j];;
		   }
	   }
	   return 1;
}

