#include "estruturasdados.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef ESCREVERARQUIVOS_H
#define	ESCREVERARQUIVOS_H

void EscreverTabelaCampeonato(FILE * TabelaDoCampeonato, int NumeroDeTimes, Time * time);
void PontuarApostadores(FILE * TabelaDoCampeonato, Apostador * apostador, int NumeroDeApostas);
void EscreverTabelaApostas (FILE * TabelaDeApostas, int NumeroDeApostas, Apostador * apostador);
void EscreverTabelaEstatisticas(FILE * TabelaDeEstatisticas, Jogo * jogos, int NumeroDeJogos);
void EscreverNovoArquivoJogos(FILE * NovoArquivoJogos, Time * times, int NumeroDeTimes);

#endif	/* ESCREVERARQUIVOS_H */

