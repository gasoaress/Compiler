#include "analex.h"
#include "pilha.h"

int token, index = 0;
char arrayPosfixo[MAX];

void E();
void E_linha();
void T();
void T_linha();
void F();

void erro_sint()
{
    printf("\nERRO SINTATICO NA LINHA %d!!", lines);
    exit(1);
}

void consome(int t)
{
    if (token == t)
        token = analex();
    else
        erro_sint();
}

void E()
{
    T();
    E_linha();
}

void E_linha()
{
    int a, b;

    switch (token)
    {
    case '+':
        consome('+');
        T();
        a = pop();
        b = pop();
        push(b + a);
        arrayPosfixo[index++] = '+';
        arrayPosfixo[index++] = ' ';
        E_linha();
        break;
    case '-':
        consome('-');
        T();
        a = pop();
        b = pop();
        push(b - a);
        arrayPosfixo[index++] = '-';
        arrayPosfixo[index++] = ' ';
        E_linha();
        break;
    }
}

void T()
{
    F();
    T_linha();
}

void T_linha()
{
    int a, b;

    switch (token)
    {
    case '*':
        consome('*');
        F();
        a = pop();
        b = pop();
        push(b * a);
        arrayPosfixo[index++] = '*';
        arrayPosfixo[index++] = ' ';
        T_linha();
        break;
    case '/':
        consome('/');
        F();
        a = pop();
        b = pop();
        push(b / a);
        arrayPosfixo[index++] = '/';
        arrayPosfixo[index++] = ' ';
        T_linha();
        break;
    }
}

void F()
{
    switch (token)
    {
    case '(':
        consome('(');
        E();
        consome(')');
        break;
    case NUM:
        consome(NUM);
        push(tokenval);
        /*
         ESCREVE O NUM QUE VEM DE TOKENVAL NO ENDERECO DO ARRAY[INDEX]
         EXEMPLO: SE TOKENVAL == 1000 MINHA SAÍDA SERÁ
         "1000 "
         POR CONTA DE:
         "%d " INDICA QUE O VALOR DE TOKENVAL VAI SER CONVERTIDO PARA STRING E VAI TER UM ESPAÇO EM SEGUIDA
         index += MOVE O INDÍCE PARA A ÚLTIMA POSIÇÃO
        */
        index += sprintf(&arrayPosfixo[index], "%d ", tokenval);
        break;
    default:
        erro_sint();
    }
}

int main()
{
    token = analex();
    E();
    if (token == ';')
    {
        printf("EXPRESSAO CORRETA\n");
        printf("NOTACAO POSFIXA: %s\n", arrayPosfixo);
        printf("RESULTADO DA EXPRESSAO: %d\n", pop());
    }
    else
        erro_sint();

    return 0;
}
