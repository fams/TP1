/*
 * guloso.c
 *
 *  Created on: 22/05/2011
 *      Author: fams
 */
/*
 * bastao.c
 *
 *  Created on: 12/05/2011
 *      Author: fams
 */



#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "greedy.h"
#include "../util/es.h"
#include "../util/debug.h"
#define m(mat,size,i,j) mat[(size*i)+j]



struct MyOpt {
char *fileA ;    // matriz com items x custo
char *fileB ;    // Mochila Carregada
int   capacidade;		// Tamanho da mochila
int   abordagem;  //Abordagem a ser considerada
} MyOpt;

void mostra_uso(char *name){
    printf("%s: parametros errados encontrados\n uso: [ -v # -a arquivo -b arquivo ] | -h \n", name);
}

int main(int argc, char **argv){
int opterr;
int *A,*B,DiA, DjA, DiB, DjB, i;
int butim; //Quanto a mochila levou


_VERB =0;
MyOpt.fileA=NULL;
MyOpt.fileB=NULL;
MyOpt.capacidade = 0;
MyOpt.abordagem  = 0;



/* Processando parametros*/
    opterr = 2;
    int opcao; // Opção passada pelo usuário ao programa.
        while ((opcao = getopt (argc, argv, "c:v:a:b:t:h")) != -1){
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
                    //Tamanho da mochila
                    MyOpt.capacidade = atoi(optarg);
                    break;
                case 't':
                    //Abordagem da mochila
                    MyOpt.abordagem = atoi(optarg);
                    break;
                case 'v':
                    //Verbosidade
                    _VERB = atoi(optarg);
                    break;
            case '?':
                    switch(optopt){
                        case 'a':
                        case 'b':
                        case 'c':
                        case 't':
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
    //Carregando Matriz Com os items do arquivo
    verb2p(printf("Carregando arquivo\n"),1);
   carrMatInt2(MyOpt.fileA,&DiA, &DjA, &A);


   //Criando tabela com os items
   titem tabela[DiA];
   for (i=0;i<DiA;i++){
		tabela[i].codigo = m(A,DjA,i,0);
		tabela[i].valor  = m(A,DjA,i,1);
		tabela[i].peso   = m(A,DjA,i,2);
	}
   //Alocando espao para a mochila
   titem mochila[DiA];
   //Items Guardados na mochila
   int itensmochila;

   printf("Carregando Mochila\n");
   butim = gdmochila(tabela,DiA, MyOpt.capacidade, MyOpt.abordagem, mochila, &itensmochila);
   printf("butim: %i\n",butim);
   //Gerando arquivo saida
   B = malloc(DjA*i * sizeof(int));
   for (i=0;i<itensmochila;i++){
	    m(B,DjA,i,0) = mochila[i].codigo;
		m(B,DjA,i,1) = mochila[i].valor ;
		m(B,DjA,i,2) = mochila[i].peso  ;
	}
   gravaMatInt2(MyOpt.fileB,itensmochila,DjA,B);


    exit(0);
}

