#pragma warning( disable : 4996 ) 

 
#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>
#include <thread>

#include "G2D.h"
#include "button.h"
#include "hero.h"
using namespace std;

// touche P   : mets en pause
// touche ESC : ferme la fenêtre et quitte le jeu

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
	Hero    hero = Hero(50, PosCeiling);

	GameData()
	{
	}

};



///////////////////////////////////////////////////////////////////////////////
//
//    Fonction de dessin du terrain

void draw_terrain(const GameData &G) {
	// Draw the ceiling (top boundary)
	for (int pos = G.PosCeiling + 4; pos >= G.PosCeiling; pos--) {
		G2D::drawLine(V2(0, pos), V2(G.WidthPix, pos), Color::Blue);
	}
	for (int pos = G.PosFloor - 4; pos <= G.PosFloor; pos++) {
		G2D::drawLine(V2(0, pos), V2(G.WidthPix, pos), Color::White);
	}

	// Draw the floor (bottom boundary)
}

///////////////////////////////////////////////////////////////////////////////
//
// 
//     fonction de rendu - reçoit en paramètre les données du jeu par référence



void render(const GameData & G)
{
    // fond noir	 
	G2D::clearScreen(Color::Black);

	switch (G.gameState) {
		case MENU:
			// Titre en haut
			G2D::drawStringFontMono(V2(250, G.HeightPix - 100), string("Gravity Ninja"), 50, 5, Color::Blue);
			// Le buton
			G.StartButton.draw();
			break;

		case PLAYING:
			// Score
			G2D::drawStringFontMono(V2(50, G.HeightPix - 50), string("Your Score : ") + to_string(G.score), 30, 5, Color::Green);
			// Le buton
			G.EndButton.draw();
			// Le terrain
			draw_terrain(G);
			// Le héros
			G.hero.drawHero();




			break;

		case END:
			// Titre en haut
			G2D::drawStringFontMono(V2(50, G.HeightPix - 100), string("Game Ended, your Score is : "), 50, 5, Color::Red);
			// Le buton
			G.BackButton.draw();
			break;
	}
	 


	// The mouse position
	int mouseX, mouseY;
	G2D::getMousePos(mouseX, mouseY);

	// The curser
	G2D::drawCircle(V2(mouseX, mouseY), 5, Color::Cyan, true);

	// précise que l'on est en pause

	if ( G2D::isOnPause() )
		G2D::drawStringFontMono(V2(100, G.HeightPix / 2), string("Pause..."), 50, 5, Color::Yellow);

	// envoie les tracés à l'écran

	G2D::Show();
}

bool is_movable_left(GameData G) {
	bool border = (G.hero.posX >= 10) && (G.hero.posX <= G.WidthPix - 10 + G.hero.speed);

	return border;
}

bool is_movable_right(GameData G) {
	bool border = (G.hero.posX >= 10 - G.hero.speed) && (G.hero.posX <= G.WidthPix - 10);

	return border;
}


	
///////////////////////////////////////////////////////////////////////////////
//
//
//      Gestion de la logique du jeu - reçoit en paramètre les données du jeu par référence

void Logic(GameData & G) // appelé 20 fois par seconde
{
	G.idFrame += 1;
	int mouseX, mouseY;
	G2D::getMousePos(mouseX, mouseY);
	switch (G.gameState) {

		case MENU:
			if (G.StartButton.isClicked(mouseX, mouseY) ){
					G.gameState = PLAYING;
			}
			break;

		case PLAYING:
			if (G.EndButton.isClicked(mouseX, mouseY) ){
					G.gameState = END;
			}

			if (G2D::isKeyPressed(Key::LEFT) && is_movable_left(G)) {
				G.hero.move_left();
			}
			if (G2D::isKeyPressed(Key::RIGHT) && is_movable_right(G)) {
				G.hero.move_right();
			}
			if (G2D::isKeyPressed(Key::V)) {
				if (G2D::elapsedTimeFromStartSeconds() - G.hero.T0 > 0.5) {
					G.hero.T0 = G2D::elapsedTimeFromStartSeconds();
					if(G.hero.inversed) {
						G.hero.turn_over();
						G.hero.inversed = false;
					}
					else {
						G.hero.turn_over();
						G.hero.inversed = true;
					}
				}
			}
			// Le hero change direction
			if (G2D::elapsedTimeFromStartSeconds() - G.hero.T0 < 0.5) {
				if (!G.hero.inversed)
					G.hero.posY = G.PosCeiling - G.hero.height - (G.PosCeiling - G.hero.height - G.PosFloor) * (G2D::elapsedTimeFromStartSeconds() - G.hero.T0) * 2;
				else
					G.hero.posY = G.PosFloor + G.hero.height + (G.PosCeiling - G.hero.height - G.PosFloor) * (G2D::elapsedTimeFromStartSeconds() - G.hero.T0) * 2;

			}
			break;

		case END:
			if (G.BackButton.isClicked(mouseX, mouseY) ){
				G.gameState = MENU;
			}
			break;

	}

	 
}
 

///////////////////////////////////////////////////////////////////////////////
//
//
//        Démarrage de l'application



int main(int argc, char* argv[])
{
	GameData G;   // instanciation de l'unique objet GameData qui sera passé aux fonctions render et logic

	G2D::initWindow(V2(G.WidthPix, G.HeightPix), V2(200, 200), string("Gravity Ninja"));

	int callToLogicPerSec = 50;  // si vous réduisez cette valeur => ralentit le jeu

	G2D::Run(Logic, render, G, callToLogicPerSec,true);


}





