%{
 	/*
	 * Nombre: Ignacio Vargas Ocampo
   * Carne: B47395
   * Archivo: lexer.l
	 */

  #include <iostream>
	#include <string>
	#include "nodos.h"
  #include "parser.tab.h"

	using namespace std;
%}
%option noyywrap yylineno
/* Números positivos */
NUM 	[1-5]

/* Identificadores alfanuméricos */
IDALFA	[a-zA-Z_]+


%%
"imprimir" {
          		yylval.hilera = new string(yytext,yyleng);
          		return t_IMPRIMIR;

	         }

{IDALFA}+ {
              yylval.hilera = new string(yytext,yyleng);
    		      return t_ID;
   	        }

{NUM} {
              yylval.valores = atoi(yytext);
      		    return t_NUMPOS;
 	      }

"=" {

		          return t_IGUAL;
	  }

"("	{

		          return t_PARENTIZ;
    }

")"	{

		          return t_PARENTDE;
	  }

":"	{

		          return t_DOSPUNTOS;
	  }

";"	{

		          return t_PUNTOCOMA;
	  }

","	{

		          return t_COMA;
	  }

[ \t\n]	;
.	{
		/* Para todos los demás lexemas no clasificados */
        yylval.error = yytext;
		    return t_error_lexico;
	}
%%
