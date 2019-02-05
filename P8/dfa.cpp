#include "dfa.hpp"

estado dfa::get_estado(int n){
    
    int cont=0;
    for(set<estado>::iterator it=estados_.begin();it!=estados_.end();it++){
        if(cont==n)
            return(*it);
        cont++;
    }
}

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

    estados_.clear();
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

void dfa::minimizar(void){
    
    set<set<estado> > total;
    
    get_alfabeto();
    
    set<estado> acept;
    set<estado> no_acept;
    
    for(auto estado : estados_){
        if(estado.acept())
            acept.insert(estado);
        else
            no_acept.insert(estado);
    }
    total.insert(acept);
    total.insert(no_acept);
    
    set<set<estado> > total_viejo;
    
    cout << endl << "Particion inicial: ";
    print(total);
    cout << endl << endl << endl;
    int x=1;
    
    do{
        
        total_viejo=total;
        total=crear_nueva_particion(total_viejo);
        print(total);
        cout << endl << endl;
        x++;
    
    }while(!(equal(total_viejo.begin(),total_viejo.end(),total.begin()))&&!(alldim1(total)));
        
    total_viejo=total;                                                          //DUDA
    cout << endl << "Particion final: ";
    print(total_viejo);
    cout << endl << endl;
    cout << "El DFA minimo tiene " << total_viejo.size() << " estados" << endl;
    
    vector<int> total_borrados;
    for(set<set<estado>>::iterator it=total_viejo.begin();it!=total_viejo.end();it++){
        if((*it).size()>1){
            int sz=(*it).size();
            int contador=1;
            int lol=0;
            vector<int> borrados;
            for(auto aux : (*it)){
                if(arranque_==aux.get_nodo())
                    lol=1;
                if(contador==sz){
                    if(lol==1)
                        arranque_=aux.get_nodo();
                    for(auto aux2 : estados_){
                        if(aux2.get_nodo()==aux.get_nodo()){
                            for(int i=0;i<aux2.get_num_trans();i++){
                                for(int j=0;j<borrados.size();j++){
                                    if(aux2.get_trans(i).get_trans()==borrados[j])
                                        aux2.get_trans(i).set_trans(aux.get_nodo());
                                }
                            }
                        }
                    }
                    contador++;
                }
                else if(contador<sz){
                    borrados.push_back(aux.get_nodo());
                    total_borrados.push_back(aux.get_nodo());
                    for(auto est : estados_){
                        if(aux.get_nodo()==est.get_nodo())
                            estados_.erase(est);
                    }
                    contador++;
                }
            }
        }
        
    }
    for(set<set<estado>>::iterator it=total_viejo.begin();it!=total_viejo.end();it++){
        if((*it).size()==1){
            for(auto aux : (*it)){
                for(auto aux2 : estados_){
                    if(aux.get_nodo()==aux2.get_nodo()){
                        for(int i=0;i<aux2.get_num_trans();i++){
                            for(int j=0;j<total_borrados.size();j++){
                                if(aux2.get_trans(i).get_trans()==total_borrados[j])
                                    aux2.get_trans(i).set_trans(aux.get_nodo());
                            }
                        }
                    }
                }
            }
        }
    }
    cantidad_=estados_.size();
    vector<int> nodos(estados_.size());
    int cont=0;
    for(auto aux : estados_){
        nodos[cont]=aux.get_nodo();
        cont++;
    }
}

set<set<estado>> dfa::crear_nueva_particion(set<set<estado> > total_viejo){
    
    set<set<estado> > total;
    set<set<estado> > auxiliar;
    
    for(set<set<estado>>::iterator it=total_viejo.begin();it!=total_viejo.end();it++){
       auxiliar.insert((*it));
       if((*it).size()>1){
            auxiliar=descomponer(total_viejo,(*it));
        }
        set_union(total.begin(),total.end(),auxiliar.begin(),auxiliar.end(),inserter(total,total.begin()));
    }
    return total;
}

set<set<estado>> dfa::descomponer(set<set<estado> > total_viejo, set<estado> G){
    
    set<set<estado> > auxiliar;
    auxiliar.insert(G);
    set<set<estado> > pmt;
   
    bool mejora=0;
    for(set<char>::iterator it=alfabeto_.begin();it!=alfabeto_.end();it++){
        set<set<estado> > P;
        P=part(G,(*it),total_viejo);
        if(P!=auxiliar&&!mejora){
            set_union(pmt.begin(),pmt.end(),P.begin(),P.end(),inserter(pmt,pmt.begin()));            
            mejora=1;
        }
        cout << "Con el símbolo '" << (*it) << "': ";
        print(P);
        cout << endl << endl;
    }
    if(pmt.size()!=0){
        auxiliar=pmt;
    }
    return auxiliar;
}

set<set<estado>> dfa::part(set<estado> G, char symbol, set<set<estado> > total_viejo){
    
    set<set<estado> > T;
        
    for(set<set<estado>>::iterator it=total_viejo.begin();it!=total_viejo.end();it++){
        set<estado> P;
        int estado_siguiente;
        for(auto aux : G){ 
            for(int i=0;i<aux.get_num_trans();i++)
                if(aux.get_trans(i).get_simbolo()==symbol)
                    estado_siguiente=aux.get_trans(i).get_trans();
            if(contenido((*it),estado_siguiente)){
                P.insert(aux); 
            }
        }
        if(P.size()!=0)
            T.insert(P);
    }
    return T;
}

void dfa::get_alfabeto(void){
    
    for(auto aux : estados_)
        for(int i=0;i<aux.get_vector().size();i++)
            alfabeto_.insert(aux.get_trans(i).get_simbolo());
}

void dfa::print(set<estado> C){
    
    cout<<"{";
    int m=0;
    int x=C.size();
	for(set<estado>::iterator it=C.begin();it!=C.end();it++){
	    cout << (*it).get_nodo(); 
	    m++;
	    if(m!=x){
	        cout << ", ";
	    }
	}
	cout<<"}";
}

void dfa::print(set<set<estado>> C){
    
    cout<<"{";
    int m=0;
    int x=C.size();
	for(set<set<estado>>::iterator it=C.begin();it!=C.end();it++){
	    print((*it));
	    m++;
	    if(m!=x){
	        cout << ",";
	    }
    }
    cout << "}";
}

bool dfa::contenido(set<estado> cactual, int x){
    
    for(set<estado>::iterator it=cactual.begin();it!=cactual.end();it++)
        if((*it).get_nodo()==x)
            return true;
    return false;
}

bool dfa::alldim1(set<set<estado>> c){
    
    for(set<set<estado>>::iterator it=c.begin();it!=c.end();it++)
        if((*it).size()>1)
            return false;
    return true;
}

void dfa::exportar(void){
    
    ofstream salida("salida.dfa",ofstream::out);
    
    salida << cantidad_ << endl;
    salida << arranque_ << endl;
    
    for(auto aux :  estados_){
        
        salida << aux.get_nodo() << " ";
        
        if(aux.acept())
            salida << "1 ";
        else
            salida << "0 ";
            
        salida << aux.get_num_trans() << " ";
        
        for(int j=0;j<aux.get_num_trans();j++)
            salida << aux.get_trans(j).get_simbolo() << " " << aux.get_trans(j).get_trans() << " ";
        salida << endl;

    }
    
    salida.close();
}