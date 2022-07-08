#include "Konfiguration.h"


Konfiguration::Konfiguration() : anzahlPl(0), anzahlBl(0)
{

}

Konfiguration::Konfiguration(int menge) : anzahlPl(menge+1), anzahlBl(menge)
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
void Konfiguration::addBlock(int nameOfBlock, int platzOfBlock)
{
    plaetze[platzOfBlock]->addBlock(nameOfBlock);
}

int Konfiguration::nameOfBlock(int platz, int block)
{
    return plaetze[platz]->getName(block);
}

int Konfiguration::nameOfBlock(int platz)
{
    return plaetze[platz]->getName();
}

int Konfiguration::removeBlock(int platz)
{
    int temp = plaetze[platz]->removeBlock();
    return temp;
}

void Konfiguration::moveBlock(int current, int placement)
{
    int block = plaetze[current]->removeBlock();
    plaetze[placement]->addBlock(block);
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


