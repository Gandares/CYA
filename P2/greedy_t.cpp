#include "greedy_t.hpp"

#include "point_t.hpp"

#include <set>


namespace CyA {

double greedy_t::NN(vector<point_t>& sequence)
{
    set<point_t> pending;                                                       //Define conjunto de puntos.
 
    for(const point_t& p: sky_)                                                 //Declaras variable de tipo point_t llamada p, recorres todo el vector sky.
        pending.insert(p);                                                      //Insertas en pending todos los puntos de p.
    
    point_t last = sky_[599];                                                     //Declaras un punto de salida.
    point_t origen(0,0);
    double menor=9999999;
    int contador=0;
    int p;
    
    for(int i=0;i<10;i++){
        if(sky_[i].distance(origen)<menor){
            p=i;
            menor=sky_[i].distance(origen);
            last=sky_[p];
        }
    }

    pending.erase(last);                                                        //Borras el visitado en pending.
    sequence.push_back(last);                                                   //Mandas en sequence el visitado al final.
    
    double tour_length = 0;                                                     //Declaras el recorrido final.
    
    do {
        point_t best_point    = *pending.begin();                               //Declaras el primer punto del conjunto de puntos pending.
        double  best_distance = last.distance(best_point);                      //Declaras variable double que calcula la distancia entre dos puntos con la funcion distance.
        
        for(const point_t& current: pending) {                                  //Declaras variable point_t current y recorres pending.
            
            const double current_distance = last.distance(current);             //Declaras una variable que calcule la distancia del punto actual con last.
            
            if (current_distance < best_distance) {                             //Si la distancia del punto atual es menor que la que estaba antes...
                
                best_distance = current_distance;                               //La mejor distancia pasa a ser esta.
                best_point    = current;                                        //Se cambia el mejor punto a current.
            }
        }
        
        tour_length += best_distance;                                           //Una vez acabado el bucle se suma la mejor distancia al tamaño final del tour.
        
        last = best_point;                                                      //last pasa a ser el mejor punto.
        
        pending.erase(last);                                                    //Borras last de pending para que no se vuelva a repetir.
        sequence.push_back(last);                                               //Mandas al final de sequence last.

    } while(!pending.empty());                                                  //Se hará el do hasta que pending se vacie.
    
    tour_length += last.distance(sequence[0]);                                  //Al final de todo se sumara la distancia del punto final con el del inicial, para que sea un "circulo cerrado".
    
    return tour_length;                                                         //Devuelves el tamaño del tour.
}

}