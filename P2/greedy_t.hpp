#pragma once

#include "sky_t.hpp"
#include "point_t.hpp"

#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

namespace CyA
{
    
class greedy_t
{
    private:
        const sky_t& sky_;                                                      //Variable vector de point_t que son pares de coordenadas.

    public:
        greedy_t(const sky_t& sky):                                             //Constructor del cielo.
        sky_(sky) {}                                                            // sky->sky_   x->1000, y->1000, 600 estrellas.
    
        ~greedy_t(void) {}                                                      //Destructor.
    
        double NN(vector<point_t>& sequence);                                   //Función del algoritmo greedy.
        
        void write(ostream& os);                                                //Función write.
};



}
