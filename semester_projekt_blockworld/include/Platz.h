#ifndef PLATZ_H
#define PLATZ_H


class Platz
{
    private:
        friend class Konfiguration;
        const int laenge;
        int top;

        int *bloecke;
        void setZero();     //setzt alle werte auf 0;

    public:
        Platz();
        Platz(int length);

        int getName();              //gibt Name des obersten Blocks
        int getName(int index);     //gibt Name des Blocks an stelle index

        void addBlock(int name);    //fügt neuen Block hinten an

        int removeBlock();      //entfernt Block am Ende und gibt dessen namen zurück

};

#endif // PLATZ_H
