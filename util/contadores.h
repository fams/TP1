//
//  contadores.h
//  Projeto PAA
//
//  Created by Fernando Augusto Medeiros Silva on 19/03/11.
//  Copyright 2011 Linuxplace. All rights reserved.
//
/*
 * Estrutura contadores
 */
#include <time.h>

struct { unsigned long int  atribuicoes; unsigned long int movimentacoes; time_t T0; time_t T1 ; unsigned long int comparacoes; unsigned long int somas; unsigned long int multiplicacoes; } __CONTADOR;

void _TIni();

void _TFim();

time_t _TExec();

void _Atb();

void _Atb2(int i);

void _Mov();

void _Cmp();

void _Mul();

void _Som();

void _LCont();

void _ImpCont();
