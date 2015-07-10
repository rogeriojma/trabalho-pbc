

#include "escreverarquivos.h"
#include <time.h>
#include <math.h>

void EscreverTabelaCampeonato(FILE * TabelaDoCampeonato, int NumeroDeTimes, Time * time){
    int i, j, k, cont ;
    Time timeTemp;
    for (i = 0; i < NumeroDeTimes; i++) {
        timeTemp.Pontos = -1;
        for (j = i; j < NumeroDeTimes; j++) {
            if (time[j].Pontos > timeTemp.Pontos){
                timeTemp = time[j];
                cont = j;
            }
            else if(time[j].Pontos == timeTemp.Pontos){
                if (time[j].GolsMarcados > timeTemp.GolsMarcados) {
                    timeTemp = time[j];
                    cont = j;
                }
                
                else if(time[j].GolsMarcados == timeTemp.GolsMarcados){
                    if (time[j].GolsSofridos < timeTemp.GolsSofridos){
                        timeTemp = time[j];
                        cont = j;
                    }
                    else if (time[j].GolsSofridos == timeTemp.GolsSofridos){
                        for (k = 0; k < 50; k++) {
                            if ((int)(time[j].NomeDoTime)[k] < (int)
                            (timeTemp.NomeDoTime)[k]) {
                                timeTemp = time[j];
                                cont = j;
                                break;
                            }
                        }
                    }//fim da comparação por nome
                }//fim da comparação por gols sofridos
            }//fim da comparação por gols marcados
        }//fim da comparação por pontos
        //fim da comparação
        time[cont] = time[i];
        time[i] = timeTemp;
        fprintf(TabelaDoCampeonato, "%s;%d;%d;%d;\n", time[i].NomeDoTime, time[i].Pontos,
                time[i].GolsMarcados, time[i].GolsSofridos);
        
    }
}
void PontuarApostadores(FILE * TabelaDoCampeonato, Apostador * apostador, 
        int NumeroDeApostas){
    int i;
    char TimePrimeiro[50], TimeSegundo[50], TimeTerceiro[50];
    //identificando os times dos primeiro, segundo e terceiro lugares
    for (i = 0; i < NumeroDeApostas; i++) {
        apostador[i].PontosDoApostador = 0;
    }
    for (i = 0; i < 50; i++) {
        TimePrimeiro[i] = '\0';
        TimeSegundo[i] = '\0';
        TimeTerceiro[i] = '\0';
    }
    rewind(TabelaDoCampeonato);
    fscanf(TabelaDoCampeonato, "%[^;];", TimePrimeiro);
    fscanf(TabelaDoCampeonato, "%*d;%*d;%*d;\n");
    fscanf(TabelaDoCampeonato, "%[^;];", TimeSegundo);
    fscanf(TabelaDoCampeonato, "%*d;%*d;%*d;\n");
    fscanf(TabelaDoCampeonato, "%[^;];", TimeTerceiro);
    fscanf(TabelaDoCampeonato, "%*d;%*d;%*d;\n");
    fclose(TabelaDoCampeonato);
    
    //pontuando os apostadores
    for (i = 0; i < NumeroDeApostas; i++) {
        if (!strcmp(apostador[i].NomeTimePrimeiro, TimePrimeiro)){
            apostador[i].PontosDoApostador = apostador[i].PontosDoApostador + 3;
        }
        if (!strcmp(apostador[i].NomeTimeSegundo, TimeSegundo)) {
            apostador[i].PontosDoApostador  = apostador[i].PontosDoApostador + 2;
        }
        if(!strcmp(apostador[i].NomeTimeTerceiro, TimeTerceiro)) {
            apostador[i].PontosDoApostador = apostador[i].PontosDoApostador + 1;
        }
    }
    
}
void EscreverTabelaApostas (FILE * TabelaDeApostas, int NumeroDeApostas, 
        Apostador * apostador){
    int i, j, k, l, cont;
    Apostador * apostadoresComNPontos, apostadorComNPontosTemp;
    char caractereTemp[NumeroDeApostas]; //variável auxiliar para armazenar caracteres
    for (j = 0; j < NumeroDeApostas; j++) {
        caractereTemp[j] = 0; //inicializacao
    }
    
    for (j = 6; j >= 0; j--) {
        cont = 0;
        for (i = 0; i < NumeroDeApostas; i++) {
            if (apostador[i].PontosDoApostador == j) {
                cont++;
            }
        }
        apostadoresComNPontos = (Apostador*) malloc(cont*(sizeof(Apostador)));
        for (k = 0; k < cont; k++) {
            for (l = 0; l < NumeroDeApostas; l++) {
                if ((apostador[l].PontosDoApostador == j) && 
                        ((apostador[l].NomeDoApostador)[0] != 126)) {
                    apostadoresComNPontos[k] = apostador[l];
                    (apostador[l].NomeDoApostador)[0] = 126;
                    break;
                    
                }
            }
        }
        for (k = 0; k < cont; k++){
            for (l = k;l < cont; l++){
                if (ComparaOrdemAlfabetica(apostadoresComNPontos[k].NomeDoApostador,
                        apostadoresComNPontos[l].NomeDoApostador) == 1){
                    apostadorComNPontosTemp = apostadoresComNPontos[k];
                    apostadoresComNPontos[k] = apostadoresComNPontos[l];
                    apostadoresComNPontos[l] = apostadorComNPontosTemp;
                    
                }
            }
            fprintf(TabelaDeApostas,"%s;%d;\n", apostadoresComNPontos[k].NomeDoApostador,
                    apostadoresComNPontos[k].PontosDoApostador);
        }
        free(apostadoresComNPontos);
    }
}
void EscreverTabelaEstatisticas(FILE * TabelaDeEstatisticas, Jogo * jogos, 
        int NumeroDeJogos){
    int i, n, j, Gols, Faltas = 0, FaltasTemp, Cartoes = 0, * NumeroDeFaltas;
    float Mediana, Media;
    Jogo jogoTemp;
    NumeroDeFaltas = (int*) malloc(NumeroDeJogos*sizeof(int));
    
    Gols = 0;
    for (i = 0; i < NumeroDeJogos; i++) {
        Gols = Gols + jogos[i].Gols;
    }
    for (i = 0; i < NumeroDeJogos; i++) {
        Faltas = Faltas + jogos[i].Faltas;
    }
    for (i = 0; i < NumeroDeJogos; i++) {
        Cartoes = Cartoes + jogos[i].Cartoes;
    }
    
    jogoTemp.Gols = -1;
    for (i = 0; i < NumeroDeJogos; i++) {
        if (jogos[i].Gols > jogoTemp.Gols) {
            jogoTemp = jogos[i];
        }
        else if (jogos[i].Gols == jogoTemp.Gols){
            if (strcmp(jogoTemp.NomeTimeCasa, jogos[i].NomeTimeCasa) > 0) {
                jogoTemp = jogos[i];
            }
            else if (strcmp(jogoTemp.NomeTimeCasa, jogos[i].NomeTimeCasa) == 0){
                if (strcmp(jogoTemp.NomeTimeVisitante, jogos[i].NomeTimeVisitante) > 0) {
                    jogoTemp = jogos[i];
                }
            }
        }
    }
    
    fprintf(TabelaDeEstatisticas, "%d;\n", Gols);
    fprintf(TabelaDeEstatisticas, "%s;%s;\n", jogoTemp.NomeTimeCasa, 
            jogoTemp.NomeTimeVisitante);
    fprintf(TabelaDeEstatisticas, "%d;\n", Faltas);
    
    //calculando a mediana das faltas
    for (i = 0; i < NumeroDeJogos; i++) {
        NumeroDeFaltas[i] = jogos[i].Faltas;
    }
    n = 0;
    for (i = 0; i < NumeroDeJogos; i++) {
        FaltasTemp = 10000;
        for (j = i; j < NumeroDeJogos; j++) {
            if ((NumeroDeFaltas[j] < NumeroDeFaltas[i]) && (NumeroDeFaltas[j] < 
                    FaltasTemp)){
                FaltasTemp = NumeroDeFaltas[j];
                n = j;
                if (FaltasTemp == 0) {
                    break;
                }
            }
        }
        FaltasTemp = NumeroDeFaltas[i];
        NumeroDeFaltas[i] = NumeroDeFaltas[n];
        NumeroDeFaltas[n] = FaltasTemp;
    }//ordena o numero de faltas de cada jogo em ordem crescente
    
    if ((NumeroDeJogos % 2) == 1) {
        i = (NumeroDeJogos)/2;
        Mediana = (float) NumeroDeFaltas[i];
        fprintf(TabelaDeEstatisticas, "%f;\n", Mediana);
    }
    else if ((NumeroDeJogos % 2) == 0){
        i = (NumeroDeJogos)/2;
        FaltasTemp = NumeroDeFaltas[i];
        i = i + 1;
        Mediana = ((float) FaltasTemp + NumeroDeFaltas[i])/((float)2);
        fprintf(TabelaDeEstatisticas, "%f;\n", Mediana);
    }
    
    fprintf(TabelaDeEstatisticas, "%d;\n", Cartoes);
    Media = ((float) Cartoes)/(float)NumeroDeJogos;
    fprintf(TabelaDeEstatisticas, "%.2f;\n", Media);
    //cálculo do desvio padrão dos cartões
    double * CartoesFloat;
    CartoesFloat = (double *) malloc(NumeroDeJogos*sizeof(double));
    float DesvioPadrao = 0.0;
    for (i = 0; i < NumeroDeJogos; i++) {
        CartoesFloat[i] = (double)jogos[i].Cartoes;
        CartoesFloat[i] = CartoesFloat[i] - Media;
        CartoesFloat[i] = CartoesFloat[i]*CartoesFloat[i];
        DesvioPadrao = DesvioPadrao + CartoesFloat[i];
    }
    
    DesvioPadrao = sqrt((DesvioPadrao)/(double)NumeroDeJogos);
    fprintf(TabelaDeEstatisticas, "%.2lf;\n", DesvioPadrao);
    free(CartoesFloat);
    free(NumeroDeFaltas);
}
void EscreverNovoArquivoJogos(FILE * NovoArquivoJogos, Time * times, int NumeroDeTimes){
    int i, j;
    srand((unsigned)time(NULL));
    fprintf(NovoArquivoJogos, "%d;\n", (NumeroDeTimes)*(NumeroDeTimes - 1));
    for (i = 0; i < NumeroDeTimes; i++) {
        for (j = 0; j < NumeroDeTimes; j++) {
            if (strcmp(times[i].NomeDoTime, times[j].NomeDoTime)) {
                
                fprintf(NovoArquivoJogos, "%s;%d;%s;%d;%d;%d;%d;\n", times[i].NomeDoTime,
                        (rand() % 11), times[j].NomeDoTime, (rand() % 11), (rand() % 31), 
                        (rand() % 6), (rand() % 4));
            }
        }
    }
    
}