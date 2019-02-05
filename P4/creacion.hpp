#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include "muro.hpp"
#include "fila.hpp"
#include "bloque.hpp"

using namespace std;

class crear{
    
    private:
    
        vector<muro> validos_;
        vector<fila> posibles_;
        double tiempo;
    
    public:
    
        crear(int l, int a);
        void generar_filas(fila f);
        void generar_pared(muro m);
        void writemuros(void) const;
        void writefilas(void) const;
    
};
