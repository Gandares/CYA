#pragma once

#include <iostream>

using namespace std;

class bloque{
    
    private:
    
        int tamano_;
        
    public:

        bloque(int a):                                                          //Contructor para dar valor 2 o 3 a la variable "valor"
        tamano_(a){}
        
        int get_valor(void){                                                    //getter del valor
            return tamano_;
        }
        
        void set_valor(int tamano){                                             //setter del valor
            tamano_=tamano;
        }
        
        void write(ostream& os) const{
            for(int i=0;i<tamano_;i++)
                cout << "X";
        }
        
        friend ostream& operator<<(ostream& os, bloque block){
            block.write(os);
            return os;
        }
};