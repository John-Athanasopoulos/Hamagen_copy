#pragma once

class SquareRegion {
public:
    int minX; // Ελάχιστη τιμή του Χ
    int minY; // Ελάχιστη τιμή του Υ
    int maxX; // Μέγιστη τιμή του Χ
    int maxY; // Μέγιστη τιμή του Υ

    // Constructor
    SquareRegion(int miX, int miY, int maX, int maY) {
        minX = miX;
        minY = miY;
        maxX = maX;
        maxY = maY;
    }
};