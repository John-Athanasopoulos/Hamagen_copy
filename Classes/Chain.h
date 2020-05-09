#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>

#include "SquareRegion.h"

#define R 10

using namespace std;

template<class T>
class ChainNode;
template<class T>
class Chain
{
public:
    // Constructor
    Chain(string name)
    {
        this->name = name;
        first = 0;
    }
    //~Chain() { // Destructor
    //    ChainNode<T>* next;

    //    // Διαγράφει έναν κόμβο και συνεχίζει με τον επόμενο
    //    while (first) {
    //        next = first->link;
    //        delete first;
    //        first = next;
    //    }
    //}

    /* Παίρνει ως είσοδο την τροχιά ενός χρήστη για μία συγκεκριμένη ημέρα, θα την
    συγκρίνει με τις τροχιές των ασθενών και θα επιστρέφει TRUE αν ο χρήστης βρέθηκε
    εντός ακτίνας R από τον ασθενή για διάστημα τουλάχιστον Τ1 λεπτών της ώρας και το
    πολύ Τ2 λεπτά αργότερα από τη στιγμή που πέρασε ο ασθενής.*/





    /*Ψάχνει για την συγκεκριμένη μέρα και για τα συγκεκριμένα αρχικά και τελικά δευτερόλεπτα
    αν ο χρήστης έμεινε στην τετραγωνική περιοχή που ορίστηκε για ένα συγκεκριμένο χρονικό διάστημα*/

    int FIND_CROWDED_PLACES(int day, int starting_sec, int ending_sec, SquareRegion a, int minStay) { //
        ChainNode<T>* p = first;
        int user_count = 0; //how many users standed in this square area during the given time interval for at least the minStay time specified
        while (p &&p->data[3] != day) {
            p = p->link; //link till the first node of the chosen day, or until we reach the end of the chain meaning the day was incorrect
        }
        if (p && 30 <= starting_sec && 86400 >= starting_sec && 30 <= ending_sec && 86400 >= ending_sec && starting_sec < ending_sec) { //all the prerequisites
            while (p->data[4] != starting_sec && p) {
                p = p->link; //link until we find the node with data[4] = starting_sec
            }
            int difference_sec = ending_sec - starting_sec; //The difference in seconds
            int numberNeeded = difference_sec / 30; //The nodes we need to check
            int counter = 0; // counts how many consecutive nodes are in the square (counter <= numberNeeded)
            int stayMinNodes = minStay / 30; //The minimum number of nodes needed for the method to return a value

            while (p && numberNeeded > 0) {
                if (p->data[0] >= a.minX && p->data[0] <= a.maxX && p->data[1] >= a.minY && p->data[1] <= a.maxY) {
                    counter++;
                    if (counter >= stayMinNodes) {
                        user_count = 1;
                        return user_count;
                    }
                }
                else {
                    counter = 0;
                }
                p = p->link;
                numberNeeded--;
            }
        }
        else {
            cout << "The day, the starting second, the ending second or a combination of them is incorrect." << endl;
        }
        return user_count;
    } 

    /* Συμπληρώνει αυτά τα κενά που μπορούν να συμβούν στην καταγραφή της τροχιάς
    ενός χρήστη. */
    Chain<T>& REPAIR(int day)
    {
        // Ξεκινάμε από τον πρώτο κόμβο
        ChainNode<T>* p = first;
        int counter = 1;

        int h = p->data[2]; // Κρατάμε την υγεία του

        // Προσπερνάμε τους κόμβους που βασίζονται σε προηγούμενες ημέρες
        while (p->data[3] < day) {
            p = p->link;
            counter++;
        }

        /* Ελέγχουμε καθε κόμβο που χρειαζόμαστε. Αν υπάρχει οποιοδήποτε κενό,
        το συμπληρώνουμε */
        while (p->link && p->data[3] == day) {
            if (p->link->data[4] - p->data[4] > 30) {
                int x = RandomInt();
                int y = RandomInt();
                InsertBetween(counter + 1, x, y, day);
            }
            else {
                p = p->link;
                counter++;
            }
        }

        return *this; // Επιστρέφουμε την ανανεωμένη αλυσίδα
    }

    /* Στο τέλος μίας συγκεκριμένης ημέρας, η τροχιά της ημέρας που απέχει ένα πλήθος
    ημερών από τη συγκεκριμένη θα αντικαθίσταται από μία σύνοψή της. */
    Chain<T>& SUMMARIZE_TRAJECTORY(int day, int daysBefore) {
        ChainNode<T>* p = first; // Ξεκινάμε από τον πρώτο κόμβο

        // Προσπερνάμε τους κόμβους που βασίζονται σε προηγούμενες ημέρες
        while (p->link && !(p->data[3] >= day - daysBefore)) {
            p = p->link;
        }

        /* Ελέγχει κάθε 2 διαδοχικούς κόμβους του επιλεγμένου διαστήματος ημερών και:
           αν ανήκουν στην ίδια μέρα και οι συντεταγμένες (x,y) απέχουν το πολύ R,
           διαγράφουμε τον 2ο. Αλλιώς, συνεχίζουμε στο επόμενο ζεύγος κόμβων. */
        while (p->link) {
            if (p->data[3] >= day - daysBefore && p->data[3] == p->link->data[3]) {
                if (abs(p->data[0] - p->link->data[0]) < R && abs(p->data[1] - p->link->data[1]) < R) {
                    p->link = p->link->link;
                }
                else {
                    p = p->link;
                }
            }
            else {
                p = p->link;
            }
        }

        return *this; // Επιστρέφουμε την ανανεωμένη αλυσίδα
    }

    // Δημιουργεί τον πρώτο κόμβο της αλυσίδας
    Chain<T>& FirstNodeCreation(int currX, int currY, int healthy)
    {
        // Δημιουργούμε node pointer
        ChainNode<T>* y = new ChainNode<T>(currX, currY, healthy, 1);

        y->ChainNode<T>::SetNode(); // Θέτουμε έναν κόμβο

        // Του δίνουμε τιμές
        y->data[0] = currX;
        y->data[1] = currY;
        y->data[2] = healthy;
        // Ο πρώτος κόμβος κάθε αλυσίδας βασίζεται πάντα στην πρώτη ημέρα
        y->data[3] = 1;
        y->data[4] = 30;

        first = y; // Ορίζουμε τον κόμβο ως πρώτο

        return *this; // Επιστρέφουμε την αρχή της αλυσίδας
    }

    // Εισαγωγή κόμβου/-ων στην αλυσίδα
    Chain<T>& Insert(int k, int day)
    {
        // Κατευθυνόμαστε στον τελευταίο κόμβο, αρχίζοντας από τον πρώτο
        ChainNode<T>* p = first;
        while (p->link)
            p = p->link;

        while (k-- > 0) {
            // Παίρνουμε τιμές x,y και health
            int currX = RandomInt();
            int currY = RandomInt();
            int healthy = 0;

            // Δημιουργούμε node pointer
            ChainNode<T>* y = new ChainNode<T>(currX, currY, healthy, day);

            y->ChainNode<T>::SetNode(); // Θέτουμε έναν κόμβο

            // Του δίνουμε τιμές
            y->data[0] = currX;
            y->data[1] = currY;
            y->data[2] = p->data[2]; // Η υγεία παραμένει σταθερή
            y->data[3] = day;
            // Τα δευτερόλεπτα του κόμβου ισούνται με αυτά του προηγούμενου + 30
            y->data[4] = p->data[4] + 30;

            // Τον προσθέτουμε στην αλυσίδα
            p->link = y;
            p = p->link;
        }

        return *this; // Επιστρέφουμε την ανανεωμένη αλυσίδα
    }

    // Εισαγωγή ενδιάμεσου κόμβου στην αλυσίδα
    Chain<T>& InsertBetween(int k, int x, int y, int day)
    {
        ChainNode<T>* p = first; // Παίρνουμε τον πρώτο κόμβο

        int h = p->data[2]; // Κρατάμε την υγεία ώστε να παραμείνει σταθερή

        // Κατευθυνόμαστε στην επιλεγμένη θέση k
        if (p->link && p)
            for (int index = 1; index < k - 1; index++)
                p = p->link;

        ChainNode<T>* nextLink = p->link; // Κρατάμε την διεύθυνση του επόμενου κόμβου

        // Δημιουργούμε node pointer
        ChainNode<T>* z = new ChainNode<T>(x, y, h, day);

        z->ChainNode<T>::SetNode(); // Θέτουμε έναν κόμβο

        // Του δίνουμε τιμές
        z->data[0] = x;
        z->data[1] = y;
        z->data[2] = h;
        z->data[3] = day;
        z->data[4] = p->data[4] + 30;

        // Τον προσθέτουμε στην αλυσίδα
        p->link = z;
        z->link = nextLink;

        return *this; // Επιστρέφουμε την ανανεωμένη αλυσίδα
    }

    // Επιστρέφει το μήκος της αλυσίδας
    int Length() const
    {
        ChainNode<T>* currentNode = first; // Παίρνουμε τον πρώτο κόμβο
        int value = 1; // Αρχικοιποιούμε την τιμή με την θέση του πρώτου κόμβου

        // Για κάθε κόμβο, αυξάνουμε την τιμή κατά 1
        while (currentNode) {
            value++;
            currentNode = currentNode->link;
        }

        return value; // Επιστρέφουμε την τιμή
    }

    // Δημιουργία τυχαίας ακέραιας τιμής [1,60]
    int RandomInt()
    {
        int value = rand() % 61;
        return value; // Επιστρέφουμε την τιμή
    }

    // Αναζητά τον κόμβο στη θέση x
    int Search(const T& x) const
    {
        ChainNode<T>* currentNode = first; // Ξεκινάει από τον πρώτο
        int counter = 1; // ...και τη θέση του

        while (currentNode && currentNode->data != x) { // Όσο ο τρέχων κόμβος δεν είναι ο x
            // Συνεχίζουμε στον επόμενο
            currentNode = currentNode->link;
            counter++;
        }

        if (currentNode) // Αν ο κόμβος βρέθηκε, επιστρέφουμε το index του
            return counter;

        return 0; // Αλλιώς, επιστρέφουμε 0
    }

    // Διαγράφει τον κόμβο στην θέση k
    Chain<T>& Delete(int k)
    {
        // Αν το index k είναι μη έγκυρο ή ο πρώτος pointer είναι NULL
        if (k < 1 || !first) {
            cout << "ERROR: Out of Bounds Exception.."; // Το exception μπορεί και να παραληφθεί
        }
        ChainNode<T>* p = first;  // Παίρνουμε τον πρώτο κόμβο

        // Αν θέλουμε να διαγραφεί ο πρώτος κόμβος, τότε θέτουμε τον δεύτερο ως αρχή της αλυσίδας
        if (k == 1) {
            first = first->link;
        }
        else { // Αλλιώς, κάνουμε όλες τις απαραίτητες μετατροπές, πριν διαγράψουμε τον κόμβο
            ChainNode<T>* q = first;
            for (int i = 1; i < k - 1 && q; i++)
                q = q->link;
            p = q->link;
            q->link = p->link;
        }

        delete p; // Διαγράφουμε τον κόμβο

        return *this; // Επιστρέφουμε την ανανεωμένη αλυσίδα
    }

    void Output()  //Outputs the whole chain in the following format: node1-node2-etc
    {
        ChainNode<T>* p = first;  // Παίρνουμε τον πρώτο κόμβο

        cout << name; // Εκτυπώνουμε το όνομα πρώτα με σκοπό να ξεχωρίζουμε το άτομο

        while (p) { // Όσο ο κόμβος p δεν είναι NULL, εκτυπώνουμε τα στοιχεία του
            cout << " -> " << "{" << p->data[3] << ", " << p->data[0] << ", " << p->data[1] << ", " << p->data[2] << ", " << p->data[4] << "}";
            // format =  -> { day, x, y, health, seconds }

            p = p->link; // συνεχίζουμε με τον επόμενο κόμβο
        }
        cout << endl;
    }

private:
    ChainNode<T>* first; // πρώτος κόμβος
    string name; // όνομα ανθρώπου
};

template<class T>
class ChainNode
{
public:
    friend Chain<T>;

    int currentX; // Τρέχων Χ
    int currentY; // Τρέχων Y
    int healthy; // 1 αν υγιής, αλλιώς 0
    int currentDay; // Τρέχουσα ημέρα

    // Constructor
    ChainNode(int x, int y, int health, int day)
    {
        currentX = x;
        currentY = y;
        healthy = health;
        currentDay = day;
    }

    // Θέτουμε έναν κόμβο με τις τιμές των στοιχείων του
    void SetNode()
    {
        int currX = this->currentX;
        int currY = this->currentY;
        int healthy = this->healthy;
        int day = this->currentDay;
        this->data[0] = currX;
        this->data[1] = currY;
        this->data[2] = healthy;
        this->data[3] = day;
    }

    int data[5];

private:
    ChainNode<T>* link;
};
