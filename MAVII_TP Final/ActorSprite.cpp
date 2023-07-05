#include "ActorSprite.h"

using namespace sf;
using namespace std;

ActorSprite::ActorSprite(b2Body* _bdy, Sprite* _spr) 
{
	/*
		Asigna a bdy_actor el cuerpo recibido
		Asigna a fig_actor la figura recibida (como rectangulo)
	*/
	bdy_actor = _bdy;
	fig_actor = _spr;

	/*
		Asigna al vetor2D posisi�n la posici�n del actor
		Define el m�ximo y m�nimo el cuadro limitador
	*/
	posicion_actorSprite = bdy_actor->GetPosition();

	//Define dimensiones m�ximas de la pantalla
	dimensiones.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
	dimensiones.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);

	/*
		por cada i = fixture del actor, desde el primer fixture, hasta el siguiene mientras que no sea Null, =>
			dimensiones: el cuadro limitador alineado al eje = dimensiones del actor
	*/
	for (b2Fixture* f = bdy_actor->GetFixtureList(); f; f = f->GetNext()) {
		dimensiones = f->GetAABB(0);
	}

	/*
		Configura el sprite del actor:
			su origen = tama�o de la figura/2 por que el centro del body es el origen
			su posici�n = posici�n del actor
			su rotaci�n = �ngulo que est� rotado el actor (se usa el conversor de rad2deg)
			su escala
				factor de escala en X = ancho de la ventana / ancho de la textura del spr
				factor de escala en Y = alto de la ventana / alto de la textura del spr
	*/
	fig_actor->setOrigin(fig_actor->getTexture()->getSize().x / 2.f, fig_actor->getTexture()->getSize().y / 2.f);
	fig_actor->setPosition(posicion_actorSprite.x, posicion_actorSprite.y);
	fig_actor->setRotation(rad2deg(bdy_actor->GetAngle()));
	fig_actor->setScale(dimensiones.GetExtents().x * 2.f / fig_actor->getTexture()->getSize().x, dimensiones.GetExtents().y * 2.f / fig_actor->getTexture()->getSize().y);
}

ActorSprite::~ActorSprite()
{
}

void ActorSprite::DrawActorSprite(RenderWindow* _ventana1) 
{
	/*
		Asigna al vetor2D posisi�n la posici�n del actor
		Posiciona a figura rect�ngulo = posici�n del actor
		Rotaci�n de la figura rect�ngulo = �ngulo que est� rotado el actor (se usa el conversor de rad2deg)
	*/
	posicion_actorSprite = bdy_actor->GetPosition();
	fig_actor->setPosition(posicion_actorSprite.x, posicion_actorSprite.y);
	fig_actor->setRotation(rad2deg(bdy_actor->GetAngle()));
	_ventana1->draw(*fig_actor);
}

float ActorSprite::rad2deg(float radianes) 
{
	//Retorna los grados seg�n los radianes recibidos por par�metro
	return radianes * 180 / 3.14f;
}