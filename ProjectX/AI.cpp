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
#include <ctype.h>

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
    
    char corrispondenzaR(int indice) {
        switch(indice){
            case 1:
                return 'A';
            case 2:
                return 'B';
            case 3:
                return 'C';
            case 4:
                return 'D';
            case 5:
                return 'E';
            case 6:
                return 'F';
            case 7:
                return 'G';
            case 8:
                return 'H';
            case 9:
                return 'I';
            default:
                throw;
        }
    }
    
    int corrispondenza(char indice) {
        char x = toupper(indice);
        switch(x){
            case 'A':
                return 1;
            case 'B':
                return 2;
            case 'C':
                return 3;
            case 'D':
                return 4;
            case 'E':
                return 5;
            case 'F':
                return 6;
            case 'G':
                return 7;
            case 'H':
                return 8;
            case 'I':
                return 9;	
            default:
                throw;
        }
    }
    
public:
    
    AI(){
    }

    Scacchiera getScacchiera() {
        return scacchiera;
    }
    
    string generaStringaMossa(int i, int j, int k, int l, int m, int n, int o, int p){
        string sb;
        sb+corrispondenzaR(i);
        sb+=j;
        sb+=corrispondenzaR(k);
        sb+=l;
        sb+=corrispondenzaR(m);
        sb+=n;
        sb+=(corrispondenzaR(o));
        sb+=(p);
        return sb;
    }
    
    string generaProssimaMossa(Scacchiera s, string side, int d){
        valutaMossa(s, side, d, Double.NEGATIVE_INFINITY);
        return mossaFinale;
    }
};