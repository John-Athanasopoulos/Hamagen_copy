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

    Chain<int> list[] = { h1,h2 };

    h1.Insert(2879, 1);
    h2.Insert(2879, 1);

    SquareRegion SR1(0, 0, 20, 20);
    SquareRegion SR2(21, 0, 40, 20);
    SquareRegion SR3(41, 0, 60, 20);
    SquareRegion SR4(0, 21, 20, 40);
    SquareRegion SR5(21, 21, 40, 40);
    SquareRegion SR6(41, 21, 60, 40);
    SquareRegion SR7(0, 41, 20, 60);
    SquareRegion SR8(21, 41, 40, 60);
    SquareRegion SR9(41, 41, 60, 60);

    int u1 = h1.FIND_CROWDED_PLACES(1, 30, 86400, SR1, 60);

    /*int k;
    int sum = 0;
    for (int i = 0; i < sizeof(list); i++) {
        k = list[i].FIND_CROWDED_PLACES(1, 30, 86400, SR1, 60);
        sum += k;
    }
    cout << sum;*/
    cout << u1;

    return 0;
}
