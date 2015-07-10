/*
 UFES
 Centro Tecnológico
 Trabalho Prático de Programação Básica de Computadores (INF09325)
 Prof. Thiago Oliveira dos Santos
 Aluno: Rogerio José Menezes Alves
 Engenharia Elétrica 2013/2
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "escreverlog.h"
#include "lerarquivos.h"
#include "escreverarquivos.h"
#include "funcoesstring.h"
#include "estruturasdados.h"



int main(int argc, char *argv[]){
    //variáveis
    FILE *ArquivoLog;
    FILE *ArquivoTimes;
    FILE *ArquivoJogos;
    FILE *ArquivoApostas;
    FILE *TabelaDoCampeonato;
    FILE *TabelaDeApostas;
    FILE *TabelaDeEstatisticas;
    char DiretorioTimes[1000];
    char DiretorioLog[1000];
    char DiretorioJogos[1000];
    char DiretorioApostas[1000];
    char DiretorioTabela[1000];
    char DiretorioTabelaApostas[1000];
    char DiretorioEstatisticas[1000];
    char Conferidor[50] = "a";
    int NumeroDeTimes = 0;
    int i;//contador
    int NumeroDeJogos = 0;
    int NumeroDeApostas;
    Time *times;
    Apostador *apostador;
    Jogo *jogo;
    
    
    if (argc == 1){
        //informa o erro na leitura do diretorio
        printf("ERRO: O diretório de arquivos não foi informado!\n");
        
    }
    else if (argc == 2){
        
        
        //criação e relatório do arquivo de log
        ConcatenaString(argv[1], "/log.txt", DiretorioLog);
        ArquivoLog = fopen(DiretorioLog, "w");
        EscreverNoLog(ArquivoLog,"SUCESSO: Leitura do diretório feita com sucesso\n");
 
        //leitura do arquivo de times
        EscreverNoLog(ArquivoLog, "EXECUTANDO: Leitura do arquivo times.txt\n");
        ConcatenaString(argv[1], "/times.txt", DiretorioTimes);
        ArquivoTimes = fopen(DiretorioTimes, "r");
        fscanf(ArquivoTimes, "%d;\n", &NumeroDeTimes);
        times = (Time*) malloc(NumeroDeTimes*sizeof(Time));
        
        LerTimes(times, ArquivoTimes, NumeroDeTimes, Conferidor);
        
        fscanf(ArquivoTimes, "%[^;];\n", Conferidor);
        i = EscreverNoLogLeitura(ArquivoLog, Conferidor, DiretorioTimes);
        if (i == 1){
            return 1;
        }
        
        fclose(ArquivoTimes);
        //fim da leitura de times.txt
        
        //inicialização das estatísticas dos times
        for (i = 0; i < NumeroDeTimes; i++) {
            times[i].Pontos = times[i].GolsMarcados = times[i].GolsSofridos = 0;
        }
        
        //leitura do arquivo de jogos
        EscreverNoLog(ArquivoLog, "EXECUTANDO: Leitura do arquivo jogos.txt\n");
        ConcatenaString(argv[1], "/jogos.txt", DiretorioJogos);
        for (i = ((int)strlen(argv[1]) + 10); i < 1000; i++) {
            DiretorioJogos[i] = '\0';
        }
        ArquivoJogos = fopen(DiretorioJogos, "r");
        fscanf(ArquivoJogos, "%d;\n", &NumeroDeJogos);
        jogo = (Jogo *) malloc(NumeroDeJogos*sizeof(Jogo));
        
        LerJogos (times, jogo, ArquivoJogos, NumeroDeTimes, NumeroDeJogos, Conferidor);
        
        fscanf(ArquivoJogos, "%s", Conferidor);
        
        i = EscreverNoLogLeitura(ArquivoLog, Conferidor, DiretorioJogos);
        if (i == 1){
            return 2;
        }
        
        fclose(ArquivoJogos);
        //fim da leitura de jogos.txt
        
        //leitura do arquivo de apostas
        fprintf(ArquivoLog, "EXECUTANDO: Leitura do arquivo apostas.txt\n");
        printf("EXECUTANDO: Leitura do arquivo apostas.txt\n");
        ConcatenaString(argv[1], "/apostas.txt", DiretorioApostas);
        for (i = ((int)strlen(argv[1]) + 12); i < 100; i++) {
            DiretorioApostas[i] = '\0';
        }
        ArquivoApostas = fopen(DiretorioApostas, "r");
        fscanf(ArquivoApostas, "%d;\n", &NumeroDeApostas);
        apostador = (Apostador*) malloc(NumeroDeApostas*sizeof(Apostador));
        
        LerApostas (ArquivoApostas, apostador, Conferidor, NumeroDeApostas);

        fscanf(ArquivoApostas, "%[^;];", Conferidor);
        
        i = EscreverNoLogLeitura (ArquivoLog, Conferidor, DiretorioApostas);
        if (i == 1){
            return 3;
        }
        
        fclose(ArquivoApostas);
        //fim da leitura de apostas.txt
        
        
        //comparando os times e gerando a tabela do campeonato
        EscreverNoLog(ArquivoLog, "EXECUTANDO: Escrita do arquivo tabelacampeonato.txt\n");
        
        ConcatenaString(argv[1], "/tabelacampeonato.txt", DiretorioTabela);
        for (i = ((int)strlen(argv[1]) + 21); i < 1000; i++) {
            DiretorioTabela[i] = '\0';
        }
        TabelaDoCampeonato = fopen(DiretorioTabela, "w+");
        fscanf(TabelaDoCampeonato, "%s", Conferidor);
        i = EscreverNoLogCriacao(ArquivoLog, Conferidor, "tabelacampeonato.txt");
        if (i == 1){
            return 4;
        }
        
        EscreverTabelaCampeonato(TabelaDoCampeonato, NumeroDeTimes, times);

        fscanf(TabelaDoCampeonato, "%[^;];", Conferidor);
        i = EscreverNoLogEscrita(ArquivoLog, Conferidor, "tabelacampeonato.txt");
        if (i == 1){
            return 5;
        }

        PontuarApostadores(TabelaDoCampeonato, apostador, NumeroDeApostas);
        
        //comparando os apostadores e gerando o arquivo da tabela de apostas
        EscreverNoLog(ArquivoLog,"EXECUTANDO: Escrita do arquivo tabelaapostas.txt\n" );
        ConcatenaString(argv[1], "/tabelaapostas.txt", DiretorioTabelaApostas);
        for (i = ((int)strlen(argv[1]) + 18); i < 1000; i++) {
            DiretorioTabelaApostas[i] = '\0';
        }
        
        TabelaDeApostas = fopen(DiretorioTabelaApostas, "w");
        fscanf(TabelaDeApostas, "%s", Conferidor);
        i = EscreverNoLogCriacao(ArquivoLog, Conferidor, "tabelaapostas.txt");
        if (i == 1){
            return 6;
        }
        
        EscreverTabelaApostas (TabelaDeApostas, NumeroDeApostas, apostador);
        
        fscanf(TabelaDeApostas, "%s", Conferidor);
        i = EscreverNoLogEscrita(ArquivoLog, Conferidor, "tabelaapostas.txt");
        if (i == 1){
            return 7;
        }
        fclose(TabelaDeApostas);
        
        //gerando tabela de estatísticas
        EscreverNoLog(ArquivoLog,"EXECUTANDO: Escrita do arquivo tabelaestatisticas.txt\n" );
        
        ConcatenaString(argv[1], "/tabelaestatisticas.txt", DiretorioEstatisticas);
        for (i = ((int)strlen(argv[1]) + 23); i < 1000; i++) {
            DiretorioEstatisticas[i] = '\0';
        }

        TabelaDeEstatisticas = fopen(DiretorioEstatisticas, "w");
        
        fscanf(TabelaDeEstatisticas, "%s", Conferidor);
        i = EscreverNoLogCriacao(ArquivoLog, Conferidor, "tabelaestatisticas.txt");
        if (i == 1){
            return 8;
        }
        
        
        //escrevendo na tabela de estatisticas
        
        EscreverTabelaEstatisticas(TabelaDeEstatisticas, jogo, NumeroDeJogos);
        
        fscanf(TabelaDeEstatisticas, "%[^;];", Conferidor);
        i = EscreverNoLogCriacao(ArquivoLog, Conferidor, "tabelaestatisticas.txt");
        if (i == 1){
            return 9;
        }
        fclose(TabelaDeEstatisticas);

    }//fim do else
    else if (argc == 3){
        //criação e relatório do log
        ConcatenaString(argv[1], "/log.txt", DiretorioLog);
        ArquivoLog = fopen(DiretorioLog, "w");
        EscreverNoLog(ArquivoLog,"SUCESSO: Leitura do diretório feita com sucesso\n");
        
        //leitura do arquivo de times
        EscreverNoLog(ArquivoLog, "EXECUTANDO: Leitura do arquivo times.txt\n");
        ConcatenaString(argv[1], "/times.txt", DiretorioTimes);
        ArquivoTimes = fopen(DiretorioTimes, "r");
        fscanf(ArquivoTimes, "%d;\n", &NumeroDeTimes);
        times = (Time*) malloc(NumeroDeTimes*sizeof(Time));
        
        LerTimes(times, ArquivoTimes, NumeroDeTimes, Conferidor);
        
        fscanf(ArquivoTimes, "%[^;];\n", Conferidor);
        i = EscreverNoLogLeitura(ArquivoLog, Conferidor, DiretorioTimes);
        if (i == 1){
            return 10;
        }
        
        fclose(ArquivoTimes);
        //fim da leitura de times.txt
        
        //criacao do novo arquivo de jogos
        FILE * NovoArquivoJogos;
        char DiretorioNovoJogos[1000];
        char DiretorioTemp[1000];
        EscreverNoLog(ArquivoLog, "EXECUTANDO: Escrita do novo arquivo de jogos\n");
        ConcatenaString("/", argv[2], DiretorioTemp);
        ConcatenaString(argv[1], DiretorioTemp, DiretorioNovoJogos);
        NovoArquivoJogos = fopen(DiretorioNovoJogos, "w");
        
        EscreverNovoArquivoJogos(NovoArquivoJogos, times, NumeroDeTimes);
        
        fscanf(NovoArquivoJogos, "%[^;];\n", Conferidor);
        i = EscreverNoLogCriacao(ArquivoLog, Conferidor, argv[2]);
        if (i == 1){
            return 11;
        }
        
        
        fclose(NovoArquivoJogos);
    }
    
   
    free(jogo);
    free(times);
    free(apostador);
}//fim da main