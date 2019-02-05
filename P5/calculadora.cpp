#include "calculadora.hpp"

calculadora::calculadora(string s){
    get_lenguaje(s);
}

void calculadora::mostrar(void){
    cout << "{";
    for(set<string>::iterator it=lenguaje_.begin();it!=lenguaje_.end();it++)
            cout << ' ' << *it << ",";
    cout << "}";
}

int calculadora::get_sz(void){
    return lenguaje_.size();
}

set<string> calculadora::returnlenguaje(void){
    return lenguaje_;
}

void calculadora::inversa(string s){
    string aux;
    int contador=0;
    for(int i=s.size()-2;i>0;i--){
        if(s[i]==','){
            lenguaje_.insert(aux);
            contador=0;
            aux.clear();
        }
        else{
            aux.push_back(s[i]);
            contador++;
        }
    }
    lenguaje_.insert(aux);
}

void calculadora::concatenacion(set<string> a, set<string> b){
   
   lenguaje_.clear();
    for(set<string>::iterator it1=a.begin();it1!=a.end();it1++)
        for(set<string>::iterator it2=b.begin();it2!=b.end();it2++){
            string aux;
            aux.append(*it1);
            aux.append(*it2);
            lenguaje_.insert(aux);
        }
}

void calculadora::unionn(string a, string b){

    get_lenguaje(a);
    get_lenguaje(b);
    
}

void calculadora::interseccion(set<string> a, set<string> b){
    
    for(set<string>::iterator it1=a.begin();it1!=a.end();it1++)
        for(set<string>::iterator it2=b.begin();it2!=b.end();it2++)
            if(*it1==*it2)
                lenguaje_.insert(*it1);
}

void calculadora::diferencia(set<string> a, set<string> b){
    
    for(set<string>::iterator it1=a.begin();it1!=a.end();it1++){
        int aux=0;
        for(set<string>::iterator it2=b.begin();it2!=b.end();it2++)
            if(*it1==*it2)
                aux++;
        if(aux==0)
            lenguaje_.insert(*it1);
    }
}

void calculadora::sublenguajes(set<string> a, set<string> b){
    
    int x=0;
    for(set<string>::iterator it1=a.begin();it1!=a.end();it1++)
        for(set<string>::iterator it2=b.begin();it2!=b.end();it2++)
            if(*it1==*it2)
                x++;
    if(x==b.size()&&x==a.size())
        cout << "Lenguaje 2 está contenido en lenguaje 1 y viceversa (son iguales).";
    else if(x==b.size())
        cout << "Lenguaje 2 está contenido en lenguaje 1.";
    else if(x==a.size())
        cout << "Lenguaje 1 está contenido en lenguaje 2.";
    else
        cout << "No tienen relacion.";
}

bool calculadora::igualdad(set<string> a, set<string> b){
    
    for(set<string>::iterator it1=a.begin(), it2=b.begin();it1!=a.end()&&it2!=b.end();it1++,it2++)
        if(*it1!=*it2)
            return false;
    return true;
}

set<string> calculadora::potencia(set<string> se, int p){
    
    if(p==0){
        lenguaje_.insert("&");
        return lenguaje_;
    }
    else if(p==1){
        lenguaje_=se;
        return lenguaje_;
    }
    else{
        int x=2;
        concatenacion(se,se);
        while(x<p){
            concatenacion(lenguaje_,se);
            x++;
        }
        return lenguaje_;
    }
}

void calculadora::kleene(set<string> se){
    
    set<string> aux;
    cout << "{ ";
    for(int i=0;i<5;i++){
        potencia(se,i);
        for(set<string>::iterator it=lenguaje_.begin();it!=lenguaje_.end();it++)
            cout << ' ' << *it << ",";
    }
    cout << " ... }";
}

void calculadora::get_lenguaje(string s){
    string aux;
    int contador=0;
    for(int i=1;i<s.size()-1;i++){
        if(s[i]==','){
            lenguaje_.insert(aux);
            contador=0;
            aux.clear();
        }
        else{
            aux.push_back(s[i]);
            contador++;
        }
    }
    lenguaje_.insert(aux);
}