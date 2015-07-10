

#include "escreverlog.h"

void EscreverNoLog(FILE * Arquivo, char * constArquivo){
    fprintf(Arquivo, "%s", constArquivo);
    printf("%s", constArquivo);
}
int EscreverNoLogLeitura(FILE * Arquivo,char *Conferidor, char * constArquivo){
    if (!strcmp(Conferidor, "a")) {
        fprintf(Arquivo, "SUCESSO: A leitura do arquivo %s foi bem sucedida.\n", constArquivo);
        printf("SUCESSO: A leitura do arquivo %s foi bem sucedida.\n", constArquivo);
        return 0;
    }
    else{
        fprintf(Arquivo, "ERRO: A leitura do arquivo %s falhou.\n", constArquivo);
        printf("ERRO: A leitura do arquivo %s falhou.\n", constArquivo);
        return 1;
    }
}
int EscreverNoLogCriacao(FILE * Arquivo,char *Conferidor, char * constArquivo){
    if (!strcmp(Conferidor, "a")) {
        fprintf(Arquivo, "SUCESSO: Criação do arquivo %s foi bem sucedida\n", constArquivo);
        printf("SUCESSO: Criação do arquivo %s foi bem sucedida\n", constArquivo);
        return 0;
    }
    else{
        fprintf(Arquivo, "ERRO: A criação do arquivo %s falhou.\n", constArquivo);
        printf("ERRO: A criação do arquivo %s falhou.\n", constArquivo);
        return 1;
    }
}
int EscreverNoLogEscrita(FILE * Arquivo,char *Conferidor, char * constArquivo){
    if (!strcmp(Conferidor, "a")) {
        fprintf(Arquivo, "SUCESSO: Escrita do arquivo %s foi bem sucedida\n", constArquivo);
        printf("SUCESSO: Escrita do arquivo %s foi bem sucedida\n", constArquivo);
        return 0;
    }
    else{
        fprintf(Arquivo, "ERRO: A escrita do arquivo %s falhou.\n", constArquivo);
        printf("ERRO: A escrita do arquivo %s falhou.\n", constArquivo);
        return 1;
    }
}