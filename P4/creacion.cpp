#include "creacion.hpp"

crear::crear(int l, int a){
    
    generar_filas(fila(l));
    unsigned t0,t1;
    t0=clock();
    generar_pared(muro(l,a));
    t1=clock();
    tiempo=(double(t1-t0)/CLOCKS_PER_SEC);
}

void crear::generar_filas(fila f){
    if(f.get_long()==f.get_tam_actual()){
        posibles_.push_back(f);
    }
    else if(f.get_long()>f.get_tam_actual()){
        f.push_bloque(bloque(2));
        generar_filas(f);
        f.pop_bloque();
        f.push_bloque(bloque(3));
        generar_filas(f);
    }
}

void crear::generar_pared(muro m){
    for(int i=0;i<posibles_.size();i++){
        if(m.get_alto()==m.get_altura_actual()){
            validos_.push_back(m);
            return;
        }
        else if(m.get_alto()>m.get_altura_actual()){
            m.push_fila(posibles_[i]);
            if(m.get_altura_actual()==1)
                generar_pared(m);
            else{
                fila ult=m.get_fila(m.get_altura_actual()-1);
                fila pen=m.get_fila(m.get_altura_actual()-2);
                if(m.comparacion(ult,pen)==true)
                     generar_pared(m);
            }
        }
        m.pop_fila();
    }
}

void crear::writemuros(void) const{
    for(int i=0;i<validos_.size();i++)
       cout << validos_[i] << endl;
}

void crear::writefilas(void) const{
    for(int i=0;i<posibles_.size();i++)
        cout << posibles_[i];
}