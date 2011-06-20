/*
 * bastao.c
 *
 *  Created on: 12/05/2011
 *      Author: fams
 */



#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "pd.h"
#include "../util/es.h"
#include "../util/debug.h"


struct MyOpt {
char *fileA ;    // matriz com valor das peas
char *fileB ;    // Melhor corte (Result)
int   n;		// Tamanho bastao
} MyOpt;

void mostra_uso(char *name){
    printf("%s: parametros errados encontrados\n uso: [ -v # -a arquivo -b arquivo ] | -h \n", name);
}

int main(int argc, char **argv){
int opterr;
int *A,*B,dimA,dimB,DjA,DiA;


_VERB =0;
MyOpt.fileA=NULL;
MyOpt.fileB=NULL;
MyOpt.n= 10;


/* Processando parametros*/
    opterr = 2;
    int opcao; // Opção passada pelo usuário ao programa.
        while ((opcao = getopt (argc, argv, "n:v:a:b:h")) != -1){
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
                case 'n':
                    //Tamanho n
                    MyOpt.n = atoi(optarg);
                    break;
                case 'v':
                    //Verbosidade
                    _VERB = atoi(optarg);
                    break;
            case '?':
                    switch(optopt){
                        case 'a':
                        case 'b':
                        case 'n':
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
   carrMatInt2(MyOpt.fileA,&DiA, &DjA,&A);


   printf("Processando Bastao\n");
   pdbastao(MyOpt.n,A,DjA);

    //gravaMatInt(MyOpt.fileB,dimB,B);


    exit(0);
}
