#include "Actor.h"

using namespace sf;
using namespace std;

Actor::Actor(b2Body* cuerpo, RectangleShape* figura)
{
	/*
		asigna a bdy_actor el cuerpo recibido
		asigna a fig_actor la figura recibida (como rectangulo) 
	*/
	bdy_actor = cuerpo;
	fig_actor = figura;

	/*
		asigna al vetor2D posisión la posición del actor
		define el máximo y mínimo el cuadro limitador 
	*/
	posicion = bdy_actor->GetPosition();

	dimensiones.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
	dimensiones.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
	
	/*
		por cada i = ficture del actor, desde el primer fixture, hasta el siguiene mientras que no sea Null, =>
		dimensiones: el cuadro limitador alineado al eje = dimensiones del actor
	*/
	for (b2Fixture* i = bdy_actor->GetFixtureList(); i; i = i->GetNext())
	{
		dimensiones = i->GetAABB(0);
	}

	/*
		configura la figura rectángulo:
			su tamaño = tamaño del actor * 2 por que toma el centro como origen
			su origen = tamaño de la figura / 2 por que el centro del body es el origen
			su posición = posición del actor
			su rotación = ángulo que está rotado el actor (se usa el conversor de rad2deg)

	*/
	fig_actor->setSize({ dimensiones.GetExtents().x * 2, dimensiones.GetExtents().y * 2 });

	fig_actor->setOrigin(fig_actor->getSize().x / 2.f, fig_actor->getSize().y / 2.f);

	fig_actor->setPosition(posicion.x, posicion.y);

	fig_actor->setRotation(rad2deg(bdy_actor->GetAngle()));
}

Actor::~Actor()
{
}

//dibuja el actor, recibe la ventana donde dibujar
void Actor::DrawActor(RenderWindow* ventana)
{
	/*
		asigna al vetor2D posisión la posición del actor
		posiciona a figura rectángulo = posición del actor
		rotación de la figura rectángulo = ángulo que está rotado el actor (se usa el conversor de rad2deg)
	*/
	posicion = bdy_actor->GetPosition();

	fig_actor->setPosition(posicion.x, posicion.y);

	fig_actor->setRotation(rad2deg(bdy_actor->GetAngle()));

	ventana->draw(*fig_actor);

}

//conversor de radianes a grados
float Actor::rad2deg(float radians)
{
	return radians * 180 / 3.1416f;
}
