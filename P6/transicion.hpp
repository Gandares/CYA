#pragma once

using namespace std;

class transicion{
    
    private:
    
        char simbolo_;
        int trans_;
        
    public:
    
        transicion(char s,int t);
        int get_trans(void) const;
        char get_simbolo(void) const;
};