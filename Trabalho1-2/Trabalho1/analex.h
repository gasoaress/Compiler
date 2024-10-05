#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NUM 256

int tokenval, lines = 1;

int analex(){
    char ch;

    ch = getchar();

    while (ch == ' ' || ch == '\t' || ch == '\n') {
        if (ch == '\n')
            lines ++;
        ch = getchar();
    }

    if(ch == '+')
        return '+';

    if(ch == '-')
        return '-';

    if(ch == '*')
        return '*';

    if(ch == '/')
        return '/';

    if(ch == ';')
        return ';';

    if(ch == '(')
        return '(';

    if(ch == ')')
        return ')';

        // SEM GRAÇA. MELHORAR EM CASA
     if(isdigit(ch)) {
        tokenval = 0;
        while(isdigit(ch)) {
            tokenval = tokenval * 10 + (ch - '0'); // Acumula o valor do número
            ch = getchar(); // Lê o próximo caractere
        }
        ungetc(ch, stdin); // CH é jogado na STARD OUTPUT, saída padrao
        return NUM;
    }
    //IH, TEM ESPAÇO. IMPLEMENTAR.
    printf("\nERRO LEXICO NA LINHA %d", lines);
    exit(1);
}
