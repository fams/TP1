#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../util/es.h"
#include "../util/debug.h"
#define m(mat,size,i,j) mat[((size)*(i))+(j)]


   int matriz_place( int n, int *A, int ai, int aj,int as, int *C, int ci, int cj, int cs);
// Salva Matriz em Arquivo
int mostraMatInt2(int n, int ms,int *Mat, int mi, int mj);

void free_matriz(int size, int ***A){
	int i;
	for (i=0;i<size;i++){
		free((*A)[i]);
	}
	free(*A);
}

int * matriz_multi(int size, int *A, int *B){
    int i, j, k,*C;
    //Gerando Matriz com retorno e mult
    C = (int *) malloc(sizeof(int *)*size*size);
    for (i=0;i<size;i++){
    	//C[i] = malloc(sizeof(int *)*size);
        for(j=0;j<size;j++){
            for (k=0;k<size;k++)
                m(C,size,i,j) += m(A,size,i,k) * m(B,size,k,j);
        }
    }
    verb2p(mostraMatInt(size,C,0,0),1);
    return C;
}
int * matriz_soma(
		int n,  //Tamanho da submatriz
		int *A, //Matriz A
		int ai, //linha de A
		int aj, //coluna de A
		int as, //Deslocamento de A
		int *B, //Matriz B
		int bi, //Linha de B
		int bj, //Coluna de B
		int bs	//Deslocamento de B
		){
    int i, j, *C;
    verb2p(printf("ai=%i aj=%i bi=%i bj=%i as=%i, bs=%i, n=%i \n",ai,aj,bi,bj,as,bs,n),2);
    verb2p(printf("Executando %i+%i\n",n,n),1);
    verb2p(mostraMatInt2(n,as,A,ai,aj),1);
    verb2p(mostraMatInt2(n,bs,B,bi,bj),1);
    //Gerando Matriz com retorno e mult
    //FIXME Alocar Fora
    C=(int *) malloc(n * n * sizeof(int *));

    for (i=0;i<n;i++){
    	//C[i]=(int *) malloc(size *sizeof(int *));
        for(j=0;j<n;j++){
                m(C,n,i,j) = m(A,as,ai+i,aj+j) + m(B,bs,bi+i,bj+j);
                verb2p(printf("C[%i][%i] (%i) = A[%i][%i] (%i) + B[%i][%i] (%i)\n", i, j, m(C,n,i,j), ai+i, aj+j, m(A,as,ai+i,aj+j), i+bi, j+bj, m(B,bs,bi+i,bj+j) ),2);
        }
    }
    verb2p(mostraMatInt(n,C,0,0),1);
    return C;
}
int * matriz_sub(
		int n,  //Tamanho da submatriz
		int *A, //Matriz A
		int ai, //linha de A
		int aj, //coluna de A
		int as, //Deslocamento de A
		int *B, //Matriz B
		int bi, //Linha de B
		int bj, //Coluna de B
		int bs	//Deslocamento de B
		){
	int i, j, *C;
    verb2p(printf("ai=%i aj=%i bi=%i bj=%i as=%i, bs=%i, n=%i \n",ai,aj,bi,bj,as,bs,n),2);
	verb2p(printf("Executando %i-%i\n",n,n),1);
	verb2p(mostraMatInt2(n,as,A,ai,aj),1);
	verb2p(mostraMatInt2(n,bs,B,bi,bj),1);
	//Gerando Matriz com retorno e mult
    C=malloc(n * n *sizeof(int *));
    for (i=0;i<n;i++){
    	//C[i]=malloc(size *sizeof(int *));
	    	for(j=0;j<n;j++){
	                m(C,n,i,j) = m(A,as,ai+i,aj+j) - m(B,bs,bi+i,bj+j);
	        }
	    }
    verb2p(mostraMatInt2(n,n,C,0,0),1);
	    return C;
}

int * matriz_multi_strass(
		int n,  //Tamanho da submatriz
		int *A, //Matriz A
		int ai, //linha de A
		int aj, //coluna de A
		int as, //Deslocamento de A
		int *B, //Matriz B
		int bi, //Linha de B
		int bj, //Coluna de B
		int bs	//Deslocamento de B
		){
    int i,*C;
    //Matrizes Intermediarias
    int *S1, *S2, *S3, *S4, *T1, *T2, *T3, *T4;
    int *P1, *P2, *P3, *P4, *P5, *P6, *P7;
    int *U1, *U2, *U3, *U4, *U5, *U6, *U7;
/*
    C = malloc(size * sizeof(int*));
    for (i=0;i<size;i++)
    	C[i] = malloc(size * sizeof(int *));
*/
    verb2p(printf ("Executando %ix%i\n",n,n),1);
    verb2p(mostraMatInt2(n,as,A,ai,aj),1);
    verb2p(printf ("x\n"),1);
    verb2p(mostraMatInt2(n,bs,B,bi,bj),1);

    if(n==1){
    	C = (int *) malloc(sizeof(int *));
    	//*C = malloc(sizeof(int *));

   // 	if(hpad>0){
    //		(*C)[c][0] = 0;
    //		return C;
    //	}
    	*C = 	m(A,as,ai,aj) * m(B,bs,bi,bj);
    	verb2p(mostraMatInt2(1,1,C,0,0),1);
    	return C;
    }
    else{
        n  >>= 1;
//Fase 1
    	verb2p(printf("S1 A21 + A22\n"),2);
        S1 = matriz_soma(n,A,ai+n,aj,as, A,ai+n,aj+n,as); //A21 + A22
        verb2p(printf("S2 S1  - A11\n"),2);
    	S2 = matriz_sub (n,S1,0,0,n,A,ai,aj,as);					//S1  - A11
    	verb2p(printf("S3 A11 - A21\n"),2);
    	S3 = matriz_sub (n,A,ai,aj,as,A,ai+n,aj,as);			//A11 - A21
    	verb2p(printf("S4 A12 - S2\n"),2);
    	S4 = matriz_sub (n,A,ai,aj+n,as,S2,0,0,n);			//A12 - S2
    	verb2p(printf("T1 B12 - B11\n"),2);
    	T1 = matriz_sub (n,B,bi,bj+n,bs,B,bi,bj,bs);			//B12 - B11
    	verb2p(printf("T2 B22 - T1\n"),2);
    	T2 = matriz_sub (n,B,bi+n,bj+n,bs,T1,0,0,n);		//B22 - T1
    	verb2p(printf("T3 B22 -B12\n"),2);
    	T3 = matriz_sub (n,B,bi+n,bj+n,bs,B,bi,bj+n,bs);	//B22 - B12
    	verb2p(printf("T4 B21 - T2\n"),2);
    	T4 = matriz_sub (n,B,bi+n,bj,bs,T2,0,0,n);			//B21 - T2

    	//Fase 2
    	verb2p(printf("P1 A11 * B11\n"),2);
    	P1 = matriz_multi_strass (n,A,ai,aj,as,B,bi,bj,bs);			//A11 * B11
    	verb2p(printf("P2 A12 * B21\n"),2);
    	P2 = matriz_multi_strass (n,A,ai,aj+n,as,B,bi+n,bj,bs);	//A12 * B21
    	verb2p(printf("P3 S1  * T1\n"),2);
    	P3 = matriz_multi_strass (n,S1,0,0,n,T1,0,0,n);			//S1  * T1
    	verb2p(printf("P4 S2 * T2\n"),2);
    	P4 = matriz_multi_strass (n,S2,0,0,n,T2,0,0,n);			//S2  * T2
    	verb2p(printf("P5 S3 * T3\n"),2);
    	P5 = matriz_multi_strass (n,S3,0,0,n,T3,0,0,n);			//S3  * T3
    	verb2p(printf("P6 S4 * B22\n"),2);
    	P6 = matriz_multi_strass (n,S4,0,0,n,B,bi+n,bj+n,bs);	//S4  * B22
    	verb2p(printf("P7 A22 * T4\n"),2);
    	P7 = matriz_multi_strass (n,A,ai+n,aj+n,as,T4,0,0,n);	//A22 * T4

    	verb2p(printf("U1 P1 + P2\n"),2);
    	U1 = matriz_soma(n,P1,0,0,n,P2,0,0,n);						//P1 + P2
    	verb2p(printf("U2 P1 + P4\n"),2);
    	U2 = matriz_soma(n,P1,0,0,n,P4,0,0,n);						//P1 + P4
    	verb2p(printf("U3 U2 + P5\n"),2);
    	U3 = matriz_soma(n,U2,0,0,n,P5,0,0,n);						//U2 + P5
    	verb2p(printf("U4 U3 + P7\n"),2);
    	U4 = matriz_soma(n,U3,0,0,n,P7,0,0,n);						//U3 + P7
    	verb2p(printf("U5 U3 + P3\n"),2);
    	U5 = matriz_soma(n,U3,0,0,n,P3,0,0,n);						//U3 + P3
    	verb2p(printf("U6 U2 + P3\n"),2);
    	U6 = matriz_soma(n,U2,0,0,n,P3,0,0,n);						//U2 + P3
    	verb2p(printf("U7 U6 + P6\n"),2);
    	U7 = matriz_soma(n,U6,0,0,n,P6,0,0,n);						//U6 + P6

        C = malloc((2*n) * (2 * n) * sizeof(int*));
        for (i=0;i<(2 * n);i++)

        verb2p(mostraMatInt2(n,n,U1,0,0),1);
        matriz_place(n,C,0,0,2*n,U1,0,0,n);			//C11

        verb2p(mostraMatInt2(n,n,U7,0,0),1);
        matriz_place(n,C,0,n,2*n,U7,0,0,n);  	//C12

        verb2p(mostraMatInt2(n,n,U4,0,0),1);
        matriz_place(n,C,n,0,2*n,U4,0,0,n);		//C21

        verb2p(mostraMatInt2(n,n,U5,0,0),1);
        matriz_place(n,C,n,n,2*n,U5,0,0,n);	//C22

        verb2p(mostraMatInt2(2*n,2*n,C,0,0),1);
        free(S1);
        free(S2);
        free(S3);
        free(S4);
        free(T1);
        free(T2);
        free(T3);
        free(T4);
        free(P1);
        free(P2);
        free(P3);
        free(P4);
        free(P5);
        free(P6);
        free(P7);
        free(U1);
        free(U2);
        free(U3);
        free(U4);
        free(U5);
        free(U6);
        free(U7);
        return C;
    }
}
   int matriz_place(
		   int n,
		   int *A,
		   int ai,
		   int aj,
		   int as,
		   int *C,
		   int ci,
		   int cj,
		   int cs
		   ){
	   int i,j;
	   for (i=0;i<n;i++){
		   for(j=0;j<n;j++){
			   m(A,as,ai+i,aj+j) = m(C,cs,ci+i,cj+j);;
		   }
	   }
	   return 1;
}

   int mostraMatInt2(
		   int n,  	//Tamanho
		   int ms, 	//Deslocamento
		   int *Mat,//Matriz
		   int mi, 	//linha
		   int mj  	//coluna
		 ){
       int i=0,j=0;
       //Gravando aqruivo
       char linha[13*n+10];
       char num[13];
       int s;
       *linha='\0';
       for(i=0;i<n;i++){
           for(j=0;j< n;j++){
               sprintf(num,"%i,",m(Mat,ms,i+mi,j+mj));
               strcat(linha,num);
           }
           s=strlen(linha);
           linha[s-1]='\n';
           linha[s]='\0';
           printf(linha);
           *linha='\0';
       }
       printf("-----\n");
       return 1;
   }
