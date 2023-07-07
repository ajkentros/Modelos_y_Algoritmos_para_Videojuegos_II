#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>

#define ITEMS 2 //Nombre del juego, Play = 1, Exit = 2

using namespace sf;
using namespace std;

class GUI
{
private:

	//variables
	int selectedItem;					//selector ítem del menú
	int alto_ventana1;					//alto de la ventana
	int ancho_ventana1;					//ancho de la ventana

	RenderWindow* ventanaGUI;			//instancia objeto ventana del tipo RenderWindow

	Font* font;							//fuente a utiliza ren el juego
	
	Text* tex_Titulo;					//instancia texto del título del juego
	Text* menu[ITEMS];					//instancia texto para el menu
	Text* tex_Nivel;					//texto para cada nivel de juego			
	Text* tex_Exit;						//texto play
	Text* tex_cantidad_Ragdoll;			//intancia texto par amostrar cantidad de ragdoll
	Text* tex_mensaje;

	//Identidad de los escenarios
	Texture* txt_scene[5];				//instancia 3 texturas para la escena
	Sprite* spr_scene[5];				//instancia 3 sprites para la escena

	//Música y sonidos
	Music* musica;						//música del juego
	Music* musica_exit;					//música cuando se abandona el juego

	SoundBuffer* buff_ganaGame;			//buffer sonido cuando gana el juego
	Sound* sound_ganaGame;				//sonido cuando gana el juego
	SoundBuffer* buff_golpeRagdoll;		//buffer sonido cuando un ragdoll se dispara
	Sound* sound_golpeRagdoll;			//sonido cuando un ragdoll se dispara


public:

	//Constructor y Destructor GUI
	GUI(RenderWindow* _ventana, int _alto_ventana1, int _ancho_ventana1);
	~GUI();
	
	//Incicia las escenas
	void InitGUIScenes();
	
	//Inicia los textos
	void InitGUIText();

	//inicia sonidos y música del jeugo
	void IniciaSonidos();

	//Activa musica del juego
	void ActivaMusica();

	//Activa sonido cuando golepa un ragdoll
	void ActivaGolpeRagdoll();

	//Activa sonido cuando pierde un nivel
	void ActivaExitJuego();

	//Activa sonido cuando gana el juego
	void ActivaGanaGame();

	//Dibuja la escena según el estado del juego (gameState, gameLevel), recibe parámetros
	void DrawGUI(RenderWindow* _ventana , int _gameState, int _gameLevel,int _cantidad_Ragdoll);

	//Mueve el selector hacia arriba
	void MoveUpMenu();

	//Mueve el selector hacia abajo
	void MoveDownMenu();
};

