#include "dfa.hpp"

int dfa::get_sz(void) const{
    return cantidad_;
}

void dfa::read(void){
    
    string f;
    cout << endl << "Nombre del fichero: ";
    cin >> f;
    ifstream ifA;
    ifA.clear();
    ifA.open(f.data());
    if(!ifA)
        cout << "No existe el fichero" << endl;
    else
        read(ifA);
}

void dfa::read(ifstream& is){

    string cantidad;
    getline(is,cantidad);
    if(cantidad.size()>2){
        cout << "Error en la definición del DFA, linea 1" << endl;
        exit(0);
    }

    string arranque;
    getline(is,arranque);
    if(arranque.size()>2){
        cout << "Error en la definición del DFA, linea 2" << endl;
        exit(0);
    }
    
    int nodo;
    int numero_de_transiciones;
    int aceptacion;
    int transicion;
    char simbolo;
    int trans_max=0;
    
    cantidad_=atoi(cantidad.c_str());
    arranque_=atoi(arranque.c_str());
    
    for(int i=0;i<cantidad_;i++){
        
        if(is.eof()){
            cout << "Hay mas cantidad de nodos totales(fila 1) que los que hay realmente. Abortando..." << endl;
            exit(0);
        }
        
        is >> nodo >> aceptacion >> numero_de_transiciones;
        
        vector<int> transiciones;
        vector<char> simbolos;
        
        if(i==0)
            trans_max=numero_de_transiciones;
        else if(numero_de_transiciones!=trans_max){
            cout << "Error en el número de transiciones. Abortando..." << endl;
            exit(0);
        }
    
        for(int j=0;j<numero_de_transiciones;j++){
            is >> simbolo;
            is >> transicion;
            simbolos.push_back(simbolo);
            transiciones.push_back(transicion);
        }
        
        estado A(nodo,numero_de_transiciones,aceptacion,transiciones,simbolos);
        estados_.insert(A);
        for(int k=0;k<simbolos.size();k++)
            for(int t=k+1;t<simbolos.size();t++)
                if(simbolos[k]==simbolos[t]){
                        cout << "Error, hay dos transiciones de un mismo símbolo del alfabeto." << endl;
                        exit(0);
                }
    }
}

void dfa::write(void){
    
    if(empty())
        cout << "No hay ningún nodo en el autómata" << endl;
    else{
        cout << endl;
        cout << cantidad_ << endl;
        cout << arranque_ << endl;
        
        for(auto aux : estados_){
            
            cout << aux.get_nodo() << " ";
            if(aux.acept())
                cout << "1 ";
            else
                cout << "0 ";
            cout << aux.get_num_trans() << " ";
            
            for(int i=0;i<aux.get_vector().size();i++)
                cout << aux.get_trans(i).get_simbolo() << " " << aux.get_trans(i).get_trans() << " ";
            cout << endl;
        }
        cout << endl;
    }
}

bool dfa::empty(void){
    if(estados_.empty())
        return true;
    else
        return false;
}

void dfa::muerte(void){
    
    for(auto aux : estados_){
    
        int total=0;
        if(!aux.acept()){
            for(int i=0;i<aux.get_num_trans();i++)
                if(aux.get_trans(i).get_trans()==aux.get_nodo())
                    total++;
            if(total==aux.get_num_trans())
                cout << "El nodo " << aux.get_nodo() << " es un estado de muerte." << endl;;
        }
    }
}

void dfa::comprobar_cadena(void){
    
    string cadena;
    cout << endl << "Introduzca la cadena a comprobar: ";
    cin >> cadena;
    cout << "Estado actual\t" << "Entrada\t\t" << "Siguiente estado" << endl;
    int camino=arranque_;
    
    for(int i=0;i<cadena.size();i++){
        char aux=cadena[i];
        int siguiente;
        
        for(auto estado : estados_){
            if(estado.get_nodo()==camino){
                int actual=estado.get_nodo();
                for(int j=0;j<estado.get_num_trans();j++)
                    if(estado.get_trans(j).get_simbolo()==aux){
                        camino=estado.get_trans(j).get_simbolo();
                        siguiente=estado.get_trans(j).get_trans();
                    }
            cout << actual << "\t\t" << aux << "\t\t" << siguiente << endl;
            }
        }
        camino=siguiente;
    }
    for(auto estado : estados_)
        if(estado.get_nodo()==camino)
            if(estado.acept()==true)
                cout << "Cadena de entrada ACEPTADA" << endl;
            else 
                cout << "Cadena de entrada NO ACEPTADA" << endl;
}
