#pragma warning( disable : 4996 ) 

 
#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>
#include "G2D.h"
#include "button.h"
using namespace std;

// touche P   : mets en pause
// touche ESC : ferme la fenêtre et quitte le jeu


///////////////////////////////////////////////////////////////////////////////
//
//    Données du jeu - structure instanciée dans le main

struct GameData
{
	int     idFrame    = 0;
	int     HeightPix  = 600;          // hauteur de la fenêtre de jeu
	int     WidthPix   = 1000;          // largeur de la fenêtre de jeu
	int     score	  = 0;
	Button  StartButton = Button(V2(400, 300), V2(200, 50), " Start Game", Color::Blue, Color::White);



	GameData()
	{
	}

};



///////////////////////////////////////////////////////////////////////////////
//
// 
//     fonction de rendu - reçoit en paramètre les données du jeu par référence



void render(const GameData & G)
{
    // fond noir	 
	G2D::clearScreen(Color::Black);
	 
	// Titre en haut
	G2D::drawStringFontMono(V2(250, G.HeightPix - 70), string("Gravity Ninja"), 50, 5, Color::Blue);

	// Le buton
	G.StartButton.draw();

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





