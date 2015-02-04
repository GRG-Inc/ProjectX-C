//
//  AI.h
//  ProjectX
//
//  Created by Gaetano Belcastro on 03/02/15.
//  Copyright (c) 2015 GRG. All rights reserved.
//

#ifndef __ProjectX__AI__
#define __ProjectX__AI__


#include <string.h>
#include "Scacchiera.h"
#include <unordered_map>
#include <cassert>
#include <cmath>
#include <iostream>
#include <ctype.h>
#include <limits>
#include <cstring>
using namespace::std;

class AI{
public:
Scacchiera getScacchiera();
string generaStringaMossa(int i, int j, int k, int l, int m, int n, int o, int p);
string generaProssimaMossa(Scacchiera s, string side, int d);
void convertiStringaMossa(string mossa);
};
#endif /* defined(__ProjectX__AI__) */
