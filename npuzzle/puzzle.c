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
#include "../util/debug.h"




struct MyOpt {
int alg;         // Qual Euristica
int chamadas;	//limite de chamadas
char *fileA ;    // arquivo Matriz A (Puzzle)
char *fileB ;    // arquivo Matriz B (Result)
int limite;
} MyOpt;

void mostra_uso(char *name){
    printf("%s: parametros errados encontrados\n uso: [ -v # -a arquivo -b arquivo ] | -h \n", name);
}

int main(int argc, char **argv){
int opterr,dim,pos;
int *A,*Mem;

MyOpt.alg  =0;
_VERB =0;
MyOpt.fileA=NULL;
MyOpt.fileB=NULL;
MyOpt.limite= 1024;


/* Processando parametros*/
    opterr = 2;
    int opcao; // Opção passada pelo usuário ao programa.
        while ((opcao = getopt (argc, argv, "l:v:a:b:h")) != -1){
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
                case 'l':
                    //Matriz B
                    MyOpt.limite = atoi(optarg);
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
                        fprintf (stderr, "Opção '-%c' requer parametros\n", optopt);
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
   MaxProf = MyOpt.limite;
   Mem = malloc(sizeof(int) * (dim*dim) * MaxProf);
   pos = 8;
    if(bs_puzzle(dim,A,Mem,&pos,0)){
    	gravaMatInt(MyOpt.fileB,dim,A);
    }

    exit(0);
}
