#include "estruturasdados.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef ESCREVERLOG_H
#define	ESCREVERLOG_H

void EscreverNoLog(FILE * Arquivo, char * constArquivo);
int EscreverNoLogLeitura(FILE * Arquivo,char *Conferidor, char * constArquivo);
int EscreverNoLogCriacao(FILE * Arquivo,char *Conferidor, char * constArquivo);
int EscreverNoLogEscrita(FILE * Arquivo,char *Conferidor, char * constArquivo);

#endif	/* ESCREVERLOG_H */

