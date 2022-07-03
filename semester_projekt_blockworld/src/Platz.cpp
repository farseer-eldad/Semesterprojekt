#include "Platz.h"

Platz::Platz() : laenge(4){     //3 benutzbare plaetze

    bloecke = new int[laenge];
    top = 0;
    setZero();
}

Platz::Platz(int length) : laenge(length+1){

    bloecke = new int[laenge];
    top = 0;
    setZero();
}

void Platz::setZero(){

    for(int i = 0; i < laenge; ++i){
        bloecke[i] = 0;
    }
}

void Platz::addBlock(int name){

    if(top < laenge-1){
        top++;
        bloecke[top] = name;
    }
}

int Platz::removeBlock(){

    if(top > 0){
        int out = bloecke[top];
        bloecke[top] = 0;
        top--;
        return out;
    }else return 0;
}

int Platz::getName(){

    return bloecke[top];
}

int Platz::getName(int index){

    if(index <= laenge-1 && index > 0){
        return bloecke[index];
    }else return 0;
}


