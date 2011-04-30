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
//Volta um estado
void Back(int **Mem, int *pos);


