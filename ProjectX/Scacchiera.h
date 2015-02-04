//
//  Scacchiera.h
//  ProjectX
//
//  Created by Gaetano Belcastro on 03/02/15.
//  Copyright (c) 2015 GRG. All rights reserved.
//

#ifndef __ProjectX__Scacchiera__
#define __ProjectX__Scacchiera__

#include <stdio.h>
#include <cmath>
#include <cstring>
class Scacchiera{
public:
	~Scacchiera();
	Scacchiera clona();
	int getBiancheCatturate();
	int getNereCatturate();
	char* getScacchiera();
	bool esisteCella(int riga, int colonna);
	void aggiornaScacchiera(int origP1, int origP2, int origU1, int origU2, int destP1, int destP2, int destU1, int destU2);
};

#endif /* defined(__ProjectX__Scacchiera__) */
