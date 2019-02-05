#pragma once

#include <iostream>
#include <vector>
#include "fila.hpp"
#include "bloque.hpp"

using namespace std;

class muro{
    
    private:
    
        int largo_;
        int alto_;
        vector<fila> pared_;
        
    public:
    
        muro(int l, int h):
        largo_(l),
        alto_(h){}
        
        fila get_fila(int pos);
        void push_fila(fila f);
        void pop_fila(void);
        int get_largo(void);
        int get_alto(void);
        int get_altura_actual(void);
        int num_filas(void);
        bool comparacion(fila f1, fila f2);
        void write(ostream& os) const;

        friend ostream& operator<<(ostream& os, muro m){
            m.write(os);
            return os;
        }
};

