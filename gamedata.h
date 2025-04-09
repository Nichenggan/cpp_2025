//
// Created by aminoç　　 on 25-4-9.
//



#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "Button.h"
#include "hero.h"
#include <string>
enum state {
    MENU,
    PLAYING,
    END
};

///////////////////////////////////////////////////////////////////////////////
//
//    Données du jeu - structure instanciée dans le main

struct GameData
{
    int     idFrame    = 0;
    int     HeightPix  = 500;          // hauteur de la fenêtre de jeu
    int     WidthPix   = 1000;          // largeur de la fenêtre de jeu
    int     score	  = 0;
    int     PosCeiling   = 400;
    int	    PosFloor     = 150;
    state   gameState = MENU;			// state du jeu
    Button  StartButton = Button(V2(400, 200), V2(200, 50), " Start Game", Color::Blue, Color::White);
    Button  EndButton  = Button(V2(100, 50), V2(200, 50), " End Game", Color::Red, Color::White);
    Button  BackButton = Button(V2(400, 100), V2(200, 50), " Back to Menu", Color::Blue, Color::White);
    Hero    player1 = Hero(50, PosCeiling, 1, true, 5, 50, 15, Key::A, Key::D, Key::C, Key::V, Color::Cyan);
    Hero	player2 = Hero(950, PosFloor, 0, false, 5, 50, 15, Key::LEFT, Key::RIGHT, Key::K, Key::L, Color::Red);

    GameData()
    {
    }

    void drawTerrain() const{
        // Draw the ceiling (top boundary)
        for (int pos = this->PosCeiling + 4; pos >= this->PosCeiling; pos--) {
            G2D::drawLine(V2(0, pos), V2(this->WidthPix, pos), Color::Blue);
        }
        for (int pos = this->PosFloor - 4; pos <= this->PosFloor; pos++) {
            G2D::drawLine(V2(0, pos), V2(this->WidthPix, pos), Color::White);
        }

        // Draw the floor (bottom boundary)
    }

    void draw_health() const {
        // Player 1 health bar (left side)
        int player1HealthBarWidth = player1.health * 2; // Assuming max health is 100, width is scaled
        G2D::drawRectangle(V2(0, HeightPix - 80), V2(player1HealthBarWidth, 20), Color::Red, true);
        G2D::drawStringFontMono(V2(10, HeightPix - 50), "Player1", 30, 4, Color::White);

        // Player 2 health bar (right side)
        int player2HealthBarWidth = player2.health * 2; // Assuming max health is 100, width is scaled
        G2D::drawRectangle(V2(WidthPix - player2HealthBarWidth, HeightPix - 80), V2(player2HealthBarWidth, 20), Color::Red, true);
        G2D::drawStringFontMono(V2(WidthPix - 150, HeightPix - 50), "Player2", 30, 4, Color::White);
    }

};
#endif //GAMEDATA_H
