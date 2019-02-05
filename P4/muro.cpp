#include "muro.hpp"

fila muro::get_fila(int pos){
    return pared_[pos];
}

void muro::push_fila(fila f){
    pared_.push_back(f);
}

void muro::pop_fila(void){
    pared_.pop_back();
}

int muro::get_largo(void){
    return largo_;
}

int muro::get_alto(void){
    return alto_;
}

int muro::get_altura_actual(void){
    return pared_.size();
}

bool muro::comparacion(fila f1, fila f2){
    
    vector<int> va;
    vector<int> vb;
    
    int a=0;
    int b=0;

    for(int i=0; i<f1.get_sz(); i++){
        a+=f1.get_bloque(i).get_valor();
        va.push_back(a);
    }

    for(int i=0; i<f2.get_sz(); i++){
        b+=f2.get_bloque(i).get_valor();
        vb.push_back(b);
    }
    for(int i=0;i<va.size()-1;i++){
        for(int j=0;j<vb.size()-1;j++){
            if(va[i]==vb[j]){
                return false;
            }
        }
    }
    return true;
}

void muro::write(ostream& os) const{
    for(int i=0;i<pared_.size();i++)
        cout << pared_[i];
}