#include "Konfiguration.h"


Konfiguration::Konfiguration() : anzahlPl(0), anzahlBl(0)
{

}

Konfiguration::Konfiguration(int menge) : anzahlPl(menge+1), anzahlBl(menge)   //anzahl der Plätze muss menge+1 sein, damit Indizes von 1 bis menge gehen
{
    plaetze = new Platz*[anzahlPl];
    for(int i = 0; i <= anzahlPl; ++i)
    {
        plaetze[i] = new Platz(anzahlBl);
    }
}

Konfiguration::Konfiguration(int menge, int bloecke) : anzahlPl(menge+1), anzahlBl(bloecke)
{
    plaetze = new Platz*[anzahlPl];
    for(int i = 0; i <= anzahlPl; ++i)
    {
        plaetze[i] = new Platz(anzahlBl);
    }
}

Konfiguration::~Konfiguration()
{

}
//-------------------------------------------------------------------
void Konfiguration::addBlock(int name, int platz)
{
    if(platz < anzahlPl){
        plaetze[platz]->addBlock(name);
    }
}

int Konfiguration::nameOfBlock(int platz, int block)
{
    if(platz < anzahlPl){
        return plaetze[platz]->getName(block);
    }
    return 0;
}

int Konfiguration::nameOfBlock(int platz)
{
    if(platz < anzahlPl){
        return plaetze[platz]->getName();
    }
}

int Konfiguration::removeBlock(int platz)
{
    if(platz < anzahlPl){
        int temp = plaetze[platz]->removeBlock();
        return temp;
    }
    return 0;
}

void Konfiguration::moveBlock(int current, int placement)
{
    if(current < anzahlPl && placement < anzahlPl){
        int block = plaetze[current]->removeBlock();
        plaetze[placement]->addBlock(block);
    }
}

int Konfiguration::getTop(int platz){
    if(platz < anzahlPl){
        return plaetze[platz]->top;
    }
    return 0;
}

koord Konfiguration::searchBlock(int name){     //gibt Koordinate des Blocks name zurück (<platz>,<höhe>)

    for(int p = 1; p < anzahlPl; p++){
        for(int i = 1; i < anzahlBl; i++){
            if(plaetze[p]->getName(i) == name)
            {
                koord platzierung = koord(p,i);
                return platzierung;
            }
        }
    }
    koord out;
    return out;
}


