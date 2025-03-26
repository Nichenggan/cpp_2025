//
// Created by aminoç　　 on 25-3-26.
//
#include "Button.h"

Button::Button(V2 pos, V2 sz, std::string lbl, Color col, Color txtCol)
    : position(pos), size(sz), label(lbl), color(col), textColor(txtCol) {}

void Button::draw() const {
    G2D::drawRectangle(position, size, color, true);
    G2D::drawStringFontMono(position + V2(10, size.y / 2 - 10), label, 20, 2, textColor);
}

bool Button::isClicked(int mouseX, int mouseY) const {
    return mouseX >= position.x && mouseX <= position.x + size.x &&
           mouseY >= position.y && mouseY <= position.y + size.y;
}