//
//  contadores.c
//  Projeto PAA
//
//  Created by Fernando Augusto Medeiros Silva on 19/03/11.
//  Copyright 2011 Linuxplace. All rights reserved.
//
#include <time.h>
#include <stdio.h>
#include "contadores.h"

//Inicia Contador de tempo
void _TIni(){
    __CONTADOR.T0 = time(NULL);
}
//Para Contador de tempo
void _TFim(){
    __CONTADOR.T1 = time(NULL);
}
//Incrementa contador de atribuicoes
void _Atb(){
    __CONTADOR.atribuicoes++;
}
//Incrementa contador de atribuicoes
void _Atb2(int i){
    __CONTADOR.atribuicoes +=i;
}
//Incrementa contador de Movimentacoes
void _Mov(){
    __CONTADOR.movimentacoes++;
}
//Incrementa contador de Comparacoes
void _Cmp(){
    __CONTADOR.comparacoes++;
}
//Obtem Tempo Executado
time_t _TExec(){
    return difftime(__CONTADOR.T1,__CONTADOR.T0);
}
//Limpa Contadores
void _LCont(){
    __CONTADOR.T0 = 0;
    __CONTADOR.T1 = 0;
    __CONTADOR.movimentacoes = 0;
    __CONTADOR.atribuicoes = 0;
    __CONTADOR.comparacoes = 0;
}
void _ImpCont(){
    //printf("%ld,\t%i,\t%i,\t%i\n",_TExec(),__CONTADOR.movimentacoes,__CONTADOR.comparacoes,__CONTADOR.atribuicoes);
    printf("%ld,\t%lu,\t%lu\n",_TExec(),__CONTADOR.comparacoes,__CONTADOR.atribuicoes);

}