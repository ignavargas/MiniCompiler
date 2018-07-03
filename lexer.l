%{
 	/*
	 * Nombre: Ignacio Vargas Ocampo
   * Carne: B47395
   * Archivo: lexer.l
	 */

  #include <iostream>
	#include <string>
	//#include "nodos.h"
  //#include "parser.tab.h"

	using namespace std;
%}

%option noyywrap yylineno
/* Números negativos */
NUMN	-[0-9]+

/* Números positivos */
NUMP 	[0-9]

/* Identificadores alfanuméricos */
IDALFA	[a-zA-Z0-9_]+

/*Rango de nuemros para el parametro del metodo */
NUMRANGE [1-5]


%%
"entero"	{
            yylval.hilera = new string(yytext,yyleng);
  		      return t_ENTERO;
	        }

"imprimir" {
          		yylval.hilera = new string(yytext,yyleng);
          		return t_IMPRIMIR;

	         }

"escanear" {
          		yylval.hilera = new string(yytext,yyleng);
          		return t_ESCANEAR;
	         }

  {IDALFA}+ {
              yylval.hilera = new string(yytext,yyleng);
    		      return t_ID;
   	        }

{NUMP}+ {
              yylval.valores = atoi(yytext);
      		    return t_NUMPOS;
 	      }

{NUMN}+ {
              yylval.valores = atoi(yytext);
      		    return t_NUMNEG;
 	      }

{NUMRANGE} {

                yylval.valores = atoi(yyetxt);
                return t_RANGE;
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
