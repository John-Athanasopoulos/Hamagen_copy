#pragma once

class SquareRegion {
public:
    int minX; // �������� ���� ��� �
    int minY; // �������� ���� ��� �
    int maxX; // ������� ���� ��� �
    int maxY; // ������� ���� ��� �

    // Constructor
    SquareRegion(int miX, int miY, int maX, int maY) {
        minX = miX;
        minY = miY;
        maxX = maX;
        maxY = maY;
    }
};