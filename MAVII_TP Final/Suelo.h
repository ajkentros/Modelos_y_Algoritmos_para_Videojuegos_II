#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <box2d/box2d.h>
#include "ActorSprite.h"
#include "Actor.h"

using namespace std;
using namespace sf;


class Suelo
{
private:

	//Identidad del Suelo
	Texture* txt_suelo;						//puntero objeto Textura suelo
	Sprite* spr_suelo;						//puntero objeto Sprite suelo
	b2Body* bdy_suelo;						//puntero objeto body suelo
	b2BodyDef bdyDef_suelo;					//objeto body def suelo
	b2Fixture* fix_suelo;					//puntero objeto Fixture suelo
	b2FixtureDef fixDef_suelo;				//objeto Fixture def suelo
	RectangleShape* fig_suelo;				//puntero objeto RectangleShape suelo
	ActorSprite* actorSprite_suelo;			//puntero objeto ActorSprite suelo


public:
	//Constructor y Destructor de clase Suelo
	Suelo(b2World* &_mundo, b2Vec2 _posicion);
	~Suelo();

	//Inicia Physic del suelo
	void InitPhysicsSuelo();

	//Inicia Imagenes del suelo
	void InitImageSuelo();

	//inicia ActorSprite del suelo
	void InitActorSpriteSuelo();

	//Dibuja el suelo
	void DrawSuelo(RenderWindow* _ventana);

	//Retorna el global bound del suelo
	FloatRect GetBoxSuelo();

};

