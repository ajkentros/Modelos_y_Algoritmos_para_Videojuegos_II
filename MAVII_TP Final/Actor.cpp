#include "Actor.h"

using namespace sf;
using namespace std;

Actor::Actor(b2Body* _bdy, RectangleShape* _fig)
{	
	/*
		Asigna a bdy_actor el cuerpo recibido
		Asigna a fig_actor la figura recibida (como rectangulo)
	*/
	bdy_actor = _bdy;
	fig_actor = _fig;

	/*
		Asigna al vetor2D posisi�n la posici�n del actor
		Define el m�ximo y m�nimo el cuadro limitador
	*/
	posicion_actor = bdy_actor->GetPosition();

	//Define las dimensiones m�ximas de la pantalla
	dimensiones.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
	dimensiones.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);

	/*
		por cada i = fixture del actor, desde el primer fixture, hasta el siguiene mientras que no sea Null, =>
		dimensiones: el cuadro limitador alineado al eje = dimensiones del actor
	*/
	for (b2Fixture* f = bdy_actor->GetFixtureList(); f; f = f->GetNext()) 
	{
			dimensiones = f->GetAABB(0);
	}

	/*
		Configura la figura rect�ngulo del actor:
			su tama�o = tama�o del actor * 2 por que toma el centro como origen
			su origen = tama�o de la figura / 2 por que el centro del body es el origen
			su posici�n = posici�n del actor
			su rotaci�n = �ngulo que est� rotado el actor (se usa el conversor de rad2deg)

	*/
	fig_actor->setSize({ dimensiones.GetExtents().x * 2, dimensiones.GetExtents().y * 2 });
	fig_actor->setOrigin(fig_actor->getSize().x / 2.f, fig_actor->getSize().y / 2.f);
	fig_actor->setPosition(posicion_actor.x, posicion_actor.y);
	fig_actor->setRotation(rad2deg(bdy_actor->GetAngle()));
}

Actor::~Actor()
{
}

void Actor::DrawActor(RenderWindow* _ventana1)
{
	/*
		Asigna al vetor2D posisi�n la posici�n del actor
		Posiciona a figura rect�ngulo = posici�n del actor
		Rotaci�n de la figura rect�ngulo = �ngulo que est� rotado el actor (se usa el conversor de rad2deg)
	*/
	posicion_actor = bdy_actor->GetPosition();
	
	fig_actor->setPosition(posicion_actor.x, posicion_actor.y);
	fig_actor->setRotation(rad2deg(bdy_actor->GetAngle()));
	
	_ventana1->draw(*fig_actor);
}

float Actor::rad2deg(float _radians)
{
	//Retorna el valor de grados
	return _radians * 180 / 3.1416f;
}