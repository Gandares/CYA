#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include "estado.hpp"

using namespace std;

class nfa{
    
    private:
        
        set<estado> estados_;
        set<char> alfabeto_;
        vector<string> posibles_;
        int cantidad_;
        int arranque_;
        
    public:
    
        nfa(void){}
        int get_sz(void) const;
        void read(void);
        void write(void);
        void muerte(void);
        void estado_importante(void);
        void es_dfa(void);
        void comprobar_cadena(void);
        
     private:
    
        void read(ifstream& is);
        bool empty(void);
        void get_alfabeto(void);
        void posibilidades(int actual,string cadena,int camino,int siguiente,int contador,vector<char> todo,vector<int> transi,int vacio);
        void clausura(int siguiente,vector<char> todo,vector<int> transi,int contador,int salida);
};