#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace sf;
using namespace std;


int main(int argc, char* argv[])
{
	Game* Juego;
	Juego = new Game(800, 600, "AKE MAVII TP1 Ejercicio 6");
	
	return 0;
}