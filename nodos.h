#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include "ListaSimbolos.cpp"
using namespace std;

class Nodo {
public:
  vector<string> listaDeclaracion, printValores;
  pair<string, int> funcion;
  ListaSimbolos ls;

  bool guardarDatos(){

    int z = funcion.second;
    int t = listaDeclaracion.size();

    if( t!= z){
      return false;
    }else{
        for (int i = 0; i < listaDeclaracion.size(); ++i) {
          /* code */
          ls.variablesDeclaradas->push_back(listaDeclaracion.at(i));
        }
        return true;
    }

  }

  bool analisisSemantico(){

    for (int i = 0; i < printValores.size(); ++i) {
      /* code */
      if(!ls.exists(printValores.at(i))){

        cout<<"ERROR: la variable '" + printValores.at(i) + "' no se encuntra declarada en la lista de variables"<<endl;
        return false;
      }
    }

    return true;
  }

  void codeGen(){
    string output = string(".data\n\t prompt: .asciiz \" Ingrese numero para el parametro")+
                    string(": \"\n")+string("\t message: .asciiz \"\\n\"")+ string("\n.text\n");

    vector<string> registerList;

    string instr;

    ofstream myfile;
    myfile.open ("asam_code.txt");

    for (int i = 0; i < listaDeclaracion.size(); i++) {
      /* code */
      registerList.push_back("t"+to_string(i));
    }

    for (int k = 0; k < listaDeclaracion.size(); k++) {
      /* code */
      instr += "\t\tli $v0, 4\n\t\tla $a0, prompt\n\t\tsyscall\n\n\t\tli $v0, 5\n\t\tsyscall\n\t\tmove $"+registerList[k]+", $v0\n";
    }

    output += instr;
    instr = "";
    for (int i = 0; i < listaDeclaracion.size(); i++) {
      /* code */
      for (int j = 0; j < printValores.size(); j++) {
        /* code */

        if (printValores[j].compare(listaDeclaracion[i]) == 0) {
          /* code */

          instr += "\t\tli $v0, 4\n\t\tla $a0, message\n\t\tsyscall\n\n\t\tli $v0, 1\n\t\tmove $a0,$"+
                  string(registerList[j])+"\n\t\tsyscall\n";
        }
      }
    }

    output+= instr;

    myfile << output;
    myfile.close();
  }
};
