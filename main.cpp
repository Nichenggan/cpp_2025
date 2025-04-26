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



void render( GameData & G)
{
    // fond noir	 
	G2D::clearScreen(Color::Black);

	switch (G.gameState) {
		case MENU:
			G.draw_context_menu();
			// Titre en haut
			G2D::drawStringFontMono(V2(250, G.HeightPix - 100), string("Gravity Ninja"), 50, 6, Color::White);
			// Le buton
			G2D::drawStringFontMono(V2(300, G.HeightPix - 250), string("Press Enter to start"), 25, 2, Color::White);


			//Instruction
			G2D::drawStringFontMono(V2(100, 150), string("Player1 -> Press 'A' 'D' to move, 'C' to Change Gravity, 'G' to Attack"), 15, 1, Color::White);
			G2D::drawStringFontMono(V2(100, 120), string("Player2 -> Press '<-' '->' to move, 'K' to Change Gravity, 'L' to Attack"), 15, 1, Color::White);

		break;

		case CHOOSE:
			G.draw_context_combat();
			G.player1.drawPic(V2(320, 270));
			G.player2.drawPic(V2(570, 270));
			G.cursor.draw();
			G2D::drawStringFontMono(V2(300, 250), string("Player 1"), 25, 2, Color::White);
			G2D::drawStringFontMono(V2(550, 250), string("Player 2"), 25, 2, Color::White);

			G2D::drawStringFontMono(V2(200, 200), string("Hero A"), 20, 2, Color::White);
			G2D::drawStringFontMono(V2(450, 200), string("Hero B"), 20, 2, Color::White);
			G2D::drawStringFontMono(V2(700, 200), string("Hero C"), 20, 2, Color::White);
			G.drawHeroAttributes();

			G.A.drawPic(G.heroApos - V2(0, 150));
			G.B.drawPic(G.heroBPos - V2(0, 150));
			G.C.drawPic(G.heroCPos - V2(0, 150));

			G2D::drawStringFontMono(V2(20, 450), string("Use Enter to choose Hero, use G to start game"), 15, 2, Color::White);


		break;


		case PLAYING:
			G.draw_context_combat();
			// Health
			G.draw_health();


			// Le héros
			G.player1.drawHero();
			G.player2.drawHero();



			break;

		case END:
			// Titre en haut
			G2D::drawStringFontMono(V2(50, G.HeightPix - 100), string("Game Ended"), 50, 5, Color::Red);
			if (G.player1.health <= 0) {
				G2D::drawStringFontMono(V2(50, G.HeightPix - 200), string("Player 2 wins!"), 50, 5, Color::Red);
			} else {
				G2D::drawStringFontMono(V2(50, G.HeightPix - 200), string("Player 1 wins!"), 50, 5, Color::Red);
			}

			G2D::drawStringFontMono(V2(50, G.HeightPix - 400), string("Press ENTER to return to main menu"), 10, 1, Color::White);


			// Le buton
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

	switch (G.gameState) {

		case MENU:
			if (G2D::keyHasBeenHit(Key::ENTER)){
				G.gameState = CHOOSE;
			}
			break;

		case CHOOSE:
			static int cursorIndex = 0; // Tracks the current cursor position (0 = Hero A, 1 = Hero B, 2 = Hero C)
			static int heroSelectionCount = 0; // Tracks the number of hero selections
			static bool keyReleased = true;
			// Hero selection logic
			if (keyReleased && G2D::isKeyPressed(Key::LEFT)) {
				cursorIndex = (cursorIndex + 2) % 3; // Move left (wrap around)
				G.cursor.pos = (cursorIndex == 0) ? G.heroApos - V2(10, -20) : (cursorIndex == 1) ? G.heroBPos- V2(10, -20) : G.heroCPos- V2(10, -20);
				keyReleased = false;
			} else if (keyReleased && G2D::isKeyPressed(Key::RIGHT)) {
				cursorIndex = (cursorIndex + 1) % 3; // Move right (wrap around)
				G.cursor.pos = (cursorIndex == 0) ? G.heroApos- V2(10, -20) : (cursorIndex == 1) ? G.heroBPos- V2(10, -20) : G.heroCPos- V2(10, -20);
				keyReleased = false;
			}
			if (!G2D::isKeyPressed(Key::LEFT) && !G2D::isKeyPressed(Key::RIGHT)) {
				keyReleased = true;
			}


			// Handle hero selection
			if (G2D::keyHasBeenHit(Key::ENTER)) {
				if (heroSelectionCount == 0) {
					G.player1 = (cursorIndex == 0) ? G.A : (cursorIndex == 1) ? G.B : G.C;
					heroSelectionCount++;
					G.player1.initAsPlayer1(G);

				} else if (heroSelectionCount == 1) {
					G.player2 = (cursorIndex == 0) ? G.A : (cursorIndex == 1) ? G.B : G.C;
					G.player2.initAsPlayer2(G);
					heroSelectionCount++;

				}
			}


			if (heroSelectionCount >= 2 && G2D::isKeyPressed(Key::G)) {
				G.gameState = PLAYING;
			}
		break;

		case PLAYING:
			if (G2D::keyHasBeenHit(Key::ENTER) ){
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
			if (G2D::keyHasBeenHit(Key::ENTER) ){
				G.gameState = MENU;
				G.reinitialise();
				heroSelectionCount = 0;
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





