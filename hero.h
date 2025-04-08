#ifndef HERO_H
#define HERO_H

#include <vector>
#include "G2D.h"
struct Hero {
    int posX;
    int posY;
    int direction = 1; // 1 = vers la droite, 0 = vers la gauche
    bool inversed = true;
    int speed = 5;
    int height = 50;
    double T0 = -1;

    Hero(int x, int y) : posX(x), posY(y) {};
    void drawHero() const{
        G2D::drawCircle(V2(posX, posY), 5, Color::Green, true);
        // Calculate the vertices of the equilateral triangle
        std::vector<V2> PointList;

        int halfBase = height / 2; // Half the base length of the triangle

        if (direction == 1 && inversed == true) { // Facing right
            PointList.push_back(V2(posX, posY)); // Top vertex
            PointList.push_back(V2(posX, posY - height)); // Bottom-left vertex
            PointList.push_back(V2(posX + halfBase, posY - height/2)); // Bottom-right vertex
        } else if (direction == 0 && inversed == true) { // Facing left
            PointList.push_back(V2(posX, posY)); // Top vertex
            PointList.push_back(V2(posX, posY - height)); // Bottom-right vertex
            PointList.push_back(V2(posX - halfBase, posY - height/2)); // Bottom-left vertex
        } else if (direction == 1 && inversed == false) {
            PointList.push_back(V2(posX, posY)); // buttom vertex
            PointList.push_back(V2(posX, posY + height)); // Bottom-right vertex
            PointList.push_back(V2(posX + halfBase, posY + height/2));
        } else {
            PointList.push_back(V2(posX, posY)); // buttom vertex
            PointList.push_back(V2(posX, posY + height)); // Bottom-right vertex
            PointList.push_back(V2(posX - halfBase, posY + height/2));
        }

        // Draw the triangle
        G2D::drawPolygon(PointList, Color::Cyan, true);
    }

    void turn_left() {
        direction = 0;
    }

    void turn_right() {
        direction = 1;
    }

    void move_left() {
        turn_left();
        posX -= speed;
    }

    void move_right() {
        turn_right();
        posX += speed;
    }

    void turn_over() {
        if (inversed) {
            posY -= height;
        } else {
            posY += height;
        }
        inversed = !inversed;
    }

};

#endif // HERO_H