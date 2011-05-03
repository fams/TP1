#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "util.h"

struct MyOpt { 
int m; // numero de linhas
int n; // Numero de colunas
char * arquivo; // Nome do Arquivo a ser gerado
int t; //Tipo de instancia a ser gerada
} MyOpt;

int mostra_uso(char *name){
    printf("%s: parametros errados encontrados\n uso: [ -m # -n # -f arquivo  -t #] | -h \n"
            "\t-m Numero de  linhas\n\t-n Numero de colunas\n\t-f nome do arquivo de saida\n\t"
            "-t tipo de instancia:\n\t\t0 Matriz Aleatoria\n\t\t1 Puzzle\n", name);
}

int main(int argc, char **argv){
FILE *fp;
int option,opterr;
int i,j;
MyOpt.m=0;
MyOpt.n=0;
MyOpt.t=0;
MyOpt.arquivo=NULL;

/* Processando parametros*/
    opterr = 4;
    int opcao; // Opção passada pelo usuário ao programa.
        while ((opcao = getopt (argc, argv, "n:m:f:t:h")) != -1){
            switch(opcao){
            case 'm':
                //Numero de linhas
                MyOpt.m = atoi(optarg);
                opterr--;
                break;

            case 'n':
                //Numero de linhas
                MyOpt.n = atoi(optarg);
                opterr--;
                break;
            case 't':
                //Numero de linhas
                MyOpt.t = atoi(optarg);
                opterr--;
                break;
            case 'f':
                //Numero de linhas
                MyOpt.arquivo = optarg;
                opterr--;
                break;
            case 'h':   /* Help */
            case '?':
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

    fp = fopen(MyOpt.arquivo,"w");
    if(fp == NULL){
        printf("Nao foi possivel abrir o arquivo %s\n",MyOpt.arquivo);
    }

    switch(MyOpt.t){
    case 0:{
        /*
        Gerando matriz d MxN com aleatorios entre 65535 e -65535
        A primeira linha vai com as dimensoes do array  no formato MxN
        */
        printf("Gerando Matriz Aleatoria\n");

        //Tamanho da Matriz
        fprintf(fp,"%ix%i\n",MyOpt.m,MyOpt.n);

        char linha[8*MyOpt.n+10];
        char num[8];
        signed int x,s;
        srand(time(NULL));
        *linha='\0';
        for(i=0;i<MyOpt.m;i++){
            for(j=0;j<MyOpt.n;j++){
                x = 2 * (rand() % 65535) - 65535;
                sprintf(num,"%i,",x);
                strcat(linha,num);
            }
            s=strlen(linha);
            linha[s-1]='\n';
            linha[s]='\0';
            fprintf(fp,linha);
            *linha='\0';
        }
    }
    break;
    case 1:{
        printf("Gerando Puzzle\n");
        fprintf(fp,"%ix%i\n",MyOpt.m,MyOpt.n);
        int A[MyOpt.m*MyOpt.n];
        int invalido=1;
        while(invalido){
            //Preenchendo vetor
            for (i=0;i<((MyOpt.m * MyOpt.n)-1);i++){
                A[i] =(i+1);
            }
            //Ultimo elemento vazio (0)
            A[(MyOpt.m*MyOpt.n)-1]=0;
            //Embaralhando
            embaralha(((MyOpt.m*MyOpt.n)-1),A,101);
            invalido=Insoluvel(A,MyOpt.m);
        }
        //Gravando arquivo
        char linha[8*MyOpt.n+10];
        char num[8];
        signed int x,s;
        *linha='\0';
        for(i=0;i<MyOpt.m;i++){
            for(j=0;j<MyOpt.n;j++){
                x = A[(i*MyOpt.m)+j];
                sprintf(num,"%i,",x);
                strcat(linha,num);
            }
            s=strlen(linha);
            linha[s-1]='\n';
            linha[s]='\0';
            fprintf(fp,linha);
            *linha='\0';
        }
    }
        break;
    }
    fclose(fp);
    exit (0);
} 
        
