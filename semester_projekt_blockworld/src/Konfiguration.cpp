#include "Konfiguration.h"

Konfiguration::Konfiguration() : anzahlPl(0), anzahlBlproPlatz(0)
{

}

Konfiguration::Konfiguration(int menge) : anzahlPl(menge), anzahlBlproPlatz(menge)
{
    for(int i = 0; i < anzahlPl; ++i)
    {
        plaetze.emplace_back(anzahlBlproPlatz);
    }
}

Konfiguration::Konfiguration(int menge, int bloecke) : anzahlPl(menge), anzahlBlproPlatz(bloecke)
{
    for(int i = 0; i < anzahlPl; ++i)
    {
        plaetze.emplace_back(anzahlBlproPlatz);
    }
}

Konfiguration::~Konfiguration()
{

}

void Konfiguration::addBlock(int nameOfBlock, int platzOfBlock)
{
    plaetze[platzOfBlock].addBlock(nameOfBlock);
}

int Konfiguration::nameOfBlock(int platz, int block)
{
    return plaetze[platz].getName(block);
}

int Konfiguration::nameOfBlock(int platz)
{
    return plaetze[platz].getName();
}

int Konfiguration::removeBlock(int platz)
{
    int temp = plaetze[platz].removeBlock();
    return temp;
}

void Konfiguration::moveBlock(int current, int placement)
{
    int block = plaetze[current].removeBlock();
    plaetze[placement].addBlock(block);
}

koord Konfiguration::searchBlock(int name){

    for(int p = 0; p < anzahlPl; p++){
        for(int i = 0; i < anzahlBlproPlatz; i++){
            if(plaetze[p].getName(i) == name)
            {
                koord platzierung = koord(p,i);
                return platzierung;
            }
        }
    }
    return koord();
}


