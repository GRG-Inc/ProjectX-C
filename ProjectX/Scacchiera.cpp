//
//  Scacchiera.cpp
//  ProjectX
//
//  Created by Gaetano Belcastro on 03/02/15.
//  Copyright (c) 2015 GRG. All rights reserved.
//

#include "Scacchiera.h"
#include <cmath>


class Scacchiera {
private:
    //0= casella non valida, 1=casella vuota, 2=pedina bianca, 3=pedina nera
     char scacchiera[11][11] = {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 2, 2, 1, 3, 3, 0, 0, 0, 0, 0 }, // A
        { 0, 2, 2, 2, 3, 3, 3, 0, 0, 0, 0 }, // B
        { 0, 1, 2, 2, 1, 3, 3, 1, 0, 0, 0 }, // C
        { 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 }, // D
        { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 }, // E
        { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0 }, // F
        { 0, 0, 0, 1, 3, 3, 1, 2, 2, 1, 0 }, // G
        { 0, 0, 0, 0, 3, 3, 3, 2, 2, 2, 0 }, // H
        { 0, 0, 0, 0, 0, 3, 3, 1, 2, 2, 0 }, // I
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
    
    int nereCatturate=0, biancheCatturate=0;//nereCatturate e' il numero di pedine perse da side1
    int minColumn[10] = { 1, 1, 1, 1, 1, 1, 2, 3, 4, 5}; //da che colonna inizia la scacchiera per ogni riga compresa cornice
    int maxColumn[10]  = { 5, 5, 6, 7, 8, 9, 9, 9, 9, 9}; //a che colonna finisce la scacchiera per ogni riga compresa cornice
    char bianco=2, nero=3;
    
    typedef char (&array11x11)[11][11];

    
    char getOppSide(int i, int numericValue) {
        return (scacchiera[i][numericValue] == 2)? nero: bianco;
    }
    
    char getSide(int i, int numericValue) {
        return (scacchiera[i][numericValue] == 2)? bianco: nero;
    }
    
    
    void traslaDiagonale (int numeroPedine, int i, int n1, int j, int n2){
        char side = getSide(i, n1);
        scacchiera[j][n2] = side;
        scacchiera[j+1][n2+1] = side;
        scacchiera[i][n1] = 1;
        scacchiera[i+1][n1+1] = 1;
        if(numeroPedine == 3){
            scacchiera[j+2][n2+2] = side;
            scacchiera[i+2][n1+2] = 1;
        }
    }
    
    void traslaColonna(int numeroPedine, int i, int n1, int j, int n2) {
        char side = getSide(i, n1);
        scacchiera[j][n2] = side;
        scacchiera[j+1][n2] = side;
        scacchiera[i][n1] = 1;
        scacchiera[i+1][n1] = 1;
        if(numeroPedine == 3){
            scacchiera[j+2][n2] = side;
            scacchiera[i+2][n1] = 1;
        }
    }
    
    void traslaRiga(int numeroPedine, int i, int n1, int j, int n2) {
        char side = getSide(i, n1);
        scacchiera[j][n2] = side;
        scacchiera[j][n2+1] = side;
        scacchiera[i][n1] = 1;
        scacchiera[i][n1+1] = 1;
        if(numeroPedine == 3){
            scacchiera[j][n2+2] = side;
            scacchiera[i][n1+2] = 1;
        }
    }
    
    void attacca(int k, int n1, int j, int n2) {
        char side=getSide(k, n1);
        cattura(side);
        scacchiera[j][n2] = side;
        scacchiera[k][n1] = 1;
    }
    
    void spostaNO2(int k, int n1, int j, int n2) {
        scacchiera[j][n2]=getSide(k, n1);
        scacchiera[j-2][n2-2]=getOppSide(k, n1);
        scacchiera[k][n1]=1;
    }
    
    void spostaNO(int k, int n1, int j, int n2) {
        scacchiera[j][n2]=getSide(k, n1);
        scacchiera[j-1][n2-1]=getOppSide(k, n1);
        scacchiera[k][n1]=1;
    }
    
    void spostaSE2(int i, int n1, int l, int n2) {
        scacchiera[l][n2]=getSide(i, n1);
        scacchiera[l+2][n2+2]=getOppSide(i, n1);
        scacchiera[i][n1]=1;
    }
    
    void spostaSE(int i, int n1, int l, int n2) {
        scacchiera[l][n2]=getSide(i, n1);
        scacchiera[l+1][n2+1]=getOppSide(i, n1);
        scacchiera[i][n1]=1;
    }
    
    void spostaColonna2(bool dir2, int k, int n1, int j, int n2) {
        if(dir2){
            scacchiera[j][n2]=getSide(k, n1);
            scacchiera[j+2][n2]=getOppSide(k, n1);
            scacchiera[k][n1]=1;
        }else{
            scacchiera[j][n2]=getSide(k, n1);
            scacchiera[j-2][n2]=getOppSide(k, n1);
            scacchiera[k][n1]=1;
        }
    }
    
    void spostaColonna(bool dir2, int k, int n1, int j, int n2) {
        if(dir2){
            scacchiera[j][n2]=getSide(k, n1);
            scacchiera[j+1][n2]=getOppSide(k, n1);
            scacchiera[k][n1]=1;
        }else{
            scacchiera[j][n2]=getSide(k, n1);
            scacchiera[j-1][n2]=getOppSide(k, n1);
            scacchiera[k][n1]=1;
        }
    }
    
    void spostaRiga2(bool dir1, int i, int n1, int l, int n2) {
        if(dir1){
            scacchiera[l][n2]=getSide(i, n1);
            scacchiera[l][n2-2]=getOppSide(i, n1);
            scacchiera[i][n1]=1;
        }else{
            scacchiera[l][n2]=getSide(i, n1);
            scacchiera[l][n2+2]=getOppSide(i, n1);
            scacchiera[i][n1]=1;
        }
        
    }
    
    void spostaRiga(bool dir1, int i, int n1, int l, int n2) {
        if(dir1){
            scacchiera[l][n2]=getSide(i, n1);
            scacchiera[l][n2-1]=getOppSide(i, n1);
            scacchiera[i][n1]=1;
        }else{
            scacchiera[l][n2]=getSide(i, n1);
            scacchiera[l][n2+1]=getOppSide(i, n1);
            scacchiera[i][n1]=1;
        }
    }
    
    void cattura(char side) {
        if(side == bianco)
            nereCatturate ++;
        else
            biancheCatturate ++;
    }
    
    
public:
    ~Scacchiera(){
    }
    
    /*Scacchiera(const Scacchiera&){
        
    }*/
    
    Scacchiera clona(){
        Scacchiera clone = Scacchiera();
        for(int i = 0 ; i < 11 ; i++)
            for(int j = 0 ; j < 11 ; j++){
                clone.scacchiera[i][j] = scacchiera[i][j];
            }
        clone.nereCatturate = nereCatturate;
        clone.biancheCatturate = biancheCatturate;
        return clone;
    }
    
    int getBiancheCatturate(){
        return biancheCatturate;
    }
    
    int getNereCatturate(){
        return nereCatturate;
    }
    
    char* getScacchiera(){
        return &scacchiera[0][0];
    }
    
    bool esisteCella(int riga, int colonna){
        return (riga >= 1 && riga <= 9 && colonna >= minColumn[riga] && colonna<= maxColumn[riga]);
    }
    
    /**
     *
     * @param origP1 Indice di riga prima pedina partenza
     * @param origP2 Indice di colonna prima pedina partenza
     * @param origU1 Indice di riga ultima pedina partenza
     * @param origU2 Indice di colonna ultima pedina partenza
     * @param destP1 Indice di riga prima pedina arrivo
     * @param destP2 Indice di colonna prima pedina arrivo
     * @param destU1 Indice di riga ultima pedina arrivo
     * @param destU2 Indice di colonna ultima pedina arrivo
     */
    
    void aggiornaScacchiera(int origP1, int origP2, int origU1, int origU2, int destP1, int destP2, int destU1, int destU2){
        
        int numeroPedine;//numero di pedine da muovere
        bool dir1, dir2; //dir1 false=destra true=sinistra, dir2 false=alto true=basso
        
        if(origP2 - origU2!=0)
            numeroPedine = fabs(origP2 - origU2) + 1;
        else
            numeroPedine = fabs(origP1-origU1) + 1;
        //System.out.println("numero di pedine: " + numeroPedine);
        char side1 = getSide(origP1, origP2);
        if(numeroPedine == 1){
            scacchiera[destP1][destP2] = side1;
            scacchiera[origP1][origP2] = 1;
            return;
        }
        if(origP1 == destP1 && origU1 == destU1){//movimento orizzontale
            if(origP1 == origU1){//movimento sulla stessa riga
                if((origP2 - destP2) < 0 ){//movimento verso destra
                    dir1=false;
                    if(scacchiera[destU1][destU2] == 1){//cella successiva vuota
                        scacchiera[destU1][destU2] = side1;
                        scacchiera[origP1][origP2] = 1;
                    }else if(scacchiera[destU1][destU2 + 1] == 1){
                        spostaRiga(dir1,origP1,origP2, destU1, destU2);
                    }else if(scacchiera[destU1][destU2 + 1] == 0){
                        attacca(origP1,origP2, destU1, destU2);
                    }else if(scacchiera[destU1][destU2 + 2] == 1){
                        spostaRiga2(dir1,origP1,origP2, destU1, destU2);
                    }else if(scacchiera[destU1][destU2 + 2] == 0)
                        attacca(origP1,origP2, destU1, destU2);
                }else {//movimento verso sinistra
                    dir1=true;
                    if(scacchiera[destP1][destP2] == 1){//cella successiva vuota
                        scacchiera[origU1][origU2] = 1;
                        scacchiera[destP1][destP2] = side1;
                    }else if(scacchiera[destP1][destP2 - 1] == 1){
                        spostaRiga(dir1,origU1,origU2,destP1,destP2);
                    }else if(scacchiera[destP1][destP2 - 1] == 0){
                        attacca(origU1,origU2,destP1,destP2);
                    }else if(scacchiera[destP1][destP2 - 2] == 1){
                        spostaRiga2(dir1,origU1,origU2,destP1,destP2);
                    }else if(scacchiera[destP1][destP2 - 2] == 0){
                        attacca(origU1,origU2,destP1,destP2);
                    }
                }
            }else if (origP2 == origU2){//movimento di pedine allineate verticalmente
                traslaColonna(numeroPedine, origP1, origP2, destP1, destP2);
            }else{
                traslaDiagonale(numeroPedine, origP1, origP2, destP1, destP2);
            }
        }else if(origP2 == destP2 && origU2 == destU2){
            if(origP2 == origU2){//movimento sulla stessa colonna
                if(origP1 > destP1 ){//movimento verso l'alto
                    dir2=false;
                    if(scacchiera[destP1][destP2] == 1){
                        scacchiera[origU1][origU2] = 1;
                        scacchiera[destP1][destP2] = side1;
                    }else if(scacchiera[destP1-1][destP2] == 1){
                        spostaColonna(dir2,origU1,origU2,destP1,destP2);
                    }else if(scacchiera[destP1-1][destP2] == 0){
                        attacca(origU1,origU2,destP1,destP2);
                    }else if(scacchiera[destP1-2][destP2] == 1){
                        spostaColonna2(dir2,origU1,origU2,destP1,destP2);
                    }else if(scacchiera[destP1-2][destP2] == 0){
                        attacca(origU1,origU2,destP1,destP2);
                    }
                }else{//movimento verso il basso
                    dir2=true;
                    if(scacchiera[destU1][destU2] == 1){
                        scacchiera[origP1][origP2] = 1;
                        scacchiera[destU1][destU2] = side1;
                    }else if(scacchiera[destU1+1][destU2] == 1){
                        spostaColonna(dir2, origP1, origP2, destU1, destU2);
                    }else if(scacchiera[destU1+1][destU2] == 0){
                        attacca(origP1, origP2,destU1,destU2);
                    }else if(scacchiera[destU1+2][destU2] == 1){
                        spostaColonna2(dir2, origP1, origP2, destU1, destU2);
                    }else if(scacchiera[destU1+2][destU2] == 0){
                        attacca(origP1,origP2,destU1,destU2);
                    }
                }
            }else if(origP1 == origU1){//movimento di pedine allineate orizzontalmente
                traslaRiga(numeroPedine, origP1, origP2, destP1, destP2);
            }else{
                traslaDiagonale(numeroPedine, origP1, origP2, destP1, destP2);
                
            }
        }else if(origP1 < destP1 && origU1 < destU1 && origP2 < destP2 && origU2 < destU2){//movimento sud-est
            if(origP1 == origU1){//pedine allineate orizzontalmente(singola o gruppo?)
                traslaRiga(numeroPedine,origP1,origP2,destP1,destP2);
            }else if(origP2 == origU2){//pedine allineate verticalmente (singola o gruppo?)
                traslaColonna(numeroPedine,origP1,origP2,destP1,destP2);
            }else if(origP2 < origU2){//movimento pedine allineate oblique dall'alto verso il basso (cosi \)
                if(scacchiera[destU1][destU2] == 1){
                    scacchiera[origP1][origP2] = 1;
                    scacchiera[destU1][destU2] = side1;
                }else if(scacchiera[destU1+1][destU2 + 1] == 1){
                    spostaSE(origP1,origP2,destU1,destU2);
                }else if(scacchiera[destU1+1][destU2 + 1] == 0){
                    attacca(origP1,origP2,destU1,destU2);
                }else if(scacchiera[destU1+2][destU2 + 2] == 1){
                    spostaSE2(origP1,origP2,destU1,destU2);
                }else if(scacchiera[destU1+2][destU2 + 2] == 0){
                    attacca(origP1,origP2,destU1,destU2);
                }
            }
        }else if(origP1 > destP1 && origU1 > destU1 && origP2 > destP2 && origU2 > destU2){//movimento nord-ovest
            if(origP1 == origU1){//pedine allineate orizzontalmente(singola o gruppo?)
                traslaRiga(numeroPedine, origP1, origP2, destP1, destP2);
            }else if(origP2 == origU2){//pedine allineate verticalmente (singola o gruppo?)
                traslaColonna(numeroPedine, origP1, origP2, destP1, destP2);
            }else if(origP2 < origU2){//movimento pedine allineate oblique dal basso verso l'alto(cosi \)
                if(scacchiera[destP1][destP2] == 1){
                    scacchiera[origU1][origU2] = 1;
                    scacchiera[destP1][destP2] = side1;
                }else if(scacchiera[destP1-1][destP2 - 1] == 1){
                    spostaNO(origU1,origU2,destP1,destP2);
                }else if(scacchiera[destP1-1][destP2-1] == 0){
                    attacca(origU1,origU2,destP1,destP2);
                }else if(scacchiera[destP1-2][destP2-2] == 1){
                    spostaNO2(origU1,origU2,destP1,destP2);
                }else if(scacchiera[destP1-2][destP2-2] == 0){
                    attacca(origU1,origU2,destP1,destP2);
                }
            }
        }
    }
};