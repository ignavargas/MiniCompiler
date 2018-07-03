#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include "ListaSimbolos.cpp"

using namespace std;

/** Macros para los operadores  **/
#define SUMA 1
#define RESTA 2
#define MULTI 3
#define DIV 4
#define MOD 5
#define AND 6
#define OR 7
#define NEG 8
#define MENOR 9
#define MENOR_IGUAL 10
#define MAYOR 11
#define MAYOR_IGUAL 12
#define DIFERENTE 13
#define IGUAL 14
#define SI 15
#define PERO_SI 16
#define SINO 17
#define PARA 18
#define MIENTRAS 19



class NodoInstruccion;
class NodoDeclaracion;
class NodoIdentificador;
class NodoDeclaracionVar;


typedef vector<NodoDeclaracion*> listaDeclaraciones;
typedef	vector<NodoInstruccion*> dimensionesMatriz;
typedef	vector<vector<NodoInstruccion*>*> matrizValores;
typedef vector<NodoInstruccion*> bloqueInstrucciones;
typedef vector<NodoDeclaracion*> parametrosFuncion;
typedef vector<NodoInstruccion*> listaVar;
typedef vector<NodoInstruccion*> listaLlamadoFun;
typedef NodoIdentificador NID;
typedef std::pair<NodoInstruccion*,NodoDeclaracionVar* > parNI_NDV;

typedef vector<string> ListaHil;
typedef map<string,ListaSimbolos*> TablaSimbolos;
typedef map<string, ListaSimbolos*>::iterator itTabla;


class Nodo {
public:
    virtual void printValores(ListaHil* niveles, int nivel,int numHijo,string padre)
        {
        }
    virtual bool cargarTablaSimbolos(map<string, ListaSimbolos*> *tablaSimbolos){
        return true;
    }
    virtual bool cargarTablaSimbolos(string nombreFuncion, map<string, ListaSimbolos*> *tablaSimbolos){
        return true;
    }
    virtual bool cargarTablaSimbolos(string nombreFuncion, map<string, ListaSimbolos*> *tablaSimbolos, string token){
        return true;
    }
    virtual bool cargarTablaSimbolos(map<string, ListaSimbolos*> *tablaSimbolos, string tipoVar){
        return true;
    }
    // Metodo dentro de NodoControlador y de las declaraciones
    /** método para comparar tipos dentro de NDV **/
    // basura es para diferenciar los métodos
    virtual bool compararTipo(TablaSimbolos* ts, string tipoPadre){}
    virtual bool compararTipo(TablaSimbolos* ts){}
    virtual bool compararTipo(TablaSimbolos* ts, string tipoPadre, string contexto){}
    virtual bool compararTipo(TablaSimbolos* ts, string tipo, string contexto, char basura){}
    virtual bool compararTipo(TablaSimbolos* ts, string contexto, char basura){}
};


class NodoInstruccion: public Nodo
{
    public:
    void printValores(ListaHil* niveles, int nivel,int numHijo,string padre){ }
    virtual string obtenerTipo(){}
    virtual string obtenerTipo(string contexto,TablaSimbolos* ts ){}
    virtual string obtenerTipo(TablaSimbolos* ts){}
    virtual bool verificarComparacion(TablaSimbolos* ts, string contexto){}
    string convertirMacro(int macro)
    {
      switch (macro) {
        case 1:
        return "suma";
        break;

        case 2:
        return "resta";
        break;

        case 3:
        return "multi";
        break;

        case 4:
        return "div";
        break;

        case 5:
        return "mod";
        break;

        case 6:
        return "and";
        break;

        case 7:
        return "or";
        break;

        case 8:
        return "neg";
        break;

        case 9:
        return "menor";
        break;

        case 10:
        return "menor igual";
        break;

        case 11:
        return "mayor";
        break;

        case 12:
        return "mayor igual";
        break;

        case 13:
        return "diferente";
        break;

        case 14:
        return "igual";
        break;

        case 15:
        return "si";
        break;

        case 16:
        return "pero si";
        break;

        case 17:
        return "sino";
        break;

        case 18:
        return "para";
        break;

        case 19:
        return "mientras";
        break;
      }
    }

};

class NodoDeclaracion: public Nodo
{

};



/** ---- Variables --- **/
class NodoVariable: public NodoInstruccion
{
};


class NodoEntero : public NodoVariable
{
public:
    int valor;
    NodoEntero(int valor) : valor(valor) { }

    void printValores(ListaHil* niveles, int nivel,int numHijo,string padre)
        {
            //string info ="[N]"+padre+"|"+to_string(numHijo)+":"+to_string(valor)+"   ";
            string info = "";
            for (int i = 0; i < nivel; i++) {
              /* code */
              info += "  ";
            }
            info += "Nodo Entero";
            niveles->at(nivel)+=info;


        }

    string obtenerTipo()
    {
      return "entero";
    }
    string obtenerTipo(string contexto, TablaSimbolos* ts)
    {
      return "entero";
    }

    bool compararTipo(TablaSimbolos* ts, string tipoPadre, bool basura){


      return "entero" == tipoPadre;
    }

    bool compcompararTipo(TablaSimbolos* ts,string tipo,string contexto,char basura)
    {
      return "entero" == tipo;
    }

};


class NodoHilera : public NodoVariable
{
public:
	string valor;
	NodoHilera(string valor) : valor(valor){}

    void printValores(ListaHil* niveles, int nivel,int numHijo,string padre)
        {

            string info ="[N]"+padre+"|"+to_string(numHijo)+":"+valor+"   ";
            niveles->at(nivel)+=info;
        }

   string obtenerTipo()
   {
      return "hilera";
   }

   string obtenerTipo(string contexto, TablaSimbolos* ts)
   {
     return "hilera";
   }

   bool compararTipo(TablaSimbolos* ts, string tipoPadre, bool basura){
     bool respuesta =  "hilera" == tipoPadre;
     if(!respuesta)
     {
       cout<<"ERROR : tipo esperado "+ tipoPadre +" vs tipo de identificador recibido: hilera"<<endl;
     }
     return respuesta;
   }


   bool compararTipo(TablaSimbolos* ts,string tipo,string contexto,char basura)
   {
     bool respuesta =  "hilera" == tipo;
     if(!respuesta)
     {
       cout<<"ERROR ("+contexto+") : tipo esperado "+ tipo +" vs tipo de identificador recibido: hilera"<<endl;
     }
     return respuesta;
   }

};

class NodoIdentificador : public NodoVariable
{
public:
	string valor;
	NodoIdentificador(string valor) : valor(valor){}

    /*void printValores(ListaHil* niveles, int nivel,int numHijo,string padre)
        {

            string info ="[N]"+padre+"|"+to_string(numHijo)+":"+valor+"   ";
            niveles->at(nivel)+=info;
        }*/
    bool cargarTablaSimbolos(map<string, ListaSimbolos*> *tablaSimbolos){
        map<string, ListaSimbolos*>::iterator itContextoG = tablaSimbolos->find(valor);
	//itContextoG iterador contexto global
        if(itContextoG == tablaSimbolos->end()){
            ListaSimbolos *listaContexto = new ListaSimbolos();
            tablaSimbolos->insert(pair<string, ListaSimbolos*>(valor, listaContexto));
        } else {
            cout << "Error: Ya existe en este contexto una variable con este nombre " << valor << endl;
        }
         return true;
    }

    bool cargarTablaSimbolos(string nombreFuncion, map<string, ListaSimbolos*> *tablaSimbolos){
        //se fija si es una variable global, osea contexto global
        map<string, ListaSimbolos*>::iterator itContextoG = tablaSimbolos->find(valor); //itContextoG iterador contexto global

        if(itContextoG == tablaSimbolos->end()){
            // en caso de que no lo sea entonces busca dentro del contexto local.
            itContextoG = tablaSimbolos->find(nombreFuncion);
            ListaSimbolos *listaContexto = itContextoG->second;
            if(listaContexto->buscar(valor) == listaContexto->getFinLista()){
                cout << "Error ( "<<nombreFuncion<<" ) : Este identificador no ha sido declarado: " << valor << endl;
            }
        }

        return true;
    }

     bool cargarTablaSimbolos(string nombreFuncion, map<string, ListaSimbolos*> *tablaSimbolos, string token){

        map<string, ListaSimbolos*>::iterator itContextoG = tablaSimbolos->find(valor);
	//itContextoG iterador contexto global
        if(itContextoG == tablaSimbolos->end()){
            itContextoG = tablaSimbolos->find(nombreFuncion);
            ListaSimbolos *listaContexto = itContextoG->second;
            if(listaContexto->buscar(valor) == listaContexto->getFinLista()){
                listaContexto->insertarNuevo(valor, token, "");
            } else {
                cout <<"Error: Ya existe en este contexto una variable con este nombre " << valor << endl;
            }
        } else {
            cout <<"Error"<<"( "<<nombreFuncion<<" )"<<": Ya existe en el contexto global una variable con este nombre " << valor << endl;
        }

         return true;
    }

    bool cargarTablaSimbolos(map<string, ListaSimbolos*> *tablaSimbolos, string tc){
        map<string, ListaSimbolos*>::iterator itContextoG = tablaSimbolos->find(valor);
	//itContextoG iterador contexto global
        if(itContextoG == tablaSimbolos->end()){
            ListaSimbolos *listaContexto = new ListaSimbolos();
            listaContexto->setTipoContexto(tc);
            tablaSimbolos->insert(pair<string, ListaSimbolos*>(valor, listaContexto));
        } else {
            cout << "Error: Ya existe en este contexto una variable con este nombre " << valor << endl;
            return false;
        }
        return true;
    }


    /** este método es para el caso de analizar dentro de variables globales **/
    string obtenerTipo(TablaSimbolos* ts)
    {
        string respuesta="";
        itTabla it= ts->find(valor);
        //busca en el contexto global
        if( it !=  ts->end() )
        {
          respuesta = it->second->getTipoContexto();
        }
        return respuesta;
    }


    string obtenerTipo(string contexto,TablaSimbolos* ts)
    {

      string respuesta="";
      itTabla it= ts->find(valor);
      //busca en el contexto global
      if( it !=  ts->end() )
      {
        respuesta = it->second->getTipoContexto();
      }
      else
      {
        it= ts->find(contexto);
        list<Simbolo*>::iterator id= it->second->buscar(valor);
        if(it->second->getFinLista() != id )
        {
          /** si lo encuentra entonces **/
          respuesta= (*id)->token;
        }
      }
      return respuesta;
    }




    bool compararTipo(TablaSimbolos* ts, string tipoPadre){


        //cout<<"tipo padre: "+tipoPadre<<endl;
        return true;

    }

    // Recive el contexto en caso de no estar ahí se busca en global

    bool compararTipo(TablaSimbolos* ts, string tipo, string contexto, char basura){

        string miTipo= this->obtenerTipo(contexto,ts);
        if(miTipo == tipo){
          return true;
        }else{

          cout<<"ERROR ("+contexto+") : tipo esperado "+ tipo +" vs tipo de identificador recibido: "+miTipo+ " - " +valor<<endl;
          return false;
        }

    }

};


class NodoBooleano : public NodoVariable
{
public:
	bool valor;
	NodoBooleano(bool valor) : valor(valor){}

    void printValores(ListaHil* niveles, int nivel,int numHijo,string padre)
        {
            string info ="[N]"+padre+"|"+to_string(numHijo)+":"+to_string(valor)+"   ";
            niveles->at(nivel)+=info;
        }

    string obtenerTipo()
    {
        return "bool";
    }

    string obtenerTipo(string contexto, TablaSimbolos* ts)
    {
      return "entero";
    }

    bool compararTipo(TablaSimbolos* ts, string tipoPadre, bool basura){


      return "bool" == tipoPadre;
    }

    bool compcompararTipo(TablaSimbolos* ts,string tipo,string contexto,char basura)
    {
      return "bool" == tipo;
    }
};


class NodoArray: public NodoVariable
{
	public:

	string ident;
	dimensionesMatriz* dimensiones;
	matrizValores* valores;

	NodoArray(string id,dimensionesMatriz* dim,matrizValores*   vals)
  {
    ident=id;
    if(dim != 0)
    {
        dimensiones = dim;
    }
    else
    {
      if(vals != 0)
      {

        //  Saca el tamaño de cada subvector y se lo agrega a las dimensiones como
        //un NodoEntero
        dimensiones= new dimensionesMatriz;
        for(int i=0; i<vals->size();i++)
        {
          dimensiones->push_back( new NodoEntero(vals->at(i)->size() )  );
        }

      }
    }
    valores=vals;
  }

  void printValores(ListaHil* niveles, int nivel,int numHijo,string padre)
  {
      string info ="[N]"+padre+"|"+to_string(numHijo)+":NArray "+ident+"   ";
      niveles->at(nivel)+=info;

      string actual = padre+","+to_string(numHijo);

      /** se mandan a imprimir las dimensiones **/
      if(dimensiones != 0)
      {
        for(int h=dimensiones->size(); h>0;h--)
        {
          cout<<"el valor de h es "<<h<<endl;
          // el (-1*h)-1 es para pasar a negativo el numero de hijo y el -1
          //es para que el valor mayor sea -1 y no 0
          dimensiones->at(h-1)->printValores(niveles,nivel+1,(-1*h),actual);
        }
      }

      /** se mandan a imprimir los valores*/
      if(valores != 0)
      {
        char a='a';
        for(int x=0; x<valores->size();x++)
        {
          // Para iterar en las columnas
          for(int y=0; y<valores->at(x)->size();y++)
          {
            valores->at(x)->at(y)->printValores(niveles,nivel+1,y,actual+"+"+a);
          }
          a++;
        }
      }

  }



};




/** ---- Instrucciones ---- **/


class NodoEstructuraControl: public NodoInstruccion
{
	public:
    	int tipo;
	NodoInstruccion* comparacion;
	NodoEstructuraControl* siguienteSi;
	bloqueInstrucciones* bloque;
	NodoDeclaracion* declaracion;
	NodoEstructuraControl(int tipo, NodoInstruccion* comparacion, bloqueInstrucciones* bloque):
    		tipo(tipo), comparacion(comparacion), bloque(bloque) {}

	// Método para inserta en la ultima posicion de la lista de SiguienteSi.
	// Esto es en caso de tener muchos pero si: ; pero si: ; (...) y por ultimo un sino ya que
	//debido a cómo esta hecha la gramatica pueden o no hacer varios "pero si" o ninguno
	void InsertarUltimo(NodoEstructuraControl* nodo)
	{
	   if(siguienteSi != 0)
	   {
	     siguienteSi->InsertarUltimo(nodo);
	   }
	   else
	   {
	     siguienteSi= nodo;
	   }
	}

   	 void printValores(ListaHil* niveles, int nivel,int numHijo,string padre)
    	{

        //string info ="[N]"+padre+"|"+to_string(numHijo)+":NEC-"+convertirMacro(tipo)+"   ";
        string info = "";
        for (int i = 0; i < nivel; i++) {
          /* code */
          info += "  ";
        }
        info += "Estructura de Control\n";
        niveles->at(nivel)+=info;

        /** Para sacar el nombre actual de este nodo **/
        string actual = padre+","+to_string(numHijo);


	      /** Llamado para printValores de los siguientes nodos Si **/
	     if(siguienteSi != 0)
	     {
	         siguienteSi->printValores(niveles,nivel,-3,actual);
	     }


        /** Llamado para printValor de comparacion
	       nota: En caso que sea tipo SINO entonces no hay comparación
	     **/
	     if(comparacion != 0)
	     {
	      comparacion->printValores(niveles, nivel+1 , -2 ,actual);
	     }

	     if(declaracion != 0)
	     {
	       declaracion->printValores(niveles, nivel+1 , -1 ,actual);
	     }


       /** Procedo a llamar el printValores de los "nodos hijos" en bloque **/
       for(int hijo =0; hijo< bloque->size();hijo++)
       {
        bloque->at(hijo)->printValores(niveles, nivel+1 , hijo ,actual);

       }
    	}



    	bool cargarTablaSimbolos(string nombreFuncion, map<string, ListaSimbolos*> *tablaSimbolos){
        /** Llamado para cargarTablaSimbolos de los siguientes nodos Si **/
        if(declaracion != 0)
        {
          declaracion->cargarTablaSimbolos(nombreFuncion,tablaSimbolos);
        }


        /** Llamado para cargarTablaSimbolos de comparacion
        nota: En caso que sea tipo SINO entonces no hay comparación
        **/
        if(comparacion != 0)
        {
           comparacion->cargarTablaSimbolos(nombreFuncion, tablaSimbolos);
        }

        /** Procedo a llamar cargarTablaSimbolos de los "nodos hijos" en bloque **/
        for(int hijo = 0; hijo < bloque->size(); hijo++)
           {
                bloque->at(hijo)->cargarTablaSimbolos(nombreFuncion, tablaSimbolos);

           }
        if(siguienteSi != 0)
        {
              siguienteSi->cargarTablaSimbolos(nombreFuncion, tablaSimbolos);
        }
        return true;
    }

    bool compararTipo(TablaSimbolos* ts, string contexto, char basura)
    {
      bool respuesta= true;
      if(declaracion != 0)
      {
        cout<<"compara la declaracion"<<endl;
        respuesta= declaracion->compararTipo(ts, contexto, basura);
      }

      // comprueba que la comparacion tenga tipos consistentes
      if(comparacion != 0)
      {
        cout<<"compara la comparacion :v"<<endl;
        respuesta = comparacion->verificarComparacion(ts,contexto) && respuesta;
      }

      if(siguienteSi != 0)
      {
        cout<<"compara el siguiente si"<<endl;
        respuesta = siguienteSi->compararTipo(ts,contexto,basura) && respuesta;
      }

      if(bloque != 0)
      {
        cout<<"compara el bloque"<<endl;
        for(int hijo =0; hijo < bloque->size(); hijo++) {

            respuesta = bloque->at(hijo)->compararTipo(ts, contexto, 'b')&&respuesta;
        }
      }

      return respuesta;
    }
};


class NodoLlamadoFuncion: public NodoInstruccion
{
	public:

	string nombreFuncion;
	listaLlamadoFun* parametros;//nodo NodoInstruccion
	NodoLlamadoFuncion(string nombreFuncion, listaLlamadoFun* parametros ):
	    nombreFuncion(nombreFuncion), parametros(parametros) {}

    NodoLlamadoFuncion(string nombreFuncion ):
	    nombreFuncion(nombreFuncion){}


    void printValores(ListaHil* niveles, int nivel,int numHijo,string padre)
        {
            //string info ="[N]"+padre+"|"+to_string(numHijo)+":NLLF-"+nombreFuncion+"   ";
            string info = "";
            for (int i = 0; i < nivel; i++) {
              /* code */
              info += "  ";
            }
            info += "Llamado a Funcion\n";
            niveles->at(nivel)+=info;

            //string actual = padre+","+to_string(numHijo);

            /** Procedo a llamar el printValores de los "nodos hijos" en parametros **/
            /**if(parametros != 0)
            {
                for(int hijo =0; hijo< parametros->size();hijo++)
                {
                    parametros->at(hijo)->printValores(niveles, nivel+1 , hijo ,actual);

                }
            }*/

        }

    bool cargarTablaSimbolos(string funcionContexto, map<string, ListaSimbolos*> *tablaSimbolos){

        /** busca si YO ya he sido declarado anteriormente **/
        map<string, ListaSimbolos*>::iterator itContextoG = tablaSimbolos->find(nombreFuncion);
	       //itContextoG iterador contexto global

        if(itContextoG == tablaSimbolos->end())
        {
	//Si el Nodo(lista de símbolos) Contexto no está en la tabla se agrega, y se le solicita a los hijos del nodo auto-agregarse

            cout << "Error: La función \"" << nombreFuncion << "\" no ha sido declarada" << endl;

            /** hay que verificar quel numero de parametros coincida **/
            if(parametros != 0)
            {
              for(int hijo =0; hijo < parametros->size(); hijo++) {
                  parametros->at(hijo)->cargarTablaSimbolos(funcionContexto, tablaSimbolos);
              }
            }
        }
        else
        {
          /** hay que verificar quel numero de parametros coincida **/
          if(parametros != 0)
          {
            for(int hijo =0; hijo < parametros->size(); hijo++) {
                parametros->at(hijo)->cargarTablaSimbolos(funcionContexto, tablaSimbolos);
            }
          }
        }
        return true;
    }

    bool cargarTablaSimbolos(map<string, ListaSimbolos*> *tablaSimbolos) {
        map<string, ListaSimbolos*>::iterator itContextoG = tablaSimbolos->find(nombreFuncion);
	//itContextoG iterador contexto global
        if(itContextoG != tablaSimbolos->end()) {
	//Si el Nodo(lista de símbolos) Contexto no está en la tabla se agrega, y se le solicita a los hijos del nodo auto-agregarse
            /** Procedo a llamar cargarTablaSimbolos de los "nodos hijos" en parametros **/
            for(int hijo =0; hijo < parametros->size(); hijo++) {
                parametros->at(hijo)->cargarTablaSimbolos(nombreFuncion, tablaSimbolos);
            }
        } else { //Si no, si está se indica el error, los nombres de funciones deben ser únicos

            if( nombreFuncion != "escanear"  && nombreFuncion != "imprimir" )
            {
              cout << "Error: La función " << nombreFuncion << " no ha sido declarada" << endl;
            }

        }
        return true;
    }

    string obtenerTipo(TablaSimbolos* ts)
    {
        itTabla it = ts->find(nombreFuncion);
        return it->second->getTipoContexto();
    }
    string obtenerTipo(TablaSimbolos*ts, string contexto, int posicionParam){


      itTabla it = ts->find(contexto);
      return it->second->typeAt(posicionParam);
    }

    // Metodo para sacar el tipo de la funcion que se llama
    string obtenerTipo(TablaSimbolos* ts, string contexto)
    {
      itTabla it= ts->find(contexto);
      return it->second->getTipoContexto();
    }

    bool compararTipo(TablaSimbolos* ts, string nombreFunAct, char b){
      bool out = true;
      for(int hijo =0; hijo < parametros->size(); hijo++) {

          out = parametros->at(hijo)->compararTipo(ts, this->obtenerTipo(ts,nombreFuncion, hijo), nombreFunAct, 'b')&&out;
      }
      return out;
    }



};


class NodoAsignacion: public NodoInstruccion
{
	public:

	NodoInstruccion* idNAsignacion;
	NodoInstruccion* expresion;
	NodoAsignacion(NodoInstruccion* idNAsignacion , NodoInstruccion* expresion):
	    idNAsignacion(idNAsignacion), expresion(expresion){}


    void printValores(ListaHil* niveles, int nivel,int numHijo,string padre)
        {

            //string info ="[N]"+padre+"|"+to_string(numHijo)+":NA   ";
            string info = "";
            for (int i = 0; i < nivel; i++) {
              /* code */
              info += "  ";
            }
            info += "Asignacion\n";
            niveles->at(nivel)+=info;

            //string actual = padre+","+to_string(numHijo);


            //idNAsignacion->printValores(niveles, nivel+1 , 0 ,actual);
            //expresion->printValores(niveles, nivel+1 , 1 ,actual);


        }

    bool cargarTablaSimbolos(map<string, ListaSimbolos*> *tablaSimbolos, string tipoVar){
        idNAsignacion->cargarTablaSimbolos(tablaSimbolos, tipoVar);
         return true;
    }

    bool cargarTablaSimbolos(string nombreFuncion, map<string, ListaSimbolos*> *tablaSimbolos){
        idNAsignacion->cargarTablaSimbolos(nombreFuncion, tablaSimbolos);
        expresion->cargarTablaSimbolos(nombreFuncion, tablaSimbolos);
        return true;
    }

    bool cargarTablaSimbolos(string nombreFuncion, map<string, ListaSimbolos*> *tablaSimbolos, string token){
        idNAsignacion->cargarTablaSimbolos(nombreFuncion, tablaSimbolos, token);
        expresion->cargarTablaSimbolos(nombreFuncion, tablaSimbolos);
        return true;
    }

    bool compararTipo(TablaSimbolos* ts, string tipoPadre){


      return expresion->compararTipo(ts, tipoPadre, true);
    }

    /** compara lo que tiene el lado izquierdo del igual con la exp del lado derecho**/
    bool compararTipo(TablaSimbolos* ts, string contexto, char basura){
      //std::cout << "Dentro de NASIG compararTipo contexto, basura" << '\n';
      return expresion->compararTipo(ts, idNAsignacion->obtenerTipo(contexto,ts) ,contexto, basura);
    }
};


class NodoVarLocal: public NodoInstruccion
{
	public:

	NodoDeclaracion* variableLocal;
	NodoVarLocal(NodoDeclaracion* variableLocal): variableLocal(variableLocal) {}

	/*void printValores(ListaHil* niveles, int nivel,int numHijo,string padre)
        {
            string info ="[N]"+padre+"|"+to_string(numHijo)+":NVL    ";
            niveles->at(nivel)+=info;

            string actual = padre+","+to_string(numHijo);
            variableLocal->printValores(niveles, nivel+1 , 0 ,actual);
        }*/
   	 bool cargarTablaSimbolos(string nombreFuncion, map<string, ListaSimbolos*> *tablaSimbolos){
            variableLocal->cargarTablaSimbolos(nombreFuncion, tablaSimbolos);
            return true;
    	}
};

class NodoExpresion: public NodoInstruccion
{
	public:
    	int operador;
	NodoInstruccion* expIz;
	NodoInstruccion* expDe;
	NodoExpresion(NodoInstruccion* expIz,NodoInstruccion* expDe, int operador):
	    expIz(expIz),expDe(expDe),operador(operador){}

    	/*void printValores(ListaHil* niveles, int nivel,int numHijo,string padre)
        {


            string info ="[N]"+padre+"|"+to_string(numHijo)+":NExp "+convertirMacro(operador)+"   ";
            niveles->at(nivel)+=info;

            string actual = padre+","+to_string(numHijo);

	          expIz->printValores(niveles, nivel+1 , 0 ,actual);

	          if(expDe!= 0)
	           {
               expDe->printValores(niveles, nivel+1 , 1 ,actual);
	            }


        }*/

        bool cargarTablaSimbolos(string nombreFuncion, map<string, ListaSimbolos*> *tablaSimbolos){
            expIz->cargarTablaSimbolos(nombreFuncion, tablaSimbolos);
            if(expDe!= 0)
            {
                expDe->cargarTablaSimbolos(nombreFuncion, tablaSimbolos);
            }
        }

        bool cargarTablaSimbolos(map<string, ListaSimbolos*> *tablaSimbolos){
            expIz->cargarTablaSimbolos(tablaSimbolos);
            if(expDe!= 0)
            {
                expDe->cargarTablaSimbolos(tablaSimbolos);
            }
            return true;
        }

        //  Método que saca el tipo de la expresion izquierda para luego
        //poder usarlo en compararTipo o verificarComparacion
        string obtenerTipo(string  contexto,TablaSimbolos* ts)
        {

          return expDe->obtenerTipo(contexto,ts);
        }

        /** metodo provisional y prototipico  para el punto 3 **/

        bool verificarComparacion(TablaSimbolos* ts,string  contexto)
        {
          bool respuesta = false;
          if(operador == AND || operador == OR )
          {
            bool r1= expIz->verificarComparacion(ts,contexto);
            respuesta = expDe->verificarComparacion(ts,contexto) && r1;
          }
          else
          {
            if(operador == NEG)
            {
              respuesta = expIz->verificarComparacion(ts,contexto);
            }
            else
            {
              // En este nivel del arbol y dada su forma de construirse, se implica
              //que existe una expDe que es una hoja(algo derivado de NodoVariable)
              // y por ende es más sencillo sacarle el tipo y mandar a confirmar
              //recursivamente a los hijos de la izquierda
              if(NEG < operador && operador< SI)
              {
                cout<<"caso de operadores de num/hil"<<endl;
                string tipoDe= expDe->obtenerTipo(contexto,ts);
                std::cout << "Despues de obtener el tipo del hijo " <<tipoDe<< '\n';
                respuesta = expIz->compararTipo(ts,tipoDe,contexto,'b');
              }
            }
            ///  respuesta = expIz->obtenerTipo == expDe->ob
          }
          return respuesta;
        }

        // Compara los tipos de las expresiones de cada lado, se usa dentro de NDVar
        bool compararTipo(TablaSimbolos* ts, string tipoPadre, bool basura){
          bool r1 =expIz->compararTipo(ts, tipoPadre, true);
          if(expDe != 0)
          {
            return r1 && expDe->compararTipo(ts, tipoPadre, true);
          }
          else
          {
              return r1;
          }


        }

        // Este se usa en caso de estar dentro de una funcion puesto que recive el contexto
        bool compararTipo(TablaSimbolos* ts, string tipo, string contexto, char basura){
            bool r1 =expIz->compararTipo(ts,tipo,contexto,basura);
            if(expDe!= 0)
            {
              return r1 && expDe->compararTipo(ts,tipo,contexto,basura);
            }
            else
            {
              return r1;
            }
        }


};






/** --- Declaraciones --- **/


class NodoDeclaracionFunc: public NodoDeclaracion
{

	public:

	string tipoRetorno;
	string nombreFuncion;
	parametrosFuncion* parametros;
	bloqueInstrucciones* codigo;

	NodoDeclaracionFunc(string tipoRetorno,string nombreFuncion,
                     parametrosFuncion* parametros,bloqueInstrucciones* codigo):
        tipoRetorno(tipoRetorno),nombreFuncion(nombreFuncion),parametros(parametros),codigo(codigo){}

	NodoDeclaracionFunc(string tipoRetorno,string nombreFuncion,bloqueInstrucciones* codigo):
        tipoRetorno(tipoRetorno),nombreFuncion(nombreFuncion),codigo(codigo), parametros(0){}


    void printValores(ListaHil* niveles, int nivel,int numHijo,string padre)
        {
            //string info ="[N]"+padre+"|"+to_string(numHijo)+":NDF-"+tipoRetorno+"+"+nombreFuncion+"   ";

            string info = "";
            for (int i = 0; i < nivel; i++) {
              /* code */
              info += "  ";
            }
            info += "Declaracion Funcion\n";
            niveles->at(nivel)+=info;
            string actual = padre+","+to_string(numHijo);

            /** Procedo a llamar el printValores de los "nodos hijos" en parametros **/
            /**if( parametros != 0)
            {
              for(int hijo =0; hijo< parametros->size();hijo++)
              {
                  parametros->at(hijo)->printValores(niveles, nivel+1 , (hijo+1)*-1 ,actual);

              }

            }*/

            /** Procedo a llamar el printValores de los "nodos hijos" en codigo **/
            for(int hijo2 =0; hijo2< codigo->size();hijo2++)
            {
                codigo->at(hijo2)->printValores(niveles, nivel+1 , hijo2 ,actual);

            }
        }

    bool cargarTablaSimbolos(map<string, ListaSimbolos*> *tablaSimbolos) {

        /** verifica que el nombre de la funcion no haya sido declarado antes */
        if(tablaSimbolos->find(nombreFuncion) == tablaSimbolos->end()){
	//Si el Nodo(lista de símbolos) Contexto no está en la tabla se agrega, y se le solicita a los hijos del nodo auto-agregarse
            ListaSimbolos *listaContexto = new ListaSimbolos();
            tablaSimbolos->insert(pair<string, ListaSimbolos*>(nombreFuncion, listaContexto));

            /** Procedo a llamar cargarTablaSimbolos de los "nodos hijos" en parametros **/
            if( parametros!= 0)
            {
              for(int hijo =0; hijo< parametros->size(); hijo++) {
                  parametros->at(hijo)->cargarTablaSimbolos(nombreFuncion, tablaSimbolos);

              }
            }


            /** Procedo a llamar cargarTablaSimbolos de los "nodos hijos" en codigo **/
             for(int hijo2 = 0; hijo2 < codigo->size(); hijo2++) {
                 codigo->at(hijo2)->cargarTablaSimbolos(nombreFuncion, tablaSimbolos);
            }
        } else { //Si no, si está se indica el error, los nombres de funciones deben ser únicos
            cout << "Error: Ya existe una función en el contexto global con el nombre  \"" << nombreFuncion << "\"" << endl;
        }
        return true;
    }

    /** Método para verificar los tipos de las instrucciones **/
    bool compararTipo(TablaSimbolos* ts){

      bool respuesta = true;
      for(int hijo =0; hijo< codigo->size();hijo++)
      {
          //cout<<"revisa el hijo "<<hijo<<" dentro de "+nombreFuncion<< endl;
          respuesta = respuesta && codigo->at(hijo)->compararTipo(ts, nombreFuncion,'b');

      }

      return respuesta;
    }
};

class NodoDeclaracionVar: public NodoDeclaracion
{

	public:

	string tipoVar;
	listaVar* variables;
	NodoDeclaracionVar(string tipoVar,listaVar* variables):
	    tipoVar(tipoVar), variables(variables){}

    void printValores(ListaHil* niveles, int nivel,int numHijo,string padre)
        {

            //string info ="[N]"+padre+"|"+to_string(numHijo)+":NDV-"+tipoVar+"   ";
            string info = "";
            for (int i = 0; i < nivel; i++) {
              /* code */
              info += "  ";
            }
            info += "Declaracion de variable\n";
            niveles->at(nivel)+=info;

            string actual = padre+","+to_string(numHijo);

            /** Procedo a llamar el printValores de los "nodos hijos" en variables **/
            for(int hijo =0; hijo< variables->size();hijo++)
            {
                variables->at(hijo)->printValores(niveles, nivel+1 , hijo ,actual);

            }
        }

    bool cargarTablaSimbolos(map<string, ListaSimbolos*> *tablaSimbolos) {
        /** Procedo a llamar cargarTablaSimbolos de los "nodos hijos" en variables **/
        for(int hijo = 0; hijo < variables->size(); hijo++) {
            variables->at(hijo)->cargarTablaSimbolos(tablaSimbolos, tipoVar);
        }
        return true;
    }

    bool cargarTablaSimbolos(string nombreFuncion, map<string, ListaSimbolos*> *tablaSimbolos){
        /** Procedo a llamar cargarTablaSimbolos de los "nodos hijos" en variables **/

        for(int hijo = 0; hijo < variables->size(); hijo++) {
            variables->at(hijo)->cargarTablaSimbolos(nombreFuncion, tablaSimbolos, tipoVar);
        }
        return true;
    }


      bool compararTipo(TablaSimbolos* ts){


        bool respuesta = true;
        for(int hijo =0; hijo< variables->size();hijo++)
        {
            respuesta = variables->at(hijo)->compararTipo(ts, tipoVar) && respuesta ;

        }
        return respuesta;
      }

};



/**  --- Controlador/Raiz --- **/
class NodoControlador: public Nodo
{
	public:

	NodoInstruccion* iniciarNombreFuncion;
    	listaDeclaraciones declaraciones;


   	void printValores(ListaHil* niveles, int nivel,int numHijo,string padre)
        {

            string info ="[N]"+padre+"|"+to_string(numHijo)+":NControlador"+"   ";
            niveles->at(nivel)+=info;

            string actual = padre;

            iniciarNombreFuncion->printValores(niveles, nivel+1 , -1 ,actual);


            /** Procedo a llamar el printValores de los "nodos hijos" en declaraciones **/
            for(int hijo =0; hijo< declaraciones.size();hijo++)
            {
                declaraciones.at(hijo)->printValores(niveles, nivel+1 , hijo ,actual);

            }
        }

        bool cargarTablaSimbolos(map<string, ListaSimbolos*> *tablaSimbolos){
             for(int hijo =0; hijo < declaraciones.size(); hijo++) {
                 declaraciones.at(hijo)->cargarTablaSimbolos(tablaSimbolos);
             }
             iniciarNombreFuncion->cargarTablaSimbolos(tablaSimbolos);

             return true;
        }


        bool compararTipo(TablaSimbolos* ts){


          bool respuesta = true;
          for(int hijo =0; hijo< declaraciones.size();hijo++)
          {
              respuesta = respuesta && declaraciones.at(hijo)->compararTipo(ts);
          }
          return respuesta;
        }

};
