#include "Platz.h"

Platz::Platz() : laenge(0)
{
    bloecke = new int[0];
    top = 0;
}

Platz::Platz(int length) : laenge(length)
{
    bloecke = new int[laenge];
    top = 0;
    setZero();
}
void Platz::addBlock(int name)
{
    if(top < laenge){
        bloecke[top] = name;
        top++;
    }
}

int Platz::removeBlock()
{
    top--;
        if(top <= 0){
        int out = bloecke[top];
        bloecke[top] = 0;
        return out;
    }
}

int Platz::getName()
{
    return bloecke[top-1];
}

int Platz::getName(int index)
{
    if(index < top);
        return bloecke[index];
}
void Platz::setZero()
{
    for(int i = 0; i < laenge; ++i)
    {
        bloecke[i] = 0;
    }
}
