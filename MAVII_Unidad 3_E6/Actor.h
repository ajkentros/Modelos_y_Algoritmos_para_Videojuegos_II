#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

using namespace sf;
using namespace std;

class Actor
{
private:
	//instancia objeto body
	b2Body* bdy_actor;

	//instancia objeto rectnagulo
	RectangleShape* fig_actor;

	//instancia objeto dimensiones
	b2AABB dimensiones;

	//instancia objeto posición
	b2Vec2 posicion;


public:
	//constructor Actor, recibe el cbody y la figura que corresponde al body
	Actor(b2Body* cuerpo, RectangleShape* figura);

	//destructor de Actor
	~Actor();

	//dibuja el actor, recibe la ventana donde dibujar
	void DrawActor(RenderWindow* ventana);

	//conversor de radianes a grados
	float rad2deg(float radians);
};

