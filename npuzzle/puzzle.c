/*
 * puzzle.c
 *
 *  Created on: 27/04/2011
 *      Author: fams
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "backtrack.h"
#include "../util/es.h"
#include "../debug.h"

int calculo_distancia(int n,int i, int j, int v){
	int io, jo;
	io= v / n;
	jo= v % n;
	return (jo>j?(jo-jo):(jo-jo))+(io>i?(io-io):(io-io));
}


struct MyOpt {
int alg;         // Qual Euristica
int chamadas;	//limite de chamadas
char *fileA ;    // arquivo Matriz A (Puzzle)
char *fileB ;    // arquivo Matriz B (Result)
} MyOpt;

void mostra_uso(char *name){
    printf("%s: parametros errados encontrados\n uso: [ -v # -a arquivo -b arquivo ] | -h \n", name);
}

int main(int argc, char **argv){
int opterr,dim;
int **A,**B;

MyOpt.alg  =0;
_VERB =0;
MyOpt.fileA=NULL;
MyOpt.fileB=NULL;


/* Processando parametros*/
    opterr = 3;
    int opcao; // Op��o passada pelo usu�rio ao programa.
        while ((opcao = getopt (argc, argv, "a:b:h")) != -1){
                switch(opcao){
                case 'a':
                    //Matriz A
                    MyOpt.fileA = optarg;
                    opterr--;
                    break;

                case 'b':
                    //Matriz B
                    MyOpt.fileB = optarg;
                    opterr--;
                    break;
                case 'v':
                    //Verbosidade
                    _VERB = atoi(optarg);
                    break;
            case '?':
                    switch(optopt){
                        case 'a':
                        case 'b':
                        case 'v':
                        fprintf (stderr, "Op��o '-%c' requer parametros\n", optopt);
                    break;
                    }
            case 'h':   /* Help */
                mostra_uso(argv[0]);
                exit(1);
                break;
            default:
                /* Nao para aqui */
                break;

                }
    }
    if(opterr>0){
        mostra_uso(argv[0]);
        exit(1);
    }
    //Carregando Matriz A do arquivo
    carrMatInt(MyOpt.fileA,&dim, &A);


   printf("Processando Puzzle\n");
    B = Puzzle(dim,&A);

    gravaMatInt(MyOpt.fileB,&dim,&B);

    exit(0);
}
