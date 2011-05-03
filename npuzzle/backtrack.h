/*
 * backtrack.h
 *
 *  Created on: 28/04/2011
 *      Author: fams
 */

//Testa inviabilidade
int Invalid(int *A, int **Mem);
//Move para um estado
void Move(int *A, int **Mem, int *pos);
//Executa
int bs_puzzle(int n, int *A, int *Mem, int *p,int pos);
//Mostra passos executados
void mostraPassos(int *M, int pos, int n);
//limite de busca
int MaxProf;


