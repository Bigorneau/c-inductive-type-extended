%{
	#include <stdio.h>
	#include <string.h>
	#include "grammaire.h"
	
	int flag=0;
%}

%option noyywrap 
%option yylineno

TYPE "type"
ID [a-z]+([0-9]|[a-z_])*
CONSTRUCTEUR [A-Z]([a-z_])*
TYPE_ATOMIQUE "int"|"string"|"char"|"float"|"bool"|"array"|"list"|"ref" 
BLANCS [ \t\n]+

%%
{BLANCS}
"/* BEGIN TIC */" {flag=1;}
"/* END TIC */" {flag=0;}
"of" {if (flag) {return OF;} else {}}
"and" {if (flag) {return AND;} else {}}
"=" {if (flag) {return EQ;} else {}}
"*" {if (flag) {return STAR;} else {}}
"|" {if (flag) {return OR;} else {}}
";" {if (flag) {return END;} else {}}
{TYPE_ATOMIQUE} {if (flag) {yylval.str = strdup(yytext); return TYPE_ATOMIQUE;} else {}}
{TYPE} {if (flag) {return TYPE;} else {}}
{ID} {if (flag) {yylval.str = strdup(yytext); return IDENT;} else {}}
{CONSTRUCTEUR} {if (flag) {yylval.str = strdup(yytext); return CONSTRUCTEUR;} else {}}
. {if (flag) {yyerror("erreur d'analyse lexicale");exit(EXIT_FAILURE);} else {}}
%%


