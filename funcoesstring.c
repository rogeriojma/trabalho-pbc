

#include "funcoesstring.h"

void ConcatenaString(char *aString1, char *aString2, char *aStringDestino){
    int i = 0;
    while(aString1[i] != '\0'){
        aStringDestino[i] = aString1[i];
        i++;
    }
    int j = 0;
    while(aString2[j] != '\0'){
        aStringDestino[i] = aString2[j];
        i++;
        j++;
    }
}
int ComparaOrdemAlfabetica(char *aString1, char *aString2){
    int i;
    char StringTemp1[100];
    char StringTemp2[100];
    for (i = 0; i < 100; i++){
        if (aString1[i] == '\0') {
            break;
        }
        StringTemp1[i] = aString1[i];
    }
    StringTemp1[i] = '\0';
    for (i = 0; i < 100; i++){
        if (aString2[i] == '\0') {
            break;
        }
        StringTemp2[i] = aString2[i];
    }
    StringTemp2[i] = '\0';
    
    for (i = 0; i < 100; i++) {
        if (StringTemp1[i] == '\0') {
            break;
        }
        if ((StringTemp1[i] >= 97) && (StringTemp1[i] <= 122)) {
            StringTemp1[i] = StringTemp1[i] - 32;
        }
    }
    for (i = 0; i < 100; i++) {
        if (StringTemp2[i] == '\0') {
            break;
        }
        if ((StringTemp2[i] >= 97) && (StringTemp2[i] <= 122)) {
            StringTemp2[i] = StringTemp2[i] - 32;
        }
    }
    i = strcmp(StringTemp1, StringTemp2);
    if (i > 0){
        return 1; //retorna 1 se tiver que mudar
    }
    else{
        return 0; //retorna 0 se ja estiver na ordem
    }
}

