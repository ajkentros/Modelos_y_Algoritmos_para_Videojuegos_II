#include "Game.h"

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

Game::Game(int ancho, int alto, string titulo)
{
	/*
		inicia fps = 60 segundos por cada frame
		inicia frameTime = 0.0166
	*/
	fps = 60;
	frameTime = 1.0f / fps;
	time2 = 0;

	/*inicia ventana1 
		establece alto, ancho y t�tulo
		visible = true
		limita el FrameLimit = fps
	*/
	ventana1 = new RenderWindow(VideoMode(ancho, alto), titulo);
	ventana1->setVisible(true);
	ventana1->setFramerateLimit(fps);

	//inicia evento1
	evento1 = new Event();

	//inicia tiempo1
	tiempo1 = new Time();

	//inicia reloj1
	reloj1 = new Clock();
	
	
	//inicia Game = inicia las f�sicas, las im�genes y el loop del juego
	InitGame();


}

Game::~Game()
{
}

void Game::InitGame()
{
	//Inicia camara1
	SetCamara();

	//Inicia las f�sicas
	InitPhysics();

	//inicia las imagenes
	InitImage();

	//inicia actor
	InitActor();

	//Loop del juego
	GameLoop();

}

void Game::SetCamara()
{
	/*
		inicializa posici�n de camara1 = 
		inicializa tama�o de camara1 =
		asigna camara1 a la ventana1
	*/
	camara1 = new View({ 5.f, 5.f }, { 10.f, 10.f });

	camara1->move(45.f, 90.f);
	
	ventana1->setView(*camara1);
}



void Game::InitPhysics()
{
	//Inicializa mundo1 con la gravedad = 9.81
	mundo1 = new b2World(b2Vec2(0.0f, 9.8f));

	/*Suelo
		suelo coo un body est�tico
		posici�n del suelo en x=50 y=102
		crea el suelo en mundo1
		suelo = pol�gono = caja de 100x5
		definiciones del fixture suelo
		crea fixture suelo con definiciones de fixDef_suelo
	*/
	bdyDef_suelo.type = b2_staticBody;
	bdyDef_suelo.position = b2Vec2(50.f, 102.f);

	bdy_suelo = mundo1->CreateBody(&bdyDef_suelo);

	b2PolygonShape shape_suelo;				//pol�gono contenedor del suelo
	shape_suelo.SetAsBox(50.f, 2.5f);


	fixDef_suelo.shape = &shape_suelo;
	fixDef_suelo.restitution = 0.f;
	fixDef_suelo.friction = 0.3f;
	fixDef_suelo.density = 1.f;

	fix_suelo = bdy_suelo->CreateFixture(&fixDef_suelo);

	
	
}

void Game::InitImage()
{

	/*
		instancia objeto ragdoll1 del tipo Radgoll en la posici�n y en el mundo
	*/
	Vector2f posicion = Vector2f(50.f, 95.f);
	ragdoll1 = new Ragdoll(posicion, *mundo1);

	/*
		instancia la figura suelo
	*/
	fig_suelo = new RectangleShape;
	fig_suelo->setFillColor(Color::Red);
	

}
//inicia actor
void Game::InitActor()
{
	//instancia actor suelo
	actor_suelo = new Actor(bdy_suelo, fig_suelo);

}

void Game::GameLoop()
{
	/*
		mientras la ventana1 est� abierta =>
			en timepo1 se guarda el tiempo transcurrido
			si el tiempo transcurrido en seg + 0.016 < tiempo transcurrido en sg =>
				limpia ventana1
				procesa eventos
				actualiza f�sicas
				dibuja en ventana1
				muestra en ventana1

	*/
	while (ventana1->isOpen())
	{
		*tiempo1 = reloj1->getElapsedTime();

		if (time2 + frameTime < tiempo1->asSeconds())
		{
			time2 = tiempo1->asSeconds();

			ventana1->clear();

			ProssesEvent();

			UpdatePhysics();

			Draw();

			ventana1->display();
		}
	}

}

void Game::ProssesEvent()
{
	/*
		mientras la ventana1 escuche event1 =>
			si clic en close 0> se cierra la ventana1
	*/
	while (ventana1->pollEvent(*evento1))
	{
		switch (evento1->type)
		{
		case Event::Closed:
			ventana1->close();
			break;

		default:
			break;
		}
	}

}

void Game::UpdatePhysics()
{
	/*
		configura el timpo de la simulaci�n
		limpia las fuerza activas en la simulaci�n
		llama al debug data
	*/
	mundo1->Step(frameTime, 8, 8);
	mundo1->ClearForces();
	mundo1->DebugDraw();

}

void Game::Draw()
{
	//dibuja actor suelo y actor Ragdoll
	actor_suelo->DrawActor(ventana1);

	ragdoll1->DrawRagdoll(*ventana1);

	
}


