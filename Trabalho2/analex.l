%{
#include <stdio.h>
#include "tokens.h"
#include "tabsimb.h"
int linha = 1;
%}
dig [0-9]
letra [a-zA-Z_]
%%

"for"	{return FOR;}
"while"	{return WHILE;}
"if"	{return IF;}
"else"	{return ELSE;}
"return" {return RT;}

"int"  {return INT;}
"float"  {return FLOAT;}

"+"   {return '+';}
"-"   {return '-';}
"*"   {return '*';}
"/"   {return '/';}

">="  {return GE;} 	
"<="  {return LE;} 		
">"   {return '>';}
"<"   {return '<';} 	
"=="  {return EQ;}

"and" {return AND;}
"or"  {return OR;}
"!"   {return '!';}

"="   {return '=';}

";"   {return ';';}
","   {return ',';}
"("	  {return '(';}
")"   {return ')';}
"{"	  {return '{';}
"}"   {return '}';}

\"[^"]*\" { return STR; }

{dig}+("."{dig}+)? { return NUM; }

{letra}({letra}|{dig})*  { 
    insere(yytext);  // Insere na tabela de símbolos
    return ID; 
}

[ \t\r] {}
\n	{ linha++; }

.	{ printf("Erro léxico na linha %d - %s\n", linha, yytext); }
%%

#ifndef yywrap
int yywrap() { return 1; }
#endif

void main(int argc, char **argv) {
    int token, i = 1;	
    yyin = fopen(argv[1], "r");
    token = yylex();
    while (token) {
        printf("%d) %d %s\n", i++, token, yytext);
        token = yylex();
    }
    imprime();  // Imprime a tabela de símbolos
}
