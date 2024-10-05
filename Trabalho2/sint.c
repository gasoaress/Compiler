#include "analex.h"
#include "pilha.h"
int token, index = 0, indexAux = 0, tkValAux = 0;
char arrayPosfixo[MAX], arrayInit[MAX];

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
    switch (token)
    {
    case '+':
        consome('+');
        T();
        // printf("+");
        a = pop();
        b = pop();
        push(b + a);
        arrayPosfixo[index] = '+';
        index++;
        arrayPosfixo[index] = ' ';
        index++;
        E_linha();
        break;
    case '-':
        consome('-');
        T();
        // printf("-");
        a = pop();
        b = pop();
        push(b - a);
        arrayPosfixo[index] = '-';
        index++;
        arrayPosfixo[index] = ' ';
        index++;
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
    switch (token)
    {
    case '*':
        consome('*');
        F();
        // printf("*");
        a = pop();
        b = pop();
        push(b * a);
        arrayPosfixo[index] = '*';
        index++;
        arrayPosfixo[index] = ' ';
        index++;
        T_linha();
        break;
    case '/':
        consome('/');
        F();
        // printf("/");
        a = pop();
        b = pop();
        push(b / a);
        arrayPosfixo[index] = '/';
        index++;
        arrayPosfixo[index] = ' ';
        index++;
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
        indexAux = 0;
        tkValAux = tokenval;
        consome(NUM);
        push(tokenval);

        while (tkValAux != 0)
        {
            int resto = tkValAux % 10;
            //printf("\nresto %d\n", resto);
            arrayInit[indexAux] = resto + '0';
            indexAux++;
            tkValAux = tkValAux / 10;
        }

        indexAux--;
        //printf("\n array posfixo %s", arrayInit);
        while (indexAux >= 0)
        {
            arrayPosfixo[index] = arrayInit[indexAux];
            index++;
            indexAux--;
        }

        arrayPosfixo[index] = ' ';
        index++;

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
        printf("NOTACAO POSFIXA: %s \n", arrayPosfixo);
        printf("RESULTADO DA EXPRESSAO: %d\n", pop());
    }

    else
        erro_sint();
    return 0;
}
