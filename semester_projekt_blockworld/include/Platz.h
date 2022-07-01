#ifndef PLATZ_H
#define PLATZ_H

class Platz
{
    public:
        Platz();
        Platz(int length);

        int getName();              //gibt Name eines Blocks
        int getName(int index);

        void addBlock(int name);    //fügt neuen Block hinten an

        int removeBlock();      //entfernt Block am Ende und gibt dessen namen zurück

        void setZero();     //setzt alle werte auf 0;

    protected:

    private:
        const int laenge;
        int top;

        int *bloecke;
};

#endif // PLATZ_H
