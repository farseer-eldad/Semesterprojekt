#ifndef KONFIGURATION_H
#define KONFIGURATION_H

#include <Platz.h>
#include <koord.h>
#include <vector>

using std::vector;


class Konfiguration
{
    public:
        Konfiguration();            //konstruiert 0 KOnfiguration
        Konfiguration(int menge);       //Anzahl Pl�tze und Bl�cke gleich
        Konfiguration(int menge, int bloecke);      //Anzahl Pl�tze und Bl�cke verschieden
        ~Konfiguration();



        void addBlock(int nameOfBLock, int platzOfBlock);   //f�gt Block mit Namen nameOfBlock auf Platz mit Nummer platzOfBlock ein

        void moveBlock(int current, int placement); //current gibt den Platz an auf dem der Block steht, placement ist der Platz auf den der Block geschoben werden soll

        koord searchBlock(int name);  //sucht Block in allen Pl�tzen und gibt Platznummer und Index im Array {platz, index} als Zeiger zur�ck

        int nameOfBlock(int platz);
        int nameOfBlock(int platz, int block);

        int removeBlock(int platz); //entfernt und gibt aus den obersten Block an Platz, bei fehler gibt 0 zur�ck
    protected:

    private:
        const int anzahlPl, anzahlBlproPlatz;

        vector<Platz> plaetze;

        void init();
};

#endif // KONFIGURATION_H
