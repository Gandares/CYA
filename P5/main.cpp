#include <iostream>
#include <set>
#include <string>
#include <cstdlib>
#include "calculadora.hpp"

using namespace std;

int main(void){
    
    int opcion;
    string C,D;
    
    cout << "Defina el primer lenguaje: ";
    
    getline(cin,C);
    calculadora A(C);
    
    cout << "Defina el segundo lenguaje: ";
    
    getline(cin,D);
    calculadora B(D);
    
    system("clear");
    
do{
    
    int sel, pot;
    
    cout << endl << "Primer lenguaje: ";
    A.mostrar();
    cout << endl;
    
    cout << "Segundo lenguaje: ";
    B.mostrar();
    cout << endl;
   
    cout << "1. Inversa" << endl;
    cout << "2. Concatenación" << endl;
    cout << "3. Unión" << endl;
    cout << "4. Intersección" << endl;
    cout << "5. Diferencia" << endl;
    cout << "6. Sublenguajes" << endl;
    cout << "7. Igualdad de lenguajes" << endl;
    cout << "8. Potencia" << endl;
    cout << "9. Cierre de Kleene" << endl;
    cout << "0. Salir" << endl;
    cout << endl;
    cout << ">>> Introduzca una opción: ";
    cin >> opcion;
    
    calculadora Inversa;
    calculadora Concatenacion;
    calculadora Union;
    calculadora Interseccion;
    calculadora Diferencia;
    calculadora Sublenguajes;
    calculadora Igualdad;
    calculadora Potencia;
    calculadora Kleene;
    
    switch(opcion){
        
        case 1:
        
            cout << "¿De qué lenguaje quiere la inversa? ¿1 o 2? >>>> ";
            cin >> sel;
            if(sel==1){
                Inversa.inversa(C);
                cout << "Inversa: ";
                Inversa.mostrar();
                cout << endl;
            }
            else if(sel==2){
                Inversa.inversa(D);
                cout << "Inversa: ";
                Inversa.mostrar();
                cout << endl;
            }
            else
                cout << "Error en la selección.";
                cout << endl;
            break;
            
        case 2:
            
            Concatenacion.concatenacion(A.returnlenguaje(),B.returnlenguaje());
            cout << endl << "La concatenación de ambos lenguajes es: ";
            Concatenacion.mostrar();
            cout << endl;
            break;
            
        case 3:
        
            Union.unionn(C,D);
            cout << endl << "La unión de ambos lenguajes es: ";
            Union.mostrar();
            cout << endl;
            break;
            
        case 4:
        
            Interseccion.interseccion(A.returnlenguaje(),B.returnlenguaje());
            cout << endl << "La intersección de ambos lenguajes es: ";
            Interseccion.mostrar();
            cout << endl;
            break;
            
        case 5:

            Interseccion.interseccion(A.returnlenguaje(),B.returnlenguaje());
            cout << "1.¿Diferencia de lenguaje 1 - lenguaje 2?" << endl;
            cout << "2.¿Diferencia de lenguaje 2 - lenguaje 1?" << endl;
            cout << ">>>>>>>> ";
            cin >> sel;
            if(sel==1){
                Diferencia.diferencia(A.returnlenguaje(),Interseccion.returnlenguaje());
                cout << "Diferencia ";
                A.mostrar();
                cout << " - ";
                B.mostrar();
                cout << " = ";
                Diferencia.mostrar();
                cout << endl;
            }
            else if(sel==2){
                Diferencia.diferencia(B.returnlenguaje(),Interseccion.returnlenguaje());
                cout << "Diferencia "; 
                B.mostrar();
                cout << " - ";
                A.mostrar();
                cout << " = ";
                Diferencia.mostrar();
                cout << endl;
            }
            else
                cout << "Error en la selección.";
                cout << endl;
            break;
            
        case 6:
        
            Sublenguajes.sublenguajes(A.returnlenguaje(),B.returnlenguaje());
            cout << endl;
            break;
            
        case 7:
            
            if(Igualdad.igualdad(A.returnlenguaje(),B.returnlenguaje())==true)
                cout << "Los lenguajes son iguales." << endl;
            else
                cout << "Los lenguajes no son iguales." << endl;
            break;
            
        case 8:
        
            cout << "¿A que potencia lo quiere elevar? ";
            cin >> pot;
            cout << "¿En qué lenguaje? ¿1 o 2? >>>> ";
            cin >> sel;
            if(sel==1){
                cout << "Lenguaje 1 elevado a " << pot << " = ";
                Potencia.potencia(A.returnlenguaje(),pot);
                Potencia.mostrar();
                cout << endl;
            }
            else if(sel==2){
                cout << "Lenguaje 2 elevado a " << pot << " = ";
                Potencia.potencia(B.returnlenguaje(),pot);
                Potencia.mostrar();
                cout << endl;
            }
            else
                cout << "Error en la selección.";
                cout << endl;
            break;
            
        case 9:
        
            cout << "¿De qué lenguaje quiere el cierre de kleene? ¿1 o 2? >>>> ";
            cin >> sel;
            if(sel==1){
                cout << "Cierre de kleene de ";
                A.mostrar();
                cout << " -> ";
                Kleene.kleene(A.returnlenguaje());
                cout << endl;
            }
            else if(sel==2){
                cout << "Cierre de kleene de ";
                B.mostrar();
                cout << " -> ";
                Kleene.kleene(B.returnlenguaje());
                cout << endl;
            }
            else
                cout << "Error en la selección.";
                cout << endl;
                break;
                
        case 0:break;
        default: 
            
            cout << "Opción equivocada, inserte de nuevo." << endl << endl;
            break;
            
    }
    
}while(opcion!=0);
}