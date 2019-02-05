#pragma once

#include <vector>
#include <set>
#include "transicion.hpp"

using namespace std;

class estado{
    
    private:
    
        int nodo_;
        int num_trans_;
        int aceptacion_;
        vector<transicion> transiciones_;
         
    public:
    
        estado(int n,int num, int a, vector<int> transiciones, vector<char> simbolos);
        int get_num_trans(void) const;
        int get_nodo(void) const;
        bool acept(void) const;
        transicion get_trans(int a);
        vector<transicion> get_vector(void);
        bool operator<(const estado &rhs) const{ return nodo_ < rhs.nodo_; }
};