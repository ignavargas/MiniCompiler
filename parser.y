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

    NodoAsignacion * asign;

    NodoVarLocal * varLocal;

    NodoExpresion * expr;
    NodoIdentificador * ident;
    NodoEstructuraControl * EstrucCont;

    NodoDeclaracionFunc * declFunc;

    std::vector<NodoInstruccion*> * listaNI;
    std::vector<NodoDeclaracion*> * listaND;
    parNI_NDV* declaFor;

		std::vector< std::vector< NodoInstruccion* >* >* valArray;
*/

}
%error-verbose
%type <valores> t_NUMPOS t_NUMNEG
%type <hilera> t_ID t_ENTERO t_IMPRIMIR
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

%type <listaND> param
%type <instr> iniciar_programa declaration_line_ent declaration_line_str declaration_line_bll
%type <instr> id_init estruc_control
%type <instr> llamado_funcion expr_impr
%type <EstrucCont> tipo_if pero_si sino tipo_for tipo_while
%type <instr> exp_cambio limite_for

*/


%token t_ID
%token t_PARENTIZ "(" t_PARENTDE ")"
%token t_ENTERO "entero"
%token t_IMPRIMIR "imprimir"
%token t_IGUAL "="
%token t_DOSPUNTOS ":"
%token t_PUNTOCOMA ";"
%token t_COMA ","
%token t_NUMPOS "Numero(+)" t_NUMNEG "Numero(-)"
%token t_error_lexico
%%

program: method_call print_statements{cout<<"whole program"<<endl;}
         ;

method_call: declaration_list t_IGUAL t_ID t_PARENTIZ t_NUMPOS t_PARENTDE t_PUNTOCOMA{cout<<"method call"<<endl;}
             ;

declaration_list: t_ID{cout<<"variable[]"; cout<< *$1<< endl;}
                  |t_ID t_COMA declaration_list{cout<<"variable{}"<<endl;}
                  ;

print_statements: t_IMPRIMIR t_DOSPUNTOS t_ID t_PUNTOCOMA{cout<<"Print"<<endl;}
                  |t_IMPRIMIR t_DOSPUNTOS t_ID t_PUNTOCOMA print_statements{cout<<"Print"<<endl;}
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
cout<< "Realizando analisis sintactico y semantico:..."<<endl;

yyparse();


}

void yyerror(const char * s){

	cout<< "ERROR" <<endl;
	cout<< s <<endl;
	cout<<endl;
}
