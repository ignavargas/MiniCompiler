%{


	#include <iostream>
	#include <ostream>
	#include <string>
	#include <cstring>
	#include <fstream>
	#include <cstdlib>
	//#include "nodos.h"

	using namespace std;
	int yylex();
	void yyerror(const char * s);

	//NodoControlador* programa;

	extern FILE *yyin;
  extern int yylineno;

%}

%union{

    char* error;
    string* hilera;
    int valores;

/*
    Nodo * nodo;
    NodoInstruccion * instr;
    NodoControlador * contrl;
    NodoDeclaracion * declaracion;

    NodoVariable * var;
    NodoDeclaracionVar * declVariables;

    NodoVarLocal * varLocal;

    NodoIdentificador * ident;

    NodoDeclaracionFunc * declFunc;

    std::vector<NodoInstruccion*> * listaNI;
    std::vector<NodoDeclaracion*> * listaND;
    parNI_NDV* declaFor;

		std::vector< std::vector< NodoInstruccion* >* >* valArray;

    */

}
%error-verbose
%type <valores> t_NUMPOS t_NUMNEG t_RANGE expNumeros
%type <hilera> t_ID t_ENTERO t_IMPRIMIR t_ESCANEAR
%type <errores> t_error_lexico

/** seccion para dar tipos a los no terminales de la gramatica **/

/*
%type <instr> exp_matem  idNum
%type <instr> expBooleana expBool simpleExpBool t_parent_iz t_parent_de
%type <instr> exp_Hilera
%type <contrl> program statements

%type <declaracion> tipo_param var_declaration func_declaration blocks
%type <declaFor> declaracion_for

%type <listaNI> declaration_body_ent declaration_body_str declaration_body_bll
%type <listaNI> statements_block lista_elem param_input dim_Array nums
%type <valArray> val_array
*/

/*
%type <listaND> param
%type <instr> iniciar_programa declaration_line_ent declaration_line_str declaration_line_bll
%type <instr> id_init estruc_control
%type <instr> llamado_funcion expr_impr
%type <EstrucCont> tipo_if pero_si sino tipo_for tipo_while
%type <instr> exp_cambio limite_for
*/




%token t_ID
%token t_RANGE
%token t_PARENTIZ "(" t_PARENTDE ")"
%token t_ENTERO "entero"
%token t_IMPRIMIR "imprimir"
%token t_ESCANEAR "escanear"
%token t_DOSPUNTOS ":"
%token t_PUNTOCOMA ";"
%token t_COMA ","
%token t_NUMPOS "Numero(+)" t_NUMNEG "Numero(-)"
%token t_error_lexico

%%
  expNumeros: t_NUMPOS{$$ = $1;}
	          | t_NUMNEG{$$ = $1;}

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
    cout<< "Realizando analisis sintactico y semantico:..."<<endl;
}
