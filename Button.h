//
// Created by aminoç　　 on 25-3-26.
//

#ifndef BUTTON_H
#define BUTTON_H

#include "G2D.h"
#include <string>

class Button {
public:
    V2 position;
    V2 size;
    std::string label;
    Color color;
    Color textColor;
    bool isPressed = false;

    Button(V2 pos, V2 sz, std::string lbl, Color col, Color txtCol);

    void draw() const;
    bool isClicked(int mouseX, int mouseY) const;
};

#endif // BUTTON_H
