#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SFMLRenderer.h"
#include "Actor.h"
#include "Ragdoll.h"

using namespace sf;
using namespace std;

class Game
{
private:
	//Identidad del frame
	float frameTime;			//tiempo por cada frame
	float time2;				//tiempo para medir los segundos de jeugo
	int fps;					//frame por segundo
	
	// Identidad de la ventana1
	int alto;					//alto de la ventana1
	int ancho;					//ancho de la ventana1
	RenderWindow* ventana1;		//ventana1 del juego
	Color clearColor;			//limpia los colores en la ventana
	Event* evento1;				//escucha eventos
	Time* tiempo1;				//mide el tiempo entre frame
	Clock* reloj1;				//guarda el tiempo transcurrido 

	//Identidad de la camara
	View* camara1;

	//Identidad de objetos de box2d
	b2World* mundo1;			//instancia objeto mundo1
	SFMLRenderer* debugRender;	//instancia objeto debugRender

	//Identidad de Suelo
	b2Body* bdy_suelo;			//body suelo
	b2BodyDef bdyDef_suelo;		//definiciones body suelo
	b2Fixture* fix_suelo;		//fixture suelo
	b2FixtureDef fixDef_suelo;	//definiciones del fixture suelo
	Actor* actor_suelo;			//instancia objeto Actor para el suelo
	RectangleShape* fig_suelo;	//instancia objeto rectángulo para la figura del suelo

	//Identidad del Ragdoll
	Ragdoll* ragdoll1;


	//Instancia resortes para cad parte del ragdoll
	b2DistanceJoint* jnt_ragdoll[5];		//constucción del resorte 
	b2DistanceJointDef jntDef_ragdoll[5];	//definiciones de cada resorte

public:
	//Constructores, destructores
	Game(int ancho, int alto, std::string titulo);
	~Game();

	//Inicia camara1
	void SetCamara();

	//Inicia Game
	void InitGame();

	//Inicia las físicas 2D
	void InitPhysics();

	//Loop del juego
	void GameLoop();

	//Procesa eventos
	void ProssesEvent();

	//Actualiza las físicas
	void UpdatePhysics();

	//Dibuja
	void Draw();

	//Inicia las imágenes
	void InitImage();

	//inicia actor
	void InitActor();




};

