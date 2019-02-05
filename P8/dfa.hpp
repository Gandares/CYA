#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <algorithm>
#include "estado.hpp"

using namespace std;

class dfa{
    
    private:
        
        set<estado> estados_;
        set<char> alfabeto_;
        int cantidad_;
        int arranque_;
        
    public:
    
        dfa(void){}
        int get_sz(void) const;
        void read(void);
        void write(void);
        void muerte(void);
        void comprobar_cadena(void);
        void minimizar(void);
        void exportar(void);

    private:
    
        estado get_estado(int n);
        void read(ifstream& is);
        bool empty(void);
        void get_alfabeto(void);
        set<set<estado>> crear_nueva_particion(set<set<estado>> total_viejo);
        set<set<estado>> descomponer(set<set<estado>> total_viejo, set<estado> G);
        set<set<estado>> part(set<estado> G, char symbol, set<set<estado>> total_viejo);
        void print(set<estado> C);
        void print(set<set<estado>> C);
        bool contenido(set<estado> cactual, int x);
        bool alldim1(set<set<estado>> c);
};