#include "transicion.hpp"

transicion::transicion(char s,int t):
simbolo_(s),
trans_(t){}

int transicion::get_trans() const{
    return trans_;
}

char transicion::get_simbolo(void) const{
    return simbolo_;
}