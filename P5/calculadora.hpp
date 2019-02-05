#include <set>
#include <string>
#include <iostream>

using namespace std;

class calculadora{
    
    private:
    
        set<string> lenguaje_;
    
    public:
      
      calculadora(void){}
      calculadora(string s);
      ~calculadora(void){}
      void mostrar(void);
      int get_sz(void);
      set<string> returnlenguaje(void);
      void inversa(string s);
      void concatenacion(set<string> a, set<string> b);
      void unionn(string a, string b);
      void interseccion(set<string> a, set<string> b);
      void diferencia(set<string> a, set<string> b);
      void sublenguajes(set<string> a, set<string> b);
      bool igualdad(set<string> a, set<string> b);
      set<string> potencia(set<string> se, int p);
      void kleene(set<string> se);
      
    private:
    
      void get_lenguaje(string s);
      
};