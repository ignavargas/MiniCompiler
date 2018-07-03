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

%%
"entero"	{
            yylval.hilera = new string(yytext,yyleng);
  		      return t_entero;
	        }

"imprimir" {
          		yylval.hilera = new string(yytext,yyleng);
          		return t_imprimir;

	         }

"escanear" {
          		yylval.hilera = new string(yytext,yyleng);
          		return t_escanear;
	         }

  {IDALFA}+ {
              yylval.hilera = new string(yytext,yyleng);
    		      return t_id;
   	        }

{NUMP}+ {
              yylval.valores = atoi(yytext);
      		    return t_num_pos;
 	      }

{NUMN}+ {
              yylval.valores = atoi(yytext);
      		    return t_num_neg;
 	      }

"=" {

		          return t_igual_a;
	  }

"("	{

		          return t_parent_iz;
    }

")"	{

		          return t_parent_de;
	  }

":"	{

		          return t_dos_puntos;
	  }

";"	{

		          return t_punto_coma;
	  }

","	{

		          return t_coma;
	  }

[ \t\n]	;
.	{
		/* Para todos los demás lexemas no clasificados */
        yylval.error = yytext;
		    return t_error_lexico;
	}
%%
