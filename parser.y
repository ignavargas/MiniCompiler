%{


	#include <iostream>
	#include <ostream>
	#include <string>
	#include <cstring>
	#include <fstream>
	#include <cstdlib>
	#include "nodos.h"

	using namespace std;
	int yylex();
	void yyerror(const char * s);

	Nodo* programa;

	extern FILE *yyin;
  extern int yylineno;

%}

%union{

    char* error;
    string* hilera;
    int valores;
    Nodo* nodo;
		pair<string, int>* par;
		vector<string>* listaDec;
		vector<string>* print;

}
%error-verbose
%type <valores> t_NUMPOS
%type <hilera> t_ID t_IMPRIMIR
%type <errores> t_error_lexico

/** seccion para dar tipos a los no terminales de la gramatica **/

%type <nodo> program
%type <listaDec> declaration_list
%type <par> method
%type <print> print_statements

%token t_ID
%token t_PARENTIZ "(" t_PARENTDE ")"
%token t_IMPRIMIR "imprimir"
%token t_IGUAL "="
%token t_DOSPUNTOS ":"
%token t_PUNTOCOMA ";"
%token t_COMA ","
%token t_NUMPOS "Numero(+) : 1<= x <= 5"
%token t_error_lexico
%%

program: declaration_list t_IGUAL method print_statements{$$ = new Nodo; $$->listaDeclaracion = *$1; $$->funcion = *$3;$$->printValores = *$4;delete $4;delete $1; delete $3;programa = $$;}
         ;

method: t_ID t_PARENTIZ t_NUMPOS t_PARENTDE t_PUNTOCOMA{$$ = new pair<string, int>; $$->first = *$1; $$->second = $3; delete $1;}
				;

declaration_list: t_ID{$$ = new vector<string>; $$->push_back(*$1); delete $1;}
                  |declaration_list t_COMA t_ID{$1->push_back(*$3); delete $3;}
                  ;

print_statements: t_IMPRIMIR t_DOSPUNTOS t_ID t_PUNTOCOMA{$$ = new vector<string>; $$->push_back(*$3);delete $3;}
                  |print_statements t_IMPRIMIR t_DOSPUNTOS t_ID t_PUNTOCOMA {$1->push_back(*$4); delete $4;}
                  ;


%%
int main(int argc, char **argv){
	++argv, --argc;
	if ( argc > 0 )
		yyin = fopen( argv[0], "r" );
	else
		yyin = stdin;


	cout<<endl;
	cout<<"___________________________________________________________"<<endl;
	cout<<endl;
	cout<< "****** Mini Compilador NACH - Examen Final ****************"<<endl;
	cout<< "Realizando analisis sintactico:..."<<endl;

	yyparse();

	cout<<"sintaxis correcto!"<<endl;
	cout<< "Realizando analisis semantico:..."<<endl;
	if(programa->guardarDatos()){

		if(programa->analisisSemantico()){

			cout<<"el analisis semantico se realizo con exito!"<<endl;
			cout<<"generando codigo..."<<endl;
			programa->codeGen();
			cout<< "codigo generado en asam_code.txt"<<endl;
		}else{

			cout<<"... terminando...."<<endl;
		}
	}else{

		cout<<"ERROR: cantidad de par�metros asignados no coincide... \nterminando..."<<endl;
	}
}
void yyerror(const char * s){

	cout<< "ERROR" <<endl;
	cout<< s <<endl;
	cout<<endl;
}
