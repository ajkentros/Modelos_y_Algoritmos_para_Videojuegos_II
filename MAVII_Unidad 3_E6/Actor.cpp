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
		asigna al vetor2D posisi�n la posici�n del actor
		define el m�ximo y m�nimo el cuadro limitador 
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
		configura la figura rect�ngulo:
			su tama�o = tama�o del actor * 2 por que toma el centro como origen
			su origen = tama�o de la figura / 2 por que el centro del body es el origen
			su posici�n = posici�n del actor
			su rotaci�n = �ngulo que est� rotado el actor (se usa el conversor de rad2deg)

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
		asigna al vetor2D posisi�n la posici�n del actor
		posiciona a figura rect�ngulo = posici�n del actor
		rotaci�n de la figura rect�ngulo = �ngulo que est� rotado el actor (se usa el conversor de rad2deg)
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
