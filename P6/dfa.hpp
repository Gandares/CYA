#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include "estado.hpp"

using namespace std;

class dfa{
    
    private:
        
        set<estado> estados_;
        int cantidad_;
        int arranque_;
        
    public:
    
        dfa(void){}
        int get_sz(void) const;
        void read(void);
        void write(void);
        void muerte(void);
        void comprobar_cadena(void);

    private:
    
        void read(ifstream& is);
        bool empty(void);
};