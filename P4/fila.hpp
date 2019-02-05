#pragma once

#include <iostream>
#include <vector>
#include "bloque.hpp"

using namespace std;

class fila{
    
    private:
    
        vector<bloque> capa_;
        int longitud_;
        int tam_actual_;
        
    public:
    
        fila(int longitud);
        void push_bloque(bloque block);
        void pop_bloque(void);
        bloque get_bloque(int pos);
        int get_sz(void);
        int get_tam_actual(void);
        int get_long(void);
        void write(ostream& os) const;
                
        friend ostream& operator<<(ostream& os, fila f){
            f.write(os);
            return os;
        }
};

