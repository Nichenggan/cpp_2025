#pragma warning( disable : 4996 ) 

 
#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>
#include <thread>

#include "G2D.h"
#include "button.h"
#include "hero.h"
#include "gamedata.h"
using namespace std;

// touche P   : mets en pause
// touche ESC : ferme la fenêtre et quitte le jeu




///////////////////////////////////////////////////////////////////////////////
//
//    Fonction de dessin du terrain



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
			// Health
			G.draw_health();
			// Le buton
			G.EndButton.draw();
			// Le terrain
			G.drawTerrain();
			// Le héros
			G.player1.drawHero();
			G.player2.drawHero();

			G.player1.drawAttackEffect();
			G.player2.drawAttackEffect();


			break;

		case END:
			// Titre en haut
			G2D::drawStringFontMono(V2(50, G.HeightPix - 100), string("Game Ended"), 50, 5, Color::Red);
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

			G.player1.movement(G);
			G.player2.movement(G);
			G.player1.attack(G.player2);
			G.player2.attack(G.player1);

			if (G.player1.health <= 0 || G.player2.health <= 0) {
				G.gameState = END;
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





