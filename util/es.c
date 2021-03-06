#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MATMAX 1024

//Carrega o arquivo da matriz
int carrMatInt(char *filename, int *size, int ***Mat){
FILE *fp;
char buffer[MATMAX];
int  m,n,d, i=0,j=0;
char *elemento, *linha;


//Abrindo arquivo
    fp = fopen(filename, "r");
    if(!fp){
        printf( "Impossivel abrir arquivo %s\n",filename);
        exit(1);
    }
//primeira linha contem a dimensao da matriz
    linha = fgets(buffer, MATMAX, fp);
    if(linha == NULL){
        printf( "Aquivo %s vazio.\n",filename);
        exit(1);
    }
//Obtendo a dimensao
    elemento = strtok ( linha, "x");
    m = atoi(elemento);
    elemento = strtok ( '\0', "x");
    n = atoi(elemento);
    printf("m = %i, n = %i \n",m,n);

//Forcar a matriz quadrada
    if( m > n )
        d = m ;
    else 
        d = n ;

//Carregando a matriz, completando com zeros se nao for quadrada
        *Mat = malloc(sizeof(int **)*d);
    while((fgets(buffer, MATMAX, fp)!=NULL) && i < d){
    	//Alocando a matriz com inteiros
    	(*Mat)[i] = malloc(sizeof(int *)*d);
        elemento = strtok(buffer,",");
        while( elemento  && j < d){
            (*Mat)[i][j] = atoi(elemento);
            elemento = strtok('\0',",");
            j++; 
        }
        //Completando com zeros
        for (;j<d;j++)
              (*Mat)[i][j] = 0;
        j=0;
        i++;
    }
        for (;i<d;i++)
               (*Mat)[i][j] = 0;
        *size = i;
        return 0;
} 
// Salva Matriz em Arquivo
int gravaMatInt(char *filename, int *size, int ***Mat){
    FILE *fp;
    int i=0,j=0;
//Abrindo arquivo
    fp = fopen(filename, "w");
    if(!fp){
        printf( "Impossivel abrir arquivo %s\n",filename);
        exit(1);
    }
    //Gravando aqruivo
    char linha[13*(*size)+10];
    char num[13];
    int s;
    *linha='\0';
    for(i=0;i<(*size);i++){
        for(j=0;j<(*size);j++){
            sprintf(num,"%i,",(*Mat)[i][j]);
            strcat(linha,num); 
        }
        s=strlen(linha);
        linha[s-1]='\n';
        linha[s]='\0';
        fprintf(fp,linha);
        *linha='\0';
    }
    fclose(fp);
    return 1;
}
// Salva Matriz em Arquivo
int mostraMatInt( int size, int ***Mat, int mi, int mj){
    int i=0,j=0;
    //Gravando aqruivo
    char linha[13*size+10];
    char num[13];
    int s;
    *linha='\0';
    for(i=0;i<size;i++){
        for(j=0;j< size;j++){
            sprintf(num,"%i,",(*Mat)[i+mi][j+mj]);
            strcat(linha,num);
        }
        s=strlen(linha);
        linha[s-1]='\n';
        linha[s]='\0';
        printf(linha);
        *linha='\0';
    }
    printf("-----\n");
    return 1;
}

