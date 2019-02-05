#include "fila.hpp"

fila::fila(int longitud):
longitud_(longitud),
tam_actual_(0)
{}

void fila::push_bloque(bloque block){
    tam_actual_+=block.get_valor();
    capa_.push_back(block);
}

void fila::pop_bloque(void){
    tam_actual_-=capa_[capa_.size()-1].get_valor();
    capa_.pop_back();
}

bloque fila::get_bloque(int pos){
    return capa_[pos];
}

int fila::get_sz(void){
    return capa_.size();
}

int fila::get_tam_actual(void){
    return tam_actual_;
}

int fila::get_long(void){
    return longitud_;
}

void fila::write(ostream& os) const{
    cout << "|";
    for(int i=0;i<capa_.size();i++)
        cout << capa_[i] << "|";
    cout << endl;
}