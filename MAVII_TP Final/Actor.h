#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

using namespace sf;
using namespace std;

//enumerador tipo de actor
enum EnumActor { suelo, arma, cajaMovil, cajaFija};


class Actor
{
private:
	//define objeto actor
	b2Body* bdy_actor;				//puntero actor a objeto clase body
	RectangleShape* fig_actor;		//puntero actor a objeto clase RactangleShape

	b2AABB dimensiones;				//define variable dimensiones del tipo Dimensiones de box2D
	b2Vec2 posicion_actor;			//define variable posición del actor del tipo vector en box2D

	EnumActor type_actor;			//define a tipo de actor según el enumerador en cabecera


public:
	//Constructor y Destructor de la clase Actor, recibe el cbody y la figura que corresponde al body
	Actor(b2Body* _bdy, RectangleShape* _fig);
	~Actor(void);
	
	//Dibuja el actor, recibe la ventana donde dibujar
	void DrawActor(RenderWindow* _ventana1);

	//Conversor de radianes a grados
	float rad2deg(float _radians);

};

