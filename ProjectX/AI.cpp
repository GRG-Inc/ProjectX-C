//
//  AI.cpp
//  ProjectX
//
//  Created by Gaetano Belcastro on 03/02/15.
//  Copyright (c) 2015 GRG. All rights reserved.
//

#include "AI.h"
#include <string>
#include "Scacchiera.cpp"
#include <unordered_map>
#include <cassert>
#include <cmath>
#include <iostream>

using namespace::std;

class AI{
    
private:
    
    string mossaFinale;
    const char CostiCattura[14] = { 0, 8, 12, 16, 24, 36, 100, 100, 100, 100, 100, 100, 100, 100 };
    const int minColumn[10] = { 1, 1, 1, 1, 1, 1, 2, 3, 4, 5}; //da che colonna inizia la scacchiera per ogni riga compresa cornice
    const int maxColumn[10] = { 5, 5, 6, 7, 8, 9, 9, 9, 9, 9}; //a che colonna finisce la scacchiera per ogni riga compresa cornice
    char direzioni[6] = {1,2,3,4,5,6};//N,NO,O,S,SE,E
    unordered_map<int, int> distance;
    int dist;
    const char white=2, black=3;
    Scacchiera scacchiera;
    
    int calcolaDistanza(int i, int j, int k, int l){
        int col = j-l;
        int riga = i-k;
        if(col<0 ^ riga <0)
            return abs(col)+abs(riga);
        return fmax(abs(col), abs(riga));
    }
    
    void distanza(){
        int dist;
        for(int i=0; i<11; i++){
            for(int j=0; j<11; j++){
                for(int k=0; k<11; k++){
                    for(int l=0; l<11;l++){
                        int key1=(int)(i*1000+j*100+k*10+l);
                        if(distance.find(key1)==distance.end()){
                            dist=(int) calcolaDistanza(i,j,k,l);
                            distance.insert(key1, dist);
                        }
                    }
                }
            }
        }
    }

public:
    
    AI(){
    }

    Scacchiera getScacchiera() {
        return scacchiera;
    }
    
    string generaStringaMossa(int i, int j, int k, int l, int m, int n, int o, int p){
        StringBuilder sb = new StringBuilder();
        sb.append(corrispondenzaR(i));
        sb.append(j);
        sb.append(corrispondenzaR(k));
        sb.append(l);
        sb.append(corrispondenzaR(m));
        sb.append(n);
        sb.append(corrispondenzaR(o));
        sb.append(p);
        return sb.toString();
    }
    
    string generaProssimaMossa(Scacchiera s, string side, int d){
        valutaMossa(s, side, d, Double.NEGATIVE_INFINITY);
        return mossaFinale;
    }
};