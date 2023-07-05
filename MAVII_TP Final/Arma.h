#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <box2d/box2d.h>
#include "ActorSprite.h"
#include "Actor.h"

using namespace std;
using namespace sf;


class Arma
{
private:

	//Identidad del arma
	Texture* txt_arma;					//puntero Textura arma
	Sprite* spr_arma;					//puntero Sprite arma
	b2Body* bdy_arma;					//puntero Body arma
	b2BodyDef bdyDef_arma;				//puntero body def arma
	b2Fixture* fix_arma;				//puntero fixture arma
	b2FixtureDef fixDef_arma;			//puntero fixture def arma
	RectangleShape* fig_arma;			//puntero RectangleShape
	ActorSprite* actorSprite_arma;		//puntero ActorSprite arma

	//Identidad del apoyo del arma
	Texture* txt_apoyoarma;					//puntero Textura apoyo arma
	Sprite* spr_apoyoarma;					//puntero Sprite apoyo arma
	b2Body* bdy_apoyoarma;					//puntero Body apoyo arma
	b2BodyDef bdyDef_apoyoarma;				//puntero body def apoy oarma
	b2Fixture* fix_apoyoarma;				//puntero fixture apoyo arma
	b2FixtureDef fixDef_apoyoarma;			//puntero fixture def apoyo arma	
	RectangleShape* fig_apoyoarma;			//puntero RectangleShape
	ActorSprite* actorSprite_apoyoarma;		//puntero ActorSprite arma

	

public:
	//Constructor / Destructor clase Arma
	Arma(b2World*& _mundo, b2Vec2 _posicion, int _tipo);
	~Arma();

	//Inicia Physic del arma
	void InitPhysicsArma();

	//Inicia Imagenes del arma
	void InitImageArma(int _tipo);

	//inicia actor
	void InitActorSpriteArma();

	//Actualiza la posición del arma según la posición del mouse
	void UpdateArma(Vector2f _positionMouseCoordinates);

	//Dibuja el arma (el apoyo y el arma principal)
	void DrawArma(RenderWindow* _ventana);

	//Retorna la posición del arma en el mundo
	Vector2f GetPositionArma();


};

