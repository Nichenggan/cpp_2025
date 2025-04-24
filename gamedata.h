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
    CHOOSE,
    PLAYING,
    END
};

struct cursur {
    V2 pos;
    cursur(V2 position) : pos(position) {}
    void draw() const {
        G2D::drawCircle(pos, 8, Color::Cyan, true);
    }
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

    V2 heroApos = V2(200, 180);
    V2 heroBPos = V2(450, 180);
    V2 heroCPos = V2(700, 180);

    cursur cursor = cursur(heroApos - V2(10, -20));


    state   gameState = MENU;			// state du jeu

    Hero    player1 = Hero(50, PosCeiling, 1, true, 5, 50, 40, 10, Key::A, Key::D, Key::C, Key::V, Color::Cyan);
    Hero	player2 = Hero(950, PosFloor, 0, false, 5, 50, 40, 10,Key::LEFT, Key::RIGHT, Key::K, Key::L, Color::Red);
    Hero    A = Hero(0, 0, 0, true, 5, 50, 40, 10, Key::Unknown, Key::Unknown, Key::Unknown, Key::Unknown, Color::Black);
    Hero    B = Hero(0, 0, 0, true, 10, 80, 20, 5, Key::Unknown, Key::Unknown, Key::Unknown, Key::Unknown, Color::Black);
    Hero    C = Hero(0, 0, 0, true, 7, 60, 30, 8, Key::Unknown, Key::Unknown, Key::Unknown, Key::Unknown, Color::Black);



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

    void draw_context_menu() const {
        static int Texture_context = -1; // Static variable to store the texture ID
        if (Texture_context == -1) { // Load the texture only if it hasn't been loaded yet
            Texture_context = G2D::ExtractTextureFromPNG("../texture/context.png", Transparency::None);
            if (Texture_context < 0) {
                std::cerr << "Failed to load texture: ../texture/context.png" << std::endl;
                return;
            }
        }
        G2D::drawRectWithTexture(Texture_context, V2(0, 0), V2(1000, 500), 0);
    }

    void draw_context_combat() const {
        static int Texture_context = -1; // Static variable to store the texture ID
        if (Texture_context == -1) { // Load the texture only if it hasn't been loaded yet
            Texture_context = G2D::ExtractTextureFromPNG("../texture/contextcombat.png", Transparency::None);
            if (Texture_context < 0) {
                std::cerr << "Failed to load texture: ../texture/contextcombat.png" << std::endl;
                return;
            }
        }
        G2D::drawRectWithTexture(Texture_context, V2(0, 0), V2(1000, 500), 0);
    }

    void drawHeroAttributes() const {
        // Define positions for the attributes of each hero


        // Define bar dimensions
        int barWidth = 100; // Maximum width of the bar
        int barHeight = 10; // Height of each bar
        int spacing = 15;   // Spacing between bars

        G2D::drawStringFontMono(this->heroApos - V2(100, 0), "Height", 15, 1, Color::White);
        G2D::drawStringFontMono(this->heroApos - V2(100, spacing), "Damage", 15, 1, Color::White);
        G2D::drawStringFontMono(this->heroApos - V2(100, spacing*2), "Speed", 15, 1, Color::White);
        G2D::drawStringFontMono(this->heroApos - V2(100, spacing*3), "Range", 15, 1, Color::White);



        // Draw attributes for Hero A
        G2D::drawRectangle(this->heroApos, V2(barWidth * A.height / 100, barHeight), Color::Green, true); // Height
        G2D::drawRectangle(this->heroApos - V2(0, spacing), V2(barWidth * A.attackDamage / 50, barHeight), Color::Red, true); // Attack Damage
        G2D::drawRectangle(this->heroApos - V2(0, spacing * 2), V2(barWidth * A.speed / 20, barHeight), Color::Blue, true); // Speed
        G2D::drawRectangle(this->heroApos - V2(0, spacing * 3), V2(barWidth * A.attackRange / 100, barHeight), Color::Yellow, true); // Attack Range

        // Draw attributes for Hero B
        G2D::drawRectangle(this->heroBPos, V2(barWidth * B.height / 100, barHeight), Color::Green, true); // Height
        G2D::drawRectangle(this->heroBPos - V2(0, spacing), V2(barWidth * B.attackDamage / 50, barHeight), Color::Red, true); // Attack Damage
        G2D::drawRectangle(this->heroBPos - V2(0, spacing * 2), V2(barWidth * B.speed / 20, barHeight), Color::Blue, true); // Speed
        G2D::drawRectangle(this->heroBPos - V2(0, spacing * 3), V2(barWidth * B.attackRange / 100, barHeight), Color::Yellow, true); // Attack Range

        // Draw attributes for Hero C
        G2D::drawRectangle(this->heroCPos, V2(barWidth * C.height / 100, barHeight), Color::Green, true); // Height
        G2D::drawRectangle(this->heroCPos - V2(0, spacing), V2(barWidth * C.attackDamage / 50, barHeight), Color::Red, true); // Attack Damage
        G2D::drawRectangle(this->heroCPos - V2(0, spacing * 2), V2(barWidth * C.speed / 20, barHeight), Color::Blue, true); // Speed
        G2D::drawRectangle(this->heroCPos - V2(0, spacing * 3), V2(barWidth * C.attackRange / 100, barHeight), Color::Yellow, true); // Attack Range
    }

};
#endif //GAMEDATA_H
