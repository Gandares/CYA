#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "nfa.hpp"
#include "estado.hpp"
#include "transicion.hpp"

using namespace std;

int main(void){
    
    int opcion;
    string f;
    nfa NFA;

    do{
        cout << "1.LEER NFA." << endl;
        cout << "2.MOSTRAR NFA." << endl;
        cout << "3.INDENTIFICAR ESTADOS DE MUERTE." << endl;
        cout << "4.INDENTIFICAR ESTADOS IMPORTANTES." << endl;
        cout << "5.ES DFA." << endl;
        cout << "6.ANALIZAR CADENA." << endl;
        cout << "0.SALIR." << endl;
        cout << "Elija una opción: ";
        cin >> opcion;
        
        if(opcion==1){
            NFA.read();
            cout << "Éxito en la lectura del nfa" << endl << endl;
        }
        else if(opcion==2){
            NFA.write();
        }
        else if(opcion==3){
            cout << endl;
            NFA.muerte();
            cout << endl;
        }
        else if(opcion==4){
            cout << endl;
            NFA.estado_importante();
            cout << endl;
        }
        else if(opcion==5){
            cout << endl;
            NFA.es_dfa();
            cout << endl;
        }
        else if(opcion==6){
            cout << endl;
            NFA.comprobar_cadena();
            cout << endl;
        }
        else if(opcion==0){
            break;
        }
        else
            cout << "Error de selección." << endl;
        
    }while(opcion!=0);
}