/*
 * backtrack.c
 *
 *  Created on: 28/04/2011
 *      Author: fams
 */
int compara(int *A,int  *B, int n){
	int i;
	for (i=0;i<n;i++)
		if(A[i] != B[i])
			return 0;
	return 1;
}


//Testa inviabilidade
int Invalid(int *A, int **Mem, int pos, int n){
	int i;
	for(i=0;i<pos;i++)
		if(compara(A,Mem[i],n))
			return 1;
	return 0;
}

//Move para um estado
void Move(int *A, int **Mem, int x, int *pos){

}
//Volta um estado
void Back(int **Mem, int *pos);

