#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "dfa.hpp"
#include "estado.hpp"
#include "transicion.hpp"

using namespace std;

int main(void){
    
    int opcion;
    string f;
    dfa DFA;

    do{
        cout << "1.LEER DFA." << endl;
        cout << "2.MOSTRAR DFA." << endl;
        cout << "3.INDENTIFICAR ESTADOS DE MUERTE." << endl;
        cout << "4.ANALIZAR CADENA." << endl;
        cout << "0.SALIR." << endl;
        cout << "Elija una opción: ";
        cin >> opcion;
        
        if(opcion==1){
            DFA.read();
            cout << "Éxito en la lectura del dfa" << endl << endl;
        }
        else if(opcion==2){
            DFA.write();
        }
        else if(opcion==3){
            cout << endl;
            DFA.muerte();
            cout << endl;
        }
        else if(opcion==4){
            DFA.comprobar_cadena();
            cout << endl;
        }
        else if(opcion==0){
            break;
        }
        else
            cout << "Error de selección." << endl;
        
    }while(opcion!=0);
}