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
#include <vector>

#include "Chain.h"
#include "SquareRegion.h"

using namespace std;

int main() {

    srand(time(0));
    int displayX;
    int displayY;
    int displayHealth;
    int simulationDays;

    // Δημιουργούμε Instances των χρηστών
    Chain<int> h1("Stratis");
    Chain<int> h2("John");
    Chain<int> h3("Maria");
    Chain<int> h4("Nikos");
    Chain<int> h5("Thanasis");
    Chain<int> h6("Peter");
    Chain<int> h7("Mina");
    Chain<int> h8("Anastasia");
    Chain<int> h9("Panagiota");
    Chain<int> h10("Leonardo");

    // Τα προσθέτουμε σε πίνακα για ευκολότερη χρήση
    Chain<int> chains[10] = { h1, h2, h3, h4, h5, h6, h7, h8, h9, h10 };

    // Μερικοί ενδεικτικοί τετραγωνικοί χώροι. Μπορούν να προσταθούν οποιοιδήποτε άλλοι
    SquareRegion SR1(0, 0, 20, 20); 
    SquareRegion SR2(21, 0, 40, 20);
    SquareRegion SR3(41, 0, 60, 20);
    SquareRegion SR4(0, 21, 20, 40);
    SquareRegion SR5(21, 21, 40, 40);
    SquareRegion SR6(41, 21, 60, 40);
    SquareRegion SR7(0, 41, 20, 60);
    SquareRegion SR8(21, 41, 40, 60);
    SquareRegion SR9(41, 41, 60, 60);

    vector<Chain<int>> patientList; // Λίστα των ασθενών

    cout << "For how many days should the simulation run?" << endl << "Answer: ";
    cin >> simulationDays;

    // Προσθέτουμε κόμβους
    for (int i = 1; i <= simulationDays; i++) // Για καθε μέρα
        for (Chain<int> h : chains) // Για κάθε chain / χρήστη
            i == 1 ? h.Insert(2879, i) : h.Insert(2880, i); // Η πρώτη ημέρα ήδη περιέχει τον πρώτο κόμβο

    for (Chain<int> h : chains) {
        // Τυχαίοι κόμβοι προς διαγραφή (1-2800)
        int d1 = 1 + rand() % 2800; 
        int d2 = 1 + rand() % 2800;
        int d3 = 1 + rand() % 2800;
        int d4 = 1 + rand() % 2800;
        int d5 = 1 + rand() % 2800;
        while (d1 != d2 && d1 != d3 && d1 != d4 && d1 != d5 && d2 != d3 && d2 != d4 && d2 != d5 && d3 != d4 && d3 != d5 && d4 != d5) {
            d1 = 1 + rand() % 2800;
            d2 = 1 + rand() % 2800;
            d3 = 1 + rand() % 2800;
            d4 = 1 + rand() % 2800;
            d5 = 1 + rand() % 2800;
        }
        // Μετά την διαγραφή, οι indexes των αλυσιδών μειώνονται αναλόγως
        h.Delete(d1);
        h.Delete(d2 - 1);
        h.Delete(d3 - 2);
        h.Delete(d4 - 3);
        h.Delete(d5 - 4);
    }

    for (Chain<int> h : chains)
        if (!h.IsHealthy())
            patientList.push_back(h);


    // ΑΡΧΗ ΠΡΟΣΟΜΟΙΩΣΗΣ

    for (int i = 1; i <= simulationDays; i++) { // Για κάθε μέρα
        srand(time(0));
        for (Chain<int> h : chains) { // Για κάθε χρήστη / chain
            h.REPAIR(i);

            if (!h.IsHealthy())
                cout << h.GetName() << " - not healthy" << endl;
            else
                if (h.POSSIBLE_COVID_19_INFECTION(20, i, patientList, 10))
                    cout << h.GetName() << " - possible patient" << endl;
                else
                    cout << h.GetName() << " - healthy" << endl;

            h.SUMMARIZE_TRAJECTORY(i, 3);
        }
        cout << "------------------------------------" << endl;
    }

    // Κρατάμε το τερματικό ανοιχτό
    char KeepConsoleOpen;
    cin >> KeepConsoleOpen;

    return 0;
}
