/* Lista de Símbolos */
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <string>
using namespace std;

class ListaSimbolos {

    public:
      vector<string> *variablesDeclaradas;
        /* Constructor */
         ListaSimbolos(){
            variablesDeclaradas = new std::vector<string>;
         }

        bool exists(string element){

          bool out = false;

          for(int i = 0; i < variablesDeclaradas->size(); ++i){

              if(variablesDeclaradas->at(i).compare(element) == 0){

                  out = true;
                  break;
              }
          }

          return out;
        }
};
