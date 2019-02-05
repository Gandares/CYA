#include "estado.hpp"

estado::estado(int n, int num, int a, vector<int> transiciones, vector<char> simbolos):
nodo_(n),
num_trans_(num),
aceptacion_(a){
    
    for(int i=0;i<transiciones.size();i++){
        transicion T(simbolos[i],transiciones[i]);
        transiciones_.push_back(T);
    }
}

int estado::get_num_trans(void) const{
    return num_trans_;
}

int estado::get_nodo(void) const{
    return nodo_;   
}

void estado::set_nodo(int n){
    nodo_=n;
}

void estado::set_acept(int n){
    aceptacion_=n;
}

bool estado::acept(void) const{
    if(aceptacion_==1)
        return true;
    else
        return false;
}

transicion estado::get_trans(int a){
    return transiciones_[a];
}

vector<transicion> estado::get_vector(void){
    return transiciones_;
}