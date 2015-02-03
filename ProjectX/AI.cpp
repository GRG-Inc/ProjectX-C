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

class AI{
private:
    std::string mossaFinale;
    const char CostiCattura[14] = { 0, 8, 12, 16, 24, 36, 100, 100, 100, 100, 100, 100, 100, 100 };
    const int minColumn[10] = { 1, 1, 1, 1, 1, 1, 2, 3, 4, 5}; //da che colonna inizia la scacchiera per ogni riga compresa cornice
    const int maxColumn[10] = { 5, 5, 6, 7, 8, 9, 9, 9, 9, 9}; //a che colonna finisce la scacchiera per ogni riga compresa cornice
    char direzioni[6] = {1,2,3,4,5,6};//N,NO,O,S,SE,E
    std::unordered_map<int, int> distance;
    int dist;
    const char white=2, black=3;
    Scacchiera scacchiera;
    
    
public:
    
    
};