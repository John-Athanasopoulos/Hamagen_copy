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

    // Δημιουργούμε Instances των χρηστών
    Chain<int> h1("Στρατής");
    Chain<int> h2("Γιάννης");
    Chain<int> h3("Μαρία");
    Chain<int> h4("Νίκος");
    Chain<int> h5("Θανάσσης");
    Chain<int> h6("Πέτρος");
    Chain<int> h7("Μίνα");
    Chain<int> h8("Αναστασία");
    Chain<int> h9("Παναγιώτα");
    Chain<int> h10("Λεονάρντο");

    // Τα προσθέτουμε σε πίνακα για ευκολότερη χρήση
    Chain<int> chains[10] = { h1, h2, h3, h4, h5, h6, h7, h8, h9, h10 };

    // Προσθέτουμε κόμβους
    for (int i = 0; i < 2; i++) // Για καθε μέρα
        for (Chain<int> h : chains) // Για κάθε chain / χρήστη
            i == 1 ? h.Insert(2879, i) : h.Insert(2880, i); // Η πρώτη ημέρα ήδη περιέχει τον πρώτο κόμβο

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
