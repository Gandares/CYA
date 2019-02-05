#include "bloque.hpp"
#include "fila.hpp"
#include "muro.hpp"
#include "creacion.hpp"
#include <vector>

using namespace std;

int main(void){
    
    int ancho, altura;
    
    cout << "Introduzca el ancho del muro: ";
    cin >> ancho;
    cout << "Introduzca la altura del muro: ";
    cin >> altura;
    
    crear prueba(ancho,altura);
    
    cout << "Estas son las posibles filas:" << endl << endl;
    prueba.writefilas();
    cout << endl;
    
    cout << "Estos son todos los muros que se podrian crear:" << endl << endl;
    prueba.writemuros();
    cout << endl;
    
}