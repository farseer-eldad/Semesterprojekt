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

Konfiguration eingabe(string inputFile);


int main()
{

//---------Eingabe der Konfigurationen-------------------------

    Konfiguration curr = eingabe("InputStart.txt");
    Konfiguration goal = eingabe("InputEnd.txt");




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
Konfiguration eingabe(string inputFile){
    fstream input;

    string line;

    input.open(inputFile, std::fstream::in);

    cout << "Start Array" << endl;

    if(input.is_open()){
        int stringNumbers[10];      //speichern der Gelesenen Zahlen
        int indexNumber = 0;        //zählt den Index von stringNumbers
        int number = 0;             //zum Aufaddieren der Zahlen
        int factor = 1;
        int lineIndex = 0;          //gibt den Platz an den der BLock soll
        int p, b;


        char temp;

        do{
            input.get(temp);
            if(temp != ',' && temp != '\n'){    //Zahlen werden eingelesen
                    stringNumbers[indexNumber] = temp - '0';
                    indexNumber++;
                } else{
                    for(int k = indexNumber-1; k >= 0; --k){        //durchläuft die eingelesenen Stellen
                        number += stringNumbers[k] * factor;        //errechnet die Zehnerpotenz der Stelle ond multipliziert diese mit der Stelle aus stringNumbers
                        indexNumber--;
                        factor *= 10;
                    }
                    if(lineIndex < 1){
                        p = number;
                        lineIndex++;
                    } else{
                        b = number;
                    }
                    indexNumber = 0;
                    number = 0;
                    factor = 1;
                }

        }while(temp != '\n');

        Konfiguration konfig = Konfiguration(p, b);

        indexNumber = 0;
        number = 0;
        factor = 1;
        lineIndex = 1;


        while(input.get(temp)){    //ließt ganze Zeile ein, eine Zeile = ein Platz
                if(temp == '0' && indexNumber == 0){ //wenn 0 gelesen wird und vorher nichts eingelesen wurde
                    lineIndex++;
                }else if(temp != ',' && temp != '\n'){    //Zahlen werden eingelesen
                    stringNumbers[indexNumber] = temp - '0';
                    indexNumber++;
                } else{
                    for(int k = indexNumber-1; k >= 0; --k){        //durchläuft die eingelesenen Stellen
                        number += stringNumbers[k] * factor;        //errechnet die Zehnerpotenz der Stelle ond multipliziert diese mit der Stelle aus stringNumbers
                        indexNumber--;
                        factor *= 10;
                    }
                    factor = 1; //setzt Zehnerpotenz zurück
                    indexNumber = 0;
                    konfig.addBlock(number, lineIndex);
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
        konfig.addBlock(number, lineIndex);

    input.close();

    return konfig;
    }

    input.close();
}
