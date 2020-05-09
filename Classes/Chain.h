//Random Waypoint Model
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
    ~Chain() { // Destructor
        ChainNode<T>* next;

        // ��������� ���� ����� ��� ��������� �� ��� �������
        while (first) {
            next = first->link;
            delete first;
            first = next;
        }
    }
    
    /* ������� �� ������ ��� ������ ���� ������ ��� ��� ������������ �����, �� ��� 
    ��������� �� ��� ������� ��� ������� ��� �� ���������� TRUE �� � ������� ������� 
    ����� ������� R ��� ��� ������ ��� �������� ����������� �1 ������ ��� ���� ��� �� 
    ���� �2 ����� �������� ��� �� ������ ��� ������ � �������.*//*
    int FIND_CROWDED_PLACES(int day, int starting_sec, int ending_sec, SquareRegion a, int minStay) { //
        ChainNode<T>&* p = first;
        int user_count = 0; //how many users standed in this square area during the given time interval for at least the minStay time specified
        while (p->data[3] != day && p) {
            p = p->link; //link till the first node of the chosen day, or until we reach the end of the chain meaning the day was incorrect
        }
        if (p && 30 <= starting_sec && 86370 <= starting_sec && 30 <= ending_sec && 86400 <= ending_sec && starting_sec < ending_sec) { //all the prerequisites
            while (p->data[4] != starting_sec && p) {
                p = p->link; //link until we find the node with data[4] = starting_sec
            }
            int difference_sec = ending_sec - starting_sec; //The difference in seconds
            int numberNeeded = difference_sec % 30; //The nodes we need to check
            int counter = 0; // counts how many consecutive nodes are in the square (counter <= numberNeeded)
            int stayMinNodes = minStay % 30; //The minimum number of nodes needed for the method to return a value
            while (p && numberNeeded > 0) {
                if (p->data[0] >= a.minX && p->data[0] <= a.maxX && p->data[1] >= a.minY && p->data[1] <= a.maxY) {
                    counter++;
                }
                else {
                    counter = 0;
                }
                p = p->link;
                numberNeeded--;
            }
            if (counter >= stayMinNodes) {
                user_count = 1;
            }
        }
        else {
            cout << "The day, the starting second, the ending second or a combination of them is incorrect." << endl;
        }
        return user_count;
    } */

    /* ����������� ���� �� ���� ��� ������� �� ������� ���� ��������� ��� ������� 
    ���� ������. */
    Chain<T>& REPAIR(int day)
    {
        // �������� ��� ��� ����� �����
        ChainNode<T>* p = first;
        int counter = 1;

        int h = p->data[2]; // ������� ��� ����� ���

        // ����������� ���� ������� ��� ���������� �� ������������ ������
        while (p->data[3] < day) {
            p = p->link;
            counter++;
        }

        /* ��������� ���� ����� ��� ������������. �� ������� ����������� ����,
        �� ������������� */
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

        return *this; // ������������ ��� ���������� �������
    }

    /* ��� ����� ���� ������������� ������, � ������ ��� ������ ��� ������ ��� ������
    ������ ��� �� ������������ �� �������������� ��� ��� ������ ���. */
    Chain<T>& SUMMARIZE_TRAJECTORY(int day, int daysBefore) {
        ChainNode<T>* p = first; // �������� ��� ��� ����� �����

        // ����������� ���� ������� ��� ���������� �� ������������ ������
        while (p->link && !(p->data[3] >= day - daysBefore)) {
            p = p->link;
        }

        /* ������� ���� 2 ����������� ������� ��� ����������� ����������� ������ ���:
           �� ������� ���� ���� ���� ��� �� ������������� (x,y) ������� �� ���� R,
           ����������� ��� 2�. ������, ����������� ��� ������� ������ ������. */
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

        return *this; // ������������ ��� ���������� �������
    }

    // ���������� ��� ����� ����� ��� ��������
    Chain<T>& FirstNodeCreation(int currX, int currY, int healthy)
    {
        // ������������ node pointer
        ChainNode<T>* y = new ChainNode<T>(currX, currY, healthy, 1);

        y->ChainNode<T>::SetNode(); // ������� ���� �����

        // ��� ������� �����
        y->data[0] = currX;
        y->data[1] = currY;
        y->data[2] = healthy;
        // � ������ ������ ���� �������� ��������� ����� ���� ����� �����
        y->data[3] = 1; 
        y->data[4] = 30;

        first = y; // �������� ��� ����� �� �����

        return *this; // ������������ ��� ���� ��� ��������
    }

    // �������� ������/-�� ���� �������
    Chain<T>& Insert(int k, int day)
    {
        // �������������� ���� ��������� �����, ���������� ��� ��� �����
        ChainNode<T>* p = first;
        while (p->link)
            p = p->link;

        while (k-- > 0) {
            // ��������� ����� x,y ��� health
            int currX = RandomInt();
            int currY = RandomInt();
            int healthy = 0;

            // ������������ node pointer
            ChainNode<T>* y = new ChainNode<T>(currX, currY, healthy, day);

            y->ChainNode<T>::SetNode(); // ������� ���� �����

            // ��� ������� �����
            y->data[0] = currX;
            y->data[1] = currY;
            y->data[2] = p->data[2]; // � ����� ��������� �������
            y->data[3] = day;
            // �� ������������ ��� ������ �������� �� ���� ��� ������������ + 30
            y->data[4] = p->data[4] + 30; 
            
            // ��� ����������� ���� �������
            p->link = y;
            p = p->link;
        }

        return *this; // ������������ ��� ���������� �������
    }

    // �������� ���������� ������ ���� �������
    Chain<T>& InsertBetween(int k, int x, int y, int day)
    {
        ChainNode<T>* p = first; // ��������� ��� ����� �����

        int h = p->data[2]; // ������� ��� ����� ���� �� ���������� �������

        // �������������� ���� ���������� ���� k
        if (p->link && p)
            for (int index = 1; index < k - 1; index++)
                p = p->link;

        ChainNode<T>* nextLink = p->link; // ������� ��� ��������� ��� �������� ������

        // ������������ node pointer
        ChainNode<T>* z = new ChainNode<T>(x, y, h, day);

        z->ChainNode<T>::SetNode(); // ������� ���� �����

        // ��� ������� �����
        z->data[0] = x;
        z->data[1] = y;
        z->data[2] = h;
        z->data[3] = day;
        z->data[4] = p->data[4] + 30;

        // ��� ����������� ���� �������
        p->link = z;
        z->link = nextLink;

        return *this; // ������������ ��� ���������� �������
    }

    // ���������� �� ����� ��� ��������
    int Length() const 
    {
        ChainNode<T>* currentNode = first; // ��������� ��� ����� �����
        int value = 1; // �������������� ��� ���� �� ��� ���� ��� ������ ������

        // ��� ���� �����, ��������� ��� ���� ���� 1
        while (currentNode) {
            value++;
            currentNode = currentNode->link;
        }

        return value; // ������������ ��� ����
    }

    // ���������� ������� �������� ����� [1,60]
    int RandomInt()
    {
        int value = rand() % 61;
        return value; // ������������ ��� ����
    }

    // ������� ��� ����� ��� ���� x
    int Search(const T& x) const
    {
        ChainNode<T>* currentNode = first; // �������� ��� ��� �����
        int counter = 1; // ...��� �� ���� ���

        while (currentNode && currentNode->data != x) { // ��� � ������ ������ ��� ����� � x
            // ����������� ���� �������
            currentNode = currentNode->link; 
            counter++;
        }

        if (currentNode) // �� � ������ �������, ������������ �� index ���
            return counter;

        return 0; // ������, ������������ 0
    }

    // ��������� ��� ����� ���� ���� k
    Chain<T>& Delete(int k)
    {
        // �� �� index k ����� �� ������ � � ������ pointer ����� NULL
        if (k < 1 || !first) { 
            cout << "ERROR: Out of Bounds Exception.."; // �� exception ������ ��� �� ����������
        }
        ChainNode<T>* p = first;  // ��������� ��� ����� �����

        // �� ������� �� ��������� � ������ ������, ���� ������� ��� ������� �� ���� ��� ��������
        if (k == 1) { 
            first = first->link;
        } else { // ������, ������� ���� ��� ����������� ����������, ���� ����������� ��� �����
            ChainNode<T>* q = first;
            for (int i = 1; i < k - 1 && q; i++)
                q = q->link;
            p = q->link;
            q->link = p->link;
        }

        delete p; // ����������� ��� �����

        return *this; // ������������ ��� ���������� �������
    }

    void Output()  //Outputs the whole chain in the following format: node1-node2-etc
    {
        ChainNode<T>* p = first;  // ��������� ��� ����� �����

        cout << name; // ����������� �� ����� ����� �� ����� �� ����������� �� �����

        while (p) { // ��� � ������ p ��� ����� NULL, ����������� �� �������� ���
            cout << " -> " << "{" << p->data[3] << ", " << p->data[0] << ", " << p->data[1] << ", " <<p->data[2] << ", " << p->data[4] << "}";
            // format =  -> { day, x, y, health, seconds }

            p = p->link; // ����������� �� ��� ������� �����
        }
        cout << endl;
    }

private:
    ChainNode<T>* first; // ������ ������
    string name; // ����� ��������
};

template<class T>
class ChainNode
{
public:
    friend Chain<T>;

    int currentX; // ������ �
    int currentY; // ������ Y
    int healthy; // 1 �� �����, ������ 0
    int currentDay; // �������� �����

    // Constructor
    ChainNode(int x, int y, int health, int day)
    {
        currentX = x;
        currentY = y;
        healthy = health;
        currentDay = day;
    }

    // ������� ���� ����� �� ��� ����� ��� ��������� ���
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