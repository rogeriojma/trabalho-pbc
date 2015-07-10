

#include "lerarquivos.h"


void LerTimes(Time * times, FILE * ArquivoDosTimes, int NumeroDeTimes, char * Conferidor){
    int i;
    for (i = 0; i < NumeroDeTimes; i++){
        fscanf(ArquivoDosTimes, "%[^;];", times[i].NomeDoTime);
        fscanf(ArquivoDosTimes, "\n");
        if (!strcmp(times[i].NomeDoTime, "\0")) {
            Conferidor[0] = 'b';
            break;
        }
    }
}
void LerJogos (Time * times, Jogo * jogos, FILE * ArquivoDosJogos, int NumeroDeTimes
, int NumeroDeJogos, char * Conferidor){
    int cont, i, j, k, l;
    char NomeTimeTemp1[50], NomeTimeTemp2[50];
    int NumeroGolsTemp1, NumeroGolsTemp2, FaltasTemp, CartoesAmarelosTemp, 
    CartoesVermelhosTemp;
    for (cont = 0; cont < NumeroDeJogos; cont++) {
        for (i = 0; i < 50; i++) {
            NomeTimeTemp1[i] = '\0';
            NomeTimeTemp2[i] = '\0';
        }
        jogos[cont].Gols = 0;
        NumeroGolsTemp1 = NumeroGolsTemp2 = 0;
        jogos[cont].Faltas = 0;
        jogos[cont].Cartoes = 0;
        
        fscanf(ArquivoDosJogos, "%[^;];", NomeTimeTemp1);
        strcpy(jogos[cont].NomeTimeCasa, NomeTimeTemp1);
        for (i = 0; i < NumeroDeTimes; i++) {
            if (!strcmp(NomeTimeTemp1, "\0")) {
                Conferidor[0] = 'b';
                break;
            }
            if (!strcmp(NomeTimeTemp1, times[i].NomeDoTime)) {
                fscanf(ArquivoDosJogos, "%d;", &NumeroGolsTemp1);
                jogos[cont].Gols = jogos[cont].Gols + NumeroGolsTemp1;
                times[i].GolsMarcados = times[i].GolsMarcados + NumeroGolsTemp1;
                k = i;
                break;
            }
        }//fim do for
        fscanf(ArquivoDosJogos, "%[^;];", NomeTimeTemp2);
        strcpy(jogos[cont].NomeTimeVisitante, NomeTimeTemp2);
        for (j = 0; j < NumeroDeTimes; j++) {
            if (!strcmp(NomeTimeTemp2, times[j].NomeDoTime)) {
                fscanf(ArquivoDosJogos, "%d;", &NumeroGolsTemp2);
                jogos[cont].Gols = jogos[cont].Gols + NumeroGolsTemp2;
                times[j].GolsMarcados = times[j].GolsMarcados + NumeroGolsTemp2;
                l = j;
                break;
            }
        }//fim do for
        times[k].GolsSofridos = times[k].GolsSofridos + NumeroGolsTemp2;
        times[l].GolsSofridos = times[l].GolsSofridos + NumeroGolsTemp1;
        if ((NumeroGolsTemp1 - NumeroGolsTemp2) >= 1) {
            times[k].Pontos = times[k].Pontos + 3;
        }
        else if ((NumeroGolsTemp1 - NumeroGolsTemp2) == 0){
            times[l].Pontos = times[l].Pontos + 1;
            times[k].Pontos = times[k].Pontos + 1;
        }
        else if ((NumeroGolsTemp1 - NumeroGolsTemp2) <= 1){
            times[l].Pontos = times[l].Pontos + 3;
        }
        fscanf(ArquivoDosJogos, "%d;", &FaltasTemp);
        jogos[cont].Faltas = FaltasTemp;
        fscanf(ArquivoDosJogos, "%d;", &CartoesAmarelosTemp);
        fscanf(ArquivoDosJogos, "%d;\n", &CartoesVermelhosTemp);
        jogos[cont].Cartoes = CartoesAmarelosTemp + CartoesVermelhosTemp;
    }
}
void LerApostas(FILE * ArquivoDeApostas, Apostador * apostadores, char * Conferidor,
int NumeroDeApostas ){
    int i;
    for (i = 0; i < NumeroDeApostas; i++) {
    fscanf(ArquivoDeApostas, "%[^;];", apostadores[i].NomeDoApostador);
    fscanf(ArquivoDeApostas, "%[^;];", apostadores[i].NomeTimePrimeiro);
    fscanf(ArquivoDeApostas, "%[^;];", apostadores[i].NomeTimeSegundo);
    fscanf(ArquivoDeApostas, "%[^;];\n", apostadores[i].NomeTimeTerceiro);
    if (!strcmp(apostadores[i].NomeDoApostador, "\0")) {
        Conferidor[0] = 'b';
        break;
    }
    }//fim do for
}