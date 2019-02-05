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
        void set_nodo(int n);
        void set_acept(int n);
        bool acept(void) const;
        transicion get_trans(int a);
        vector<transicion> get_vector(void);
        bool operator<(const estado &rhs) const{ return nodo_ < rhs.nodo_; }
        bool operator==(const estado &rhs) const{
            int cont=0;
            if(nodo_==rhs.nodo_)
                cont++;
            else return false;
            if(num_trans_==rhs.num_trans_)
                cont++;
            else return false;
            if(aceptacion_==rhs.aceptacion_)
                cont++;
            else return false;
            for(int i=0;i<num_trans_;i++)
                if((transiciones_[i].get_trans()==rhs.transiciones_[i].get_trans())&&(transiciones_[i].get_simbolo()==rhs.transiciones_[i].get_simbolo()))
                    cont++;
            if(cont==(3+num_trans_))
                return true;
            else
                return false;
        }
};