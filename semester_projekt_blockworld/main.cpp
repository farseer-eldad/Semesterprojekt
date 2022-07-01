#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

#include <Konfiguration.h>
#include <koord.h>

using namespace std;

int main()
{

    int p, b;

//---------Eingabe der Dimensionen-------------------------
    cout << "Gib die Anzahl der Plätze und Blöcke so an: <Plätze> >Blöcke>" << endl;
    cin >> p >> b;

    Konfiguration start = Konfiguration(p, b);
    Konfiguration goal = Konfiguration(p, b);


//-----------Einlesen der Ausgangstellung--------------------
    fstream inputStart;

    string line;

    inputStart.open("InputStart.txt", std::fstream::in);

    cout << "Start Array" << endl;

    if(inputStart.is_open()){
        int stringNumbers[10];      //speichern der Gelesenen Zahlen
        int indexNumber = 0;        //zählt den Index von stringNumbers
        int number = 0;             //zum Aufaddieren der Zahlen
        int factor = 1;
        int lineIndex = 0;          //gibt den Platz an den der BLock soll

        char temp;

        while(inputStart.get(temp)){    //ließt ganze Zeile ein, eine Zeile = ein Platz
                if(temp != ',' && temp != '\n'){    //Zahlen werden eingelesen
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
                    start.addBlock(number, lineIndex);
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
        start.addBlock(number, lineIndex);
    }

    inputStart.close();

    /*int temp;
    int k = 0;*/

    /*for(int i = 0; i < p; ++i)
    {
        cout << "R." << i << ": ";
        while(start.nameOfBlock(i,k) != 0){
            cout << start.nameOfBlock(i,k) << ',';
            k++;
        }
        k = 0;
        cout << '\r' << endl;
    }*/

//----------------Einlesen der Zeilstellung----------------------
    fstream inputEnd;

    inputEnd.open("InputEnd.txt", std::fstream::in);

    cout << "End Array" << endl;

    if(inputEnd.is_open()){
        int stringNumbers[10];
        int indexNumber = 0;
        int number = 0;
        int factor = 1;
        int lineIndex = 0;

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


    cout << "remove from Start " << start.removeBlock(1) << endl;
    cout << "remove from goal " << goal.removeBlock(3) << endl;

    koord pos = start.searchBlock(4);

    cout << pos.x << "|" << pos.y << endl;*/


    return 0;
}
