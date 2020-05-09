/*
Εργασία από τους:
    ΑΜ: Π19005
    Ονοματεπώνυμο: Ιωάννης Αθανασόπουλος

    ΑΜ: Π19041
    Ονοματεπώνυμο: Ευστράτιος Δερμανούτσος
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Grid.h"
#include "Chain.h"
#include "SquareRegion.h"

using namespace std;

int main() {
    //Grid* grid = new Grid();

    srand(time(0));
    int displayX;
    int displayY;
    int displayHealth;
    Chain<int> h1("Stratis");
    int startingX = h1.RandomInt();
    int startingY = h1.RandomInt();
    h1.FirstNodeCreation(startingX, startingY, 1);

    Chain<int> h2("John");
    startingX = h2.RandomInt();
    startingY = h2.RandomInt();
    h2.FirstNodeCreation(startingX, startingY, 0);

    h1.Insert(2, 1);
    h2.Insert(2, 1);
    h1.Output();
    h2.Output();
    cout << "\n\n";
    h2.Insert(2, 2);
    h1.Insert(2, 2);
    h1.Output();
    h2.Output();
    cout << "\n\n";
    h2.Insert(3, 3);
    h1.Insert(3, 3);
    h1.Output();
    h2.Output();
    cout << "\n\n";
    h2.Insert(7, 4);
    h1.Insert(7, 4);
    h1.Output();
    h2.Output();
    cout << "\n\n";
    //cout << h1.Length() << endl; // debug
    h1 = h1.SUMMARIZE_TRAJECTORY(4, 3);
    //cout << h1.Length() << endl; // debug
    h1.Output();
    // cout << h2.Length() << endl; // debug
    h2 = h2.SUMMARIZE_TRAJECTORY(4, 3);
    // cout << h2.Length() << endl; // debug
    h2.Output();

    cout << "\n\n";

    //cout << h1.Length() << endl; // debug
    h1 = h1.REPAIR(1);
    h1 = h1.REPAIR(2);
    h1 = h1.REPAIR(3);
    h1 = h1.REPAIR(4);
    //cout << h1.Length() << endl; // debug
    h1.Output();
    // cout << h2.Length() << endl; // debug
    h2 = h2.REPAIR(1);
    h2 = h2.REPAIR(2);
    h2 = h2.REPAIR(3);
    h2 = h2.REPAIR(4);
    // cout << h2.Length() << endl; // debug
    h2.Output();
    //h1.Details(1, displayX, displayY, displayHealth);


    SquareRegion SR2(21, 0, 40, 20);
    SquareRegion SR3(41, 0, 60, 20);
    SquareRegion SR4(0, 21, 20, 40);
    SquareRegion SR5(21, 21, 40, 40);
    SquareRegion SR6(41, 21, 60, 40);
    SquareRegion SR7(0, 41, 20, 60);
    SquareRegion SR8(21, 41, 40, 60);
    SquareRegion SR9(41, 41, 60, 60);
    return 0;
}
