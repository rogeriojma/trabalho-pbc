#include "estruturasdados.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef LERARQUIVOS_H
#define	LERARQUIVOS_H

void LerTimes(Time * times, FILE * ArquivoDosTimes, int NumeroDeTimes, char * Conferidor);
void LerJogos(Time * times, Jogo * jogos, FILE * ArquivoDosJogos,int NumeroDeTimes, int NumeroDeJogos, char * Conferidor);
void LerApostas(FILE * ArquivoDeApostas, Apostador * apostadores, char * Conferidor, int NumeroDeApostas);

#endif	/* LERARQUIVOS_H */

