#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

using namespace sf;
using namespace std;

class ActorSprite
{
private:
	//define objeto actor
	b2Body* bdy_actor;				//puntero objeto body del actor
	Sprite* fig_actor;				//puntero objeto Sprite del actor
	b2AABB dimensiones;				//objeto boundig box dimensiones 
	b2Vec2 posicion_actorSprite;	//objeto vector posicion del sprite del actor

public:
	//constructor Actor, recibe el body y el sprite que corresponde al body
	ActorSprite(b2Body* _bdy, Sprite* _spr);
	~ActorSprite();

	//Dibuja el Sprite del Actor
	void DrawActorSprite(RenderWindow* _ventana1);

	//Convierte radianes a grados
	float rad2deg(float _radianes);
};

