#include "sorted_vector_t.hpp"

#include <climits>
#include <iomanip>

namespace CyA
{

void sorted_vector_t::merge_sort(void)
{
    merge_sort(0, size() - 1);
}

void sorted_vector_t::write(ostream& os) const
{
    const int sz = size();

    os << "< ";
    for(int i = 0; i < sz; i++)
        os << setw(5) << at(i);
    os << "> ";
}


void sorted_vector_t::merge_sort(int l, int r)
{
    static int contador=0;
    if (l < r) {
        
        int c=(l+r)/2;
    
        merge_sort(l, c);
        contador++;
        merge_sort(c + 1, r);
        contador++;
        merge(l, c, r);
    }
    cout << contador << ", " << endl;
}


////////////////////////////////////////////////////////////////////////////
// FUSIÓN CON CENTINELA
////////////////////////////////////////////////////////////////////////////

void sorted_vector_t::create_vector_sentinel(int l, int r, vector<int>& v)
{
    v.clear();
    for(int i=l;i<=r;i++)
        v.push_back(at(i));
    v.push_back(INT_MAX);
}

void sorted_vector_t::merge(int l, int c, int d)
{
    vector<int> v1;
    vector<int> v2;
    create_vector_sentinel(l,c,v1);
    create_vector_sentinel(c+1,d,v2);
    merge(v1,v2,l);
}

void sorted_vector_t::merge(const vector<int>& v1, const vector<int>& v2, int l)
{
    int sz=v1.size()+v2.size()-2;
    int aux1=0, aux2=0;
    for(int i=0;i<sz;i++){
        if(v1[aux1]<v2[aux2]){
            at(l+i)=v1[aux1];
            aux1++;
        }
        else{
            at(l+i)=v2[aux2];
            aux2++;
        }
    }
    
}

////////////////////////////////////////////////////////////////////////////
// ITERATIVO
////////////////////////////////////////////////////////////////////////////

int sorted_vector_t::min(int x, int y) { return (x<y)? x :y; }

void sorted_vector_t::merge_sort_iterative()
{
   int csize;
   int izq;
   for (csize=1; csize<=size()-1; csize = 2*csize){
       for (izq=0; izq<size()-1; izq += 2*csize){
           int mid = izq + csize - 1;
           int der = min(izq + 2*csize - 1, size()-1);
           cout << 1;
           merge_iterative(izq, mid, der);
       }
   }
}

void sorted_vector_t::merge_iterative(int l, int c, int d)
{
    vector<int> v1;
    vector<int> v2;
    create_vector_sentinel(l,c,v1);
    create_vector_sentinel(c+1,d,v2);
    
    int sz=v1.size()+v2.size()-2;
    int aux1=0, aux2=0;
    for(int i=0;i<sz;i++){
        if(v1[aux1]<v2[aux2]){
            at(l+i)=v1[aux1];
            aux1++;
        }
        else{
            at(l+i)=v2[aux2];
            aux2++;
        }
    }
}
}

ostream& operator<<(ostream& os, const CyA::sorted_vector_t& v)
{
    v.write(os);
    return os;
}

