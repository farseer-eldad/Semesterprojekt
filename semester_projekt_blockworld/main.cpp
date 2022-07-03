#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <stdbool.h>

#include "Konfiguration.h"
#include "koord.h"

using namespace std;

void konfigAusgabe(Konfiguration kZuAusgabe);
void konfigAusgabe(Konfiguration kZuAusgabe, koord besPos);
void moveTopofBlock(Konfiguration &curr, koord topBlockPos, int topBlocks, koord targetBlPos, koord targetPos, int targetBlock);
void moveTopofPlace(Konfiguration &curr, koord topBlockPos, int topBlocks, koord targetBlPos, koord targetPos, int targetBlock);



int main()
{

    int p, b;

//---------Eingabe der Dimensionen-------------------------
    cout << "Gib die Anzahl der Plaetze und Bloecke so an: <Plaetze> <Bloecke>" << endl;
    cin >> p >> b;

    p++;
    b++;

    Konfiguration curr (p, b);
    Konfiguration goal (p, b);


//-----------Einlesen der Ausgangstellung--------------------
    fstream inputStart;     //input start konfiguration

    string line;

    inputStart.open("InputStart.txt", std::fstream::in);

    cout << "Start Array" << endl;

    if(inputStart.is_open()){
        int stringNumbers[10];      //speichern der Gelesenen Zahlen
        int indexNumber = 0;        //zählt den Index von stringNumbers
        int number = 0;             //zum Aufaddieren der Zahlen
        int factor = 1;
        int lineIndex = 1;          //gibt den Platz an den der BLock soll

        char temp;

        while(inputStart.get(temp)){    //ließt ganze Zeile ein, eine Zeile = ein Platz
                if(temp != ',' && temp != '\n'){    //Zahlen werden eingelesen
                    stringNumbers[indexNumber] = temp - '0';
                    indexNumber++;
                } else{
                    for(int k = indexNumber-1; k >= 0; --k){        //durchläuft die eingelesenen Stellen
                        number += stringNumbers[k] * factor;        //errechnet die Zehnerpotenz der Stelle und multipliziert diese mit der Stelle aus stringNumbers
                        indexNumber--;
                        factor *= 10;
                    }
                    factor = 1; //setzt Zehnerpotenz zurück
                    indexNumber = 0;
                    curr.addBlock(number, lineIndex);
                    number = 0;
                    if(temp == '\n'){
                        lineIndex++;
                    }
                }
        }
        for(int k = indexNumber-1; k >= 0; --k){
            number += stringNumbers[k] * factor;
            indexNumber--;
            factor *= 10;
        }
        curr.addBlock(number, lineIndex);
    }

    inputStart.close();

    /*int temp;
    int k = 0;*/

    /*for(int i = 0; i < p; ++i)
    {
        cout << "R." << i << ": ";
        while(curr.nameOfBlock(i,k) != 0){
            cout << curr.nameOfBlock(i,k) << ',';
            k++;
        }
        k = 0;
        cout << '\r' << endl;
    }*/

//----------------Einlesen der Zielstellung----------------------
    fstream inputEnd;

    inputEnd.open("InputEnd.txt", std::fstream::in);

    cout << "End Array" << endl;

    if(inputEnd.is_open()){
        int stringNumbers[10];
        int indexNumber = 0;
        int number = 0;
        int factor = 1;
        int lineIndex = 1;

        char temp;

        while(inputEnd.get(temp)){
                if(temp != ',' && temp != '\n'){
                    stringNumbers[indexNumber] = temp - '0';
                    indexNumber++;
                } else{
                    for(int k = indexNumber-1; k >= 0; --k){
                        number += stringNumbers[k] * factor;
                        indexNumber--;
                        factor *= 10;
                    }
                    factor = 1;
                    indexNumber = 0;
                    goal.addBlock(number, lineIndex);
                    number = 0;
                    if(temp == '\n'){
                        lineIndex++;
                    }
                }
        }
        for(int k = indexNumber-1; k >= 0; --k){
            number += stringNumbers[k] * factor;
            indexNumber--;
            factor *= 10;
        }
        goal.addBlock(number, lineIndex);
    }

    inputEnd.close();


    /*for(int i = 0; i < p; ++i)
    {
        cout << "R." << i << ": ";
        while(goal.nameOfBlock(i,k) != 0){
            cout << goal.nameOfBlock(i,k) << ',';
            k++;
        }
        k = 0;
        cout << '\r' << endl;
    }


    cout << "remove from curr " << curr.removeBlock(1) << endl;
    cout << "remove from goal " << goal.removeBlock(3) << endl;

    koord pos = curr.searchBlock(4);

    cout << pos.x << "|" << pos.y << endl;*/

    //---------------------------------------------------sortierung

    cout << endl << "current konfiguration" << endl;
    konfigAusgabe(curr);
    cout << "goal konfiguration" << endl;
    konfigAusgabe(goal);

    koord tPos (1,1);
    int blocksSorted = 0;

    while(blocksSorted != goal.anzahlBl-1){

        int tBlock = goal.nameOfBlock(tPos.x,tPos.y);
        koord tBlPos = curr.searchBlock(tBlock);    //target block position

        cout << endl << tBlock << " to " << tPos.x << ", " << tPos.y <<endl ;
        cout << blocksSorted << " blocks sorted, " << goal.anzahlBl-blocksSorted-1 << " left" << endl;

        if(tBlock == 0) cout << "tBlock is 0" << endl;;

        if(tBlPos.x!=tPos.x && tBlock!=0){
            koord topBlockPos = curr.searchBlock(curr.nameOfBlock(tBlPos.x));    //top block position (gleicher platz wie tBlPos)

            unsigned int topBlocks = tBlPos.y-topBlockPos.y;   //menge der bloecke auf unseren target Block

            moveTopofBlock(curr,topBlockPos,topBlocks,tBlPos,tPos,tBlock);


            topBlockPos = curr.searchBlock(curr.nameOfBlock(tPos.x));    //top block position (gleicher platz wie tPos)
            topBlocks = topBlockPos.y-tPos.y-1;   //menge der bloecke auf unseren target Place

            moveTopofPlace(curr,topBlockPos,topBlocks,tBlPos,tPos,tBlock);

            curr.moveBlock(tBlPos.x,tPos.x);

            konfigAusgabe(curr,curr.searchBlock(tBlock));

        }else if(tBlPos.y!=tPos.y && tBlock!=0){
            koord topBlockPos = curr.searchBlock(curr.nameOfBlock(tBlPos.x));    //top block position (gleicher platz wie tBlPos)
            unsigned int topBlocks = tBlPos.y-topBlockPos.y;   //menge der bloecke auf unseren target Block

            moveTopofBlock(curr,topBlockPos,topBlocks,tBlPos,tPos,tBlock);

            int blockMoveindex = 1;
            if(tBlPos.x-blockMoveindex < 1){
                blockMoveindex = blockMoveindex - (curr.anzahlPl-1);
            }

            curr.moveBlock(tBlPos.x,tBlPos.x-blockMoveindex);    //block in die andere richtung bewegen

            konfigAusgabe(curr,curr.searchBlock(tBlock));

            tBlPos = curr.searchBlock(tBlock);

            topBlockPos = curr.searchBlock(curr.nameOfBlock(tPos.x));    //top block position (gleicher platz wie tPos)
            topBlocks = topBlockPos.y-tPos.y-1;   //menge der bloecke auf unseren target Place

            moveTopofPlace(curr,topBlockPos,topBlocks,tBlPos,tPos,tBlock);

            curr.moveBlock(tBlPos.x,tPos.x);

            konfigAusgabe(curr,curr.searchBlock(tBlock));
        }

        tPos.x++;
        if(tBlock != 0) blocksSorted++;
        if (tPos.x==goal.anzahlPl){
            tPos.x = 1;
            tPos.y++;
        }

    }

    cout << endl << "end result: ";

    konfigAusgabe(curr);


    return 0;
}

void moveTopofBlock(Konfiguration &curr, koord topBlockPos, int topBlocks, koord targetBlPos, koord targetPos, int targetBlock){
    if(topBlocks){
        int moveindex = 1;
        for(int i=topBlockPos.y; i>targetBlPos.y; i--){

            if(topBlockPos.x+moveindex == targetPos.x){
                moveindex++;
            }
            if(topBlockPos.x+moveindex > curr.anzahlPl-1){
                moveindex = moveindex - (curr.anzahlPl-1);
            }
            if(topBlockPos.x+moveindex == targetPos.x){
                moveindex++;
            }

            curr.moveBlock(topBlockPos.x,topBlockPos.x+moveindex);

            konfigAusgabe(curr,curr.searchBlock(targetBlock));

        }
    }
}

void moveTopofPlace(Konfiguration &curr, koord topBlockPos, int topBlocks, koord targetBlPos, koord targetPos, int targetBlock){
    if(topBlocks){
        int moveindex = 1;
        for(int i=topBlockPos.y; i>targetPos.y-1; i--){

            if(topBlockPos.x+moveindex == targetBlPos.x){
                moveindex++;
            }
            if(topBlockPos.x+moveindex > curr.anzahlPl-1){
                moveindex = moveindex - (curr.anzahlPl-1);
            }
            if(topBlockPos.x+moveindex == targetBlPos.x){
                moveindex++;
            }

            curr.moveBlock(topBlockPos.x,topBlockPos.x+moveindex);

            konfigAusgabe(curr,curr.searchBlock(targetBlock));

        }
    }
}


void konfigAusgabe(Konfiguration kZuAusgabe){
    int b = kZuAusgabe.anzahlBl-1;
    int p = kZuAusgabe.anzahlPl;
    int onBlock = b;

    for(int i=b-1; i>0; i--){
        for(int j=1;j<p; j++){
            if(i!=onBlock){
                cout << endl;
                onBlock = i;
            }
            if(kZuAusgabe.nameOfBlock(j,i)!=0){
                cout << " " << kZuAusgabe.nameOfBlock(j,i) << "\t";
            }else cout << "  " << "\t";
        }
    }
    cout << endl;
}

void konfigAusgabe(Konfiguration kZuAusgabe, koord besPos){           //mit angabe
    int b = kZuAusgabe.anzahlBl-1;
    int p = kZuAusgabe.anzahlPl;
    int onBlock = b;

    for(int i=b-1; i>0; i--){
        for(int j=1;j<p; j++){
            if(i!=onBlock){
                cout << endl;
                onBlock = i;
            }
            if(i==besPos.y && j==besPos.x){
                cout << "|" << kZuAusgabe.nameOfBlock(j,i) << "|" << "\t";
            }else{
                if(kZuAusgabe.nameOfBlock(j,i)!=0){
                    cout << " " << kZuAusgabe.nameOfBlock(j,i) << "\t";
                }else cout << "  " << "\t";
            }
        }
    }
    cout << endl;
}
