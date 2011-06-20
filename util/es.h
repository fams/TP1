/*
 * es.h
 *
 *  Created on: 23/04/2011
 *      Author: fams
 */

int carrMatInt(char *filename, int *size, int **Mat);

int gravaMatInt(char *filename, int size, int *Mat);

int carrMatInt2(char *filename, int *Di, int *Dj, int **Mat);

int gravaMatInt2(char *filename, int Di, int Dj, int *Mat);

int mostraMatInt( int size, int *Mat,int ai, int aj);

int mostraMatInt2(int n, int ms,int *Mat, int mi, int mj);

