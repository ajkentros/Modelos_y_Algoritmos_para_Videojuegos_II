#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Ragdoll.h"
#include "ActorSprite.h"
#include "GUI.h"
#include "Suelo.h"
#include "Arma.h"
#include "Cajas.h"


using namespace std;
using namespace sf;
 

class Game
{
private:

	//variables del juego
	float frameTime;			//tiempo por cada frame
	float tiempo;				//tiempo para medir los segundos de jeugo

	Vector2f offsetCajas;		//offset de las cajas, se alejan en x e y según incrementan el nivel

	int fps;					//frame por segundo
	int gameLevel;				//niveles de juego nivel 1 = 1, nivel 2 = 2, nivel 3 = 3
	int gameState;				//variable estado del juego: 0 = menú , 1 = juego, 2 = exit, 3 = gana nivel, 4 = pierde nivel
	int alto_ventana;			//alto de la ventana
	int ancho_ventana;			//ancho de la ventana

	RenderWindow* ventana;		//ventana1 del juego			
	Event* evento1;				//Puntero a objeto Event		
	View* camara1;				//Punetro a objeto View
	
	Clock* reloj1;				//Puntero a objeto Clock
	Time* tiempo1;				//Puntero a objeto Time

	GUI* gui;					//Puntero objeto GUI para maneja la interface de usuario
	int selectedItem;			//selector ítem del menú

	b2World* mundo;				//Puntero a objeto world de box2D

	Suelo* suelo;				//Puntero a objeto Suelo

	Arma* arma;					//Punetro a objeto Arma
		
	Cajas* cajas;				//Puntero a objeto Cajas

	Ragdoll* ragdoll[5];		//Punteros a objetos Ragdoll

	int cantidad_ragdoll;		//cantidad de ragdoll disparados
	int cajasEnPiso;			//variable que controla cantidad de cajas en el piso

	bool active_ragdoll;		//variable que controla si el ragdoll aparece o no

public:

	Game(int ancho_Ventana1, int alto_ventana1, string titulo_ventana1);
	~Game();

	//inicia variables
	void InitVariables();

	//Inicia camara1
	void SetCamara(Vector2f center, Vector2f size, Vector2f offset);

	//Inicia Game
	void InitGame();

	void InitSound();
	
	//Inicia Physic
	void InitPhysics();

	//Loop del juego
	void GameLoop();

	//Controla la variable gameState
	void gameStateCondition();

	//Procesa los menú
	void ConditionGame();

	//Procesa eventos
	void ProssesEvent();

	//Controla movimiento del arma
	void UpdateArma();

	//Controla cantidad de ragdoll disparados
	void UpdateRagdoll();
	
	//Actualiza las físicas
	void UpdatePhysics();
	
	//Mueve el selector hacia arriba
	void ItemSelectUp();

	//Mueve el selector hacia abajo
	void ItemSelectDown();
	
	//Controla el cambio de nivel de juego
	void DetectColission();
	
	//Dibuja el juego
	void DrawGame();

	//cConcersor de grados a radianes
	float deg2rad(float degrees);

};

