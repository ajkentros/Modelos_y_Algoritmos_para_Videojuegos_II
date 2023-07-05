#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <box2d/box2d.h>
#include "ActorSprite.h"
#include "Actor.h"

using namespace std;
using namespace sf;

const float coordenadaX_cajaFija = 50.5f;	//define posición en x de la cajaFija 
const float coordenadaY_cajaFija = 99.f;	//define posición en y de la cajaFija 


class Cajas
{
private:

	int cantidadCajas;							//variable que define la cantidad de cajas en la escena

	//Identidad de caja fija
	Texture* txt_cajaFija[3];					//puntero vector texture caja fija
	Sprite* spr_cajaFija[3];					//puntero vector sprite caja fija
	b2Body* bdy_cajaFija[3];					//puntero vector body caja fija
	b2BodyDef bdyDef_cajaFija[3];				//puntero vector body def caja fija
	b2Fixture* fix_cajaFija[3];					//puntero vector Fixture caja fija
	b2FixtureDef fixDef_cajaFija[3];			//puntero vector Fixture def caja fija
	Actor* actor_cajaFija;						//puntero Actor caja fija
	RectangleShape* fig_cajaFija[3];			//puntero vector Arreglo RectanguleShape caja fija
	ActorSprite* actorSprite_cajaFija[3];		//puntero vector ActorSprite caja fija

	//Identidad de caja móvil
	Texture* txt_cajaMovil[3];					//puntero vector texture caja móvil
	Sprite* spr_cajaMovil[3];					//puntero vector sprite caja móvil
	b2Body* bdy_cajaMovil[3];					//puntero vector body caja móvil
	b2BodyDef bdyDef_cajaMovil[3];				//puntero vector body def caja móvil
	b2Fixture* fix_cajaMovil[3];				//puntero vector Fixture caja móvil
	b2FixtureDef fixDef_cajaMovil[3];			//puntero vector Fixture def caja móvil
	Actor* actor_cajaMovil;						//puntero Actor caja móvil
	RectangleShape* fig_cajaMovil[3];			//puntero vector Arreglo RectanguleShape caja móvil
	ActorSprite* actorSprite_cajaMovil[3];		//puntero vector ActorSprite caja móvil

	//Instancia resortes para caja móvil
	b2DistanceJoint* jnt_cajaMovil;				//puntero resorte caja móvil
	b2DistanceJointDef jntDef_cajaMovil;		//puntero resorte def caja móvil

public:
	//Contructor y destructor clase Cajas
	Cajas(b2World*& _mundo, Vector2f _offsetCajas, int _tipo, int _cantidadCajas);
	~Cajas();

	//Inicia Physic de las cajas
	void InitPhysicsCajas(b2World*& _mundo);

	//Inicia imágenes de las cajas según el tipo controlado desde Game
	void InitImageCajas(int _tipo);

	//Inicia Actor para las cajas
	void InitActorSpriteCajas();

	//Dibuja las cajas en la escena
	void DrawCajas(RenderWindow* _ventana);

	//Retorna el global bound de la caja móvil según el orden de aparición
	FloatRect GetBoxCajaMovil(int _i);

	//Retorna el global bound de la caja fija según el orden de aparición
	FloatRect GetBoxCajaFija(int _i);


};

