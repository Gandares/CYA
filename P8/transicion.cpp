#include "transicion.hpp"

transicion::transicion(char s,int t):
simbolo_(s),
trans_(t){}

int transicion::get_trans() const{
    return trans_;
}

void transicion::set_trans(int num){
    trans_=num;
}

char transicion::get_simbolo(void) const{
    return simbolo_;
}