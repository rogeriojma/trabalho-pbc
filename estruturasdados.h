
#ifndef ESTRUTURASDADOS_H
#define	ESTRUTURASDADOS_H

typedef struct TTime{
    char NomeDoTime[50];
    int Pontos;
    int GolsMarcados;
    int GolsSofridos;
}Time;
typedef struct TApostador{
    char NomeDoApostador[100];
    char NomeTimePrimeiro[50];
    char NomeTimeSegundo[50];
    char NomeTimeTerceiro[50];
    int PontosDoApostador;
}Apostador;
typedef struct TJogo{
    char NomeTimeCasa[50];
    char NomeTimeVisitante[50];
    int Gols;
    int Faltas;
    int Cartoes;
}Jogo;

#endif	/* ESTRUTURASDADOS_H */

