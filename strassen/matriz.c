#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../util/es.h"
#include "../util/debug.h"
#include "../util/contadores.h"
#define m(mat,size,i,j) mat[((size)*(i))+(j)]



int * matriz_multi(int size, int *A, int *B){
    int i, j, k,*C;
    //Gerando Matriz com retorno e mult
    C = (int *) malloc(sizeof(int *)*size*size);
    for (i=0;i<size;i++){
        for(j=0;j<size;j++){
            for (k=0;k<size;k++){
                m(C,size,i,j) += m(A,size,i,k) * m(B,size,k,j);_Mul();_Som();_Atb();
            }
        }
    }
    verb2p(mostraMatInt(size,C,0,0),1);
    return C;
}
void matriz_soma(
		int n,  //Tamanho da submatriz
		int *A, //Matriz A
		int ai, //linha de A
		int aj, //coluna de A
		int as, //Deslocamento de A
		int *B, //Matriz B
		int bi, //Linha de B
		int bj, //Coluna de B
		int bs,	//Deslocamento de B
		int *C, //Matriz retorno
		int ci,
		int cj,
		int cs
		){
    int i, j;
    verb2p(printf("ai=%i aj=%i bi=%i bj=%i as=%i, bs=%i, n=%i \n",ai,aj,bi,bj,as,bs,n),2);
    verb2p(printf("Executando %i+%i\n",n,n),1);
    verb2p(mostraMatInt2(n,as,A,ai,aj),1);
    verb2p(mostraMatInt2(n,bs,B,bi,bj),1);
    //Gerando Matriz com retorno e mult


    for (i=0;i<n;i++){
        for(j=0;j<n;j++){
                m(C,cs,i+ci,j+cj) = m(A,as,ai+i,aj+j) + m(B,bs,bi+i,bj+j);_Som();_Atb();
                verb2p(printf("C[%i][%i] (%i) = A[%i][%i] (%i) + B[%i][%i] (%i)\n", i, j, m(C,n,i,j), ai+i, aj+j, m(A,as,ai+i,aj+j), i+bi, j+bj, m(B,bs,bi+i,bj+j) ),2);
        }
    }
    verb2p(mostraMatInt(n,C,0,0),1);

}
void matriz_sub(
		int n,  //Tamanho da submatriz
		int *A, //Matriz A
		int ai, //linha de A
		int aj, //coluna de A
		int as, //Deslocamento de A
		int *B, //Matriz B
		int bi, //Linha de B
		int bj, //Coluna de B
		int bs,	//Deslocamento de B
		int *C //Matriz retorno
		){
	int i, j;
    verb2p(printf("ai=%i aj=%i bi=%i bj=%i as=%i, bs=%i, n=%i \n",ai,aj,bi,bj,as,bs,n),2);
	verb2p(printf("Executando %i-%i\n",n,n),1);
	verb2p(mostraMatInt2(n,as,A,ai,aj),1);
	verb2p(mostraMatInt2(n,bs,B,bi,bj),1);
	//Gerando Matriz com retorno e mult

    for (i=0;i<n;i++){
	    	for(j=0;j<n;j++){
	                m(C,n,i,j) = m(A,as,ai+i,aj+j) - m(B,bs,bi+i,bj+j); _Atb();_Som();
	        }
	    }
    verb2p(mostraMatInt2(n,n,C,0,0),1);
}

void matriz_multi_strass(
		int n,  //Tamanho da submatriz
		int *A, //Matriz A
		int ai, //linha de A
		int aj, //coluna de A
		int as, //Deslocamento de A
		int *B, //Matriz B
		int bi, //Linha de B
		int bj, //Coluna de B
		int bs,	//Deslocamento de B
		int *C,  //Matriz Retorno
		int ci,
		int cj,
		int cs
		){
    int i;
    //Matrizes Intermediarias
    int *S1, *S2, *S3, *S4, *T1, *T2, *T3, *T4;
    int *P1, *P2, *P3, *P4, *P5, *P6, *P7;
    int *U1, *U2, *U3, *U4, *U5, *U6, *U7;

    verb2p(printf ("Executando %ix%i\n",n,n),1);
    verb2p(mostraMatInt2(n,as,A,ai,aj),1);
    verb2p(printf ("x\n"),1);
    verb2p(mostraMatInt2(n,bs,B,bi,bj),1);

    if(n==1){
    	//C = (int *) malloc(sizeof(int *));
    	*C = 	m(A,as,ai,aj) * m(B,bs,bi,bj);_Mul();
    	verb2p(mostraMatInt2(1,1,C,0,0),1);
    	return;
    }
    else{
        n  >>= 1;
//Fase 1
        int * sums, * prods;
        int size = n*n;
        sums = malloc(sizeof(int *) * size * 8);
        S1=sums;
        S2=S1+(size);
        S3=S2+(size);
        S4=S3+(size);
        T1=S4+(size);
        T2=T1+(size);
        T3=T2+(size);
        T4=T3+(size);
    	verb2p(printf("S1 A21 + A22\n"),2);
        matriz_soma(n,A,ai+n,aj,as, A,ai+n,aj+n,as,S1,0,0,n); //A21 + A22
        verb2p(printf("S2 S1  - A11\n"),2);
    	matriz_sub (n,S1,0,0,n,A,ai,aj,as,S2);					//S1  - A11
    	verb2p(printf("S3 A11 - A21\n"),2);
    	matriz_sub (n,A,ai,aj,as,A,ai+n,aj,as,S3);			//A11 - A21
    	verb2p(printf("S4 A12 - S2\n"),2);
    	matriz_sub (n,A,ai,aj+n,as,S2,0,0,n,S4);			//A12 - S2
    	verb2p(printf("T1 B12 - B11\n"),2);
    	matriz_sub (n,B,bi,bj+n,bs,B,bi,bj,bs,T1);			//B12 - B11
    	verb2p(printf("T2 B22 - T1\n"),2);
    	matriz_sub (n,B,bi+n,bj+n,bs,T1,0,0,n,T2);		//B22 - T1
    	verb2p(printf("T3 B22 -B12\n"),2);
    	matriz_sub (n,B,bi+n,bj+n,bs,B,bi,bj+n,bs,T3);	//B22 - B12
    	verb2p(printf("T4 B21 - T2\n"),2);
    	matriz_sub (n,B,bi+n,bj,bs,T2,0,0,n,T4);			//B21 - T2

    	//Fase 2
    	prods = malloc(sizeof(int *) * size * 7);
    	P1 =prods;
    	P2 =P1+(size);
    	P3 =P2+(size);
    	P4 =P3+(size);
    	P5 =P4+(size);
    	P6 =P5+(size);
    	P7 =P6+(size);
    	verb2p(printf("P1 A11 * B11\n"),2);
    	matriz_multi_strass (n,A,ai,aj,as,B,bi,bj,bs,P1,0,0,n);			//A11 * B11
    	verb2p(printf("P2 A12 * B21\n"),2);
    	matriz_multi_strass (n,A,ai,aj+n,as,B,bi+n,bj,bs,P2,0,0,n);	//A12 * B21
    	verb2p(printf("P3 S1  * T1\n"),2);
    	matriz_multi_strass (n,S1,0,0,n,T1,0,0,n,P3,0,0,n);			//S1  * T1
    	verb2p(printf("P4 S2 * T2\n"),2);
    	matriz_multi_strass (n,S2,0,0,n,T2,0,0,n,P4,0,0,n);			//S2  * T2
    	verb2p(printf("P5 S3 * T3\n"),2);
    	matriz_multi_strass (n,S3,0,0,n,T3,0,0,n,P5,0,0,n);			//S3  * T3
    	verb2p(printf("P6 S4 * B22\n"),2);
    	matriz_multi_strass (n,S4,0,0,n,B,bi+n,bj+n,bs,P6,0,0,n);	//S4  * B22
    	verb2p(printf("P7 A22 * T4\n"),2);
    	matriz_multi_strass (n,A,ai+n,aj+n,as,T4,0,0,n,P7,0,0,n);	//A22 * T4

    	U1=sums;
        U2=U1+(size);
        U3=U2+(size);
        U4=U3+(size);
        U5=U4+(size);
        U6=U5+(size);
        U7=U6+(size);
    	verb2p(printf("U1 P1 + P2 (C11)\n"),2);
    	matriz_soma(n,P1,0,0,n,P2,0,0,n,C,0,0,2*n);						//P1 + P2
    	verb2p(printf("U2 P1 + P4\n"),2);
    	matriz_soma(n,P1,0,0,n,P4,0,0,n,U2,0,0,n);						//P1 + P4
    	verb2p(printf("U3 U2 + P5\n"),2);
    	matriz_soma(n,U2,0,0,n,P5,0,0,n,U3,0,0,n);						//U2 + P5
    	verb2p(printf("U4 U3 + P7 (C21)\n"),2);
    	matriz_soma(n,U3,0,0,n,P7,0,0,n,C,n,0,2*n);						//U3 + P7
    	verb2p(printf("U5 U3 + P3 (C22)\n"),2);
    	matriz_soma(n,U3,0,0,n,P3,0,0,n,C,n,n,2*n);						//U3 + P3
    	verb2p(printf("U6 U2 + P3\n"),2);
    	matriz_soma(n,U2,0,0,n,P3,0,0,n,U6,0,0,n);						//U2 + P3
    	verb2p(printf("U7 U6 + P6 (C12)\n"),2);
    	matriz_soma(n,U6,0,0,n,P6,0,0,n,C,0,n,n*2);						//U6 + P6

        verb2p(mostraMatInt2(2*n,2*n,C,0,0),1);
        free(sums);
        free(prods);

    }
}



