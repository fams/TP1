#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "matriz.h"
#include "../util/es.h"
#include "../util/debug.h"


struct MyOpt { 
int alg;         // Qual algoritimo usar strassen ou padrao
char *fileA ;    // arquivo Matriz A (fator)
char *fileB ;    // arquivo Matriz B (fator)
char *fileC ;    // arquivo Matriz C (produto)
} MyOpt;

void mostra_uso(char *name){
    printf("%s: parametros errados encontrados\n uso: [ -s -v # -a arquivo -b arquivo -c arquivo ] | -h \n", name);
}

int main(int argc, char **argv){
int opterr,dim;
int *A,*B,*C;

MyOpt.alg  =0;
_VERB =0;
MyOpt.fileA=NULL;
MyOpt.fileB=NULL;
MyOpt.fileC=NULL;

/* Processando parametros*/
    opterr = 3;
    int opcao; // Opção passada pelo usuário ao programa.
        while ((opcao = getopt (argc, argv, "v:sa:b:c:h")) != -1){
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

                case 'c':
                    //Matriz C
                    MyOpt.fileC = optarg;
                    opterr--;
                    break;

                case 'v':
                    //Verbosidade
                    _VERB = atoi(optarg);
                    break;

                case 's':
                    MyOpt.alg = 1;
                    break;

                case '?':
                    switch(optopt){
                        case 'a':
                        case 'b':
                        case 'c':
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
    //Carregando Matriz B do arquivo
    carrMatInt(MyOpt.fileB,&dim, &B);

    if(MyOpt.alg){
        printf("Strassen\n");
        C = matriz_multi_strass(dim,A,0,0,B,0,0);
    }else{
        C = matriz_multi(dim,A,B);
    }
    gravaMatInt(MyOpt.fileC,&dim,C);

    exit(0);
} 
