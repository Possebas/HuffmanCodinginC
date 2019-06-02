#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char entrada[] = "aaaaabbbbcccdde";
    int* numberChars = calloc(255, sizeof numberChars);

    printf("Caracteres da mensagem em decimal:\n");
    for(int i=0; i<strlen(entrada); i++){
        printf(" [%d] ", entrada[i]);
        numberChars[(int)entrada[i]] += 1;
    }
    //printf("\n\nVezes que cada caractere apareceu:\n");
    /*
    for(int i=0; i<255; i++){
        if(numberChars[i] > 0){
        printf(" [%d] ", numberChars[i]);
        }
    }
    */
    printf("\n\n");
    printf("Caractere em ASCII          Quantidade");
    for(int i=0;i<256;i++){
        if(numberChars[i] > 0){
            printf("\n%c                              %d\n", i, numberChars[i]);
        }
    }

    //printf("\nHello world!\n");
    return 0;
}
