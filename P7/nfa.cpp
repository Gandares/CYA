#include "nfa.hpp"

int nfa::get_sz(void) const{
    return cantidad_;
}

void nfa::read(void){
    
    estados_.clear();
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

void nfa::read(ifstream& is){

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
    
        for(int j=0;j<numero_de_transiciones;j++){
            is >> simbolo;
            is >> transicion;
            simbolos.push_back(simbolo);
            transiciones.push_back(transicion);
        }
        
        estado A(nodo,numero_de_transiciones,aceptacion,transiciones,simbolos);
        estados_.insert(A);
    }
}

void nfa::write(void){
    
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

bool nfa::empty(void){
    if(estados_.empty())
        return true;
    else
        return false;
}

void nfa::muerte(void){
    
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

void nfa::estado_importante(void){
    
    get_alfabeto();
    for(auto aux : estados_){
        if(aux.acept())
            cout << "El nodo " << aux.get_nodo() << " es un estado importante. " << endl;
        else{
            if(aux.get_vector().size()>=alfabeto_.size()){
                set<char> simbolos_nodo;
                for(int i=0;i<aux.get_vector().size();i++)
                    simbolos_nodo.insert(aux.get_trans(i).get_simbolo());   
                if(simbolos_nodo==alfabeto_)
                    cout << "El nodo " << aux.get_nodo() << " es un estado importante. " << endl;
                else
                    cout << "El nodo " << aux.get_nodo() << " no es un estado importante. " << endl;
            }
            else
                cout << "El nodo " << aux.get_nodo() << " no es un estado importante. " << endl;
        }
    }
}

void nfa::es_dfa(void){
    
    get_alfabeto();
    int size=0;
    int contador=0;
    for(auto aux : estados_){
        if(alfabeto_.size()==aux.get_vector().size()){
            set<char> prueba;
            for(int i=0;i<aux.get_vector().size();i++)
                prueba.insert(aux.get_trans(i).get_simbolo()); 
            if(prueba==alfabeto_)
                contador++;
        }
        size++;
    }
    if(contador==size)
        cout << "Es un DFA." << endl;
    else
        cout << "No es un DFA." << endl;
}

void nfa::get_alfabeto(void){
    
    for(auto aux : estados_)
        for(int i=0;i<aux.get_vector().size();i++)
            alfabeto_.insert(aux.get_trans(i).get_simbolo());
}

void nfa::comprobar_cadena(void){
    
    string cadena;
    cout << endl << "Introduzca la cadena a comprobar: ";
    cin >> cadena;
    int camino=arranque_;
    int contador=-1;
    vector<char> todo(cadena.size());
    vector<int> transi(cadena.size()+1);
    posibilidades(0,cadena,camino,arranque_,contador,todo,transi,0);
}

void nfa::posibilidades(int actual,string cadena,int camino,int siguiente,int contador,vector<char> todo,vector<int> transi,int vacio){
    
    camino=siguiente;
    int aux1=camino;
    if(vacio==0)
        contador++;
    char aux=cadena[contador];
    if(contador==cadena.size()-1){
        for(auto estado : estados_){
            if(estado.get_nodo()==aux1){
                actual=estado.get_nodo();
                for(int j=0;j<estado.get_num_trans();j++)
                    if(estado.get_trans(j).get_simbolo()==aux){
                        siguiente=estado.get_trans(j).get_trans();
                        camino=siguiente;
                        todo[contador]=aux;
                        transi[contador]=actual;
                        int salida;
                        clausura(siguiente,todo,transi,contador,salida);
                        }
                    else if(estado.get_trans(j).get_simbolo()=='~'){
                        siguiente=estado.get_trans(j).get_trans();
                        posibilidades(actual,cadena,camino,siguiente,contador,todo,transi,1);
                    }
                }
            }
        }
    else if(contador<cadena.size()){
        for(auto estado : estados_){
            if(estado.get_nodo()==aux1){
                actual=estado.get_nodo();
                for(int j=0;j<estado.get_num_trans();j++){
                    if(estado.get_trans(j).get_simbolo()==aux){
                        siguiente=estado.get_trans(j).get_trans();
                        todo[contador]=aux;
                        transi[contador]=actual;
                        posibilidades(actual,cadena,camino,siguiente,contador,todo,transi,0);
                    }
                    else if(estado.get_trans(j).get_simbolo()=='~'){
                        siguiente=estado.get_trans(j).get_trans();
                        posibilidades(actual,cadena,camino,siguiente,contador,todo,transi,1);
                    }
                }
            }
        }
    }
}

void nfa::clausura(int siguiente,vector<char> todo,vector<int> transi, int contador,int salida){
    salida=0;
    int aux2=siguiente;
    for(auto estados : estados_)
        if(estados.get_nodo()==aux2){
            if(estados.acept()){
                transi[contador+1]=siguiente;
                cout << "Estado actual\t" << "Entrada\t\t" << "Siguiente estado" << endl;
                for(int i=0;i<todo.size();i++)
                    cout << transi[i] << "\t\t" << todo[i] << "\t\t" << transi[i+1] << endl;
                cout << "Cadena de entrada ACEPTADA" << endl;
            }
            else{
                for(int i=0;i<estados.get_num_trans();i++)
                    if(estados.get_trans(i).get_simbolo()=='~'){
                        salida++;
                        siguiente=estados.get_trans(i).get_trans();
                        clausura(siguiente,todo,transi,contador,salida);
                    }
                    if(salida==0){
                    transi[contador+1]=siguiente;
                        cout << "Estado actual\t" << "Entrada\t\t" << "Siguiente estado" << endl;
                    for(int i=0;i<todo.size();i++)
                        cout << transi[i] << "\t\t" << todo[i] << "\t\t" << transi[i+1] << endl;
                    cout << "Cadena de entrada NO ACEPTADA" << endl;
                    }
            }
        }
}