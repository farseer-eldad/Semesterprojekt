#ifndef KONFIGURATION_H
#define KONFIGURATION_H

#include "Platz.h"
#include "koord.h"
#include "vector"

using std::vector;


class Konfiguration
{
    private:
    vector<Platz> plaetze;                  //platz array scaffold
    void init();

    public:
        const int anzahlPl, anzahlBl;   //anzahl plaetze, anzahl bloecke

        Konfiguration();            //konstruiert 0 Konfiguration
        Konfiguration(int menge);       //Anzahl Plaetze und Bloecke gleich
        Konfiguration(int menge, int bloecke);      //Anzahl Plaetze und Bloecke verschieden
        ~Konfiguration();



        void addBlock(int platzOfBlock, int nameOfBLock);   //fügt Block mit Namen nameOfBlock auf Platz mit Nummer platzOfBlock ein

        void moveBlock(int current, int placement); //current gibt den Platz an auf dem der Block steht, placement ist der Platz auf den der Block geschoben werden soll

        koord searchBlock(int name);  //sucht Block in allen Plätzen und gibt Platznummer und Index im Array {platz, index} als Zeiger zurück

        int nameOfBlock(int platz);
        int nameOfBlock(int platz, int block);

        int removeBlock(int platz); //entfernt und gibt aus den obersten Block an Platz, bei fehler gibt 0 zurück

};

#endif // KONFIGURATION_H
