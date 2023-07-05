#include "Arma.h"

Arma::Arma(b2World*& _mundo, b2Vec2 _posicion, int _tipo)
{
	/*
		Inicializa el body del arma y el apoyo del arma en el mundo
		Game pasa como parámetro la posición del arma (opción para modificar según dificultad del juego)
	*/
	//Inicializa apoyo de arma
	bdyDef_apoyoarma.type = b2_staticBody;
	bdyDef_apoyoarma.position = b2Vec2(_posicion);
	bdy_apoyoarma = _mundo->CreateBody(&bdyDef_apoyoarma);

	//Inicializa arma
	bdyDef_arma.type = b2_staticBody;
	bdyDef_arma.position = b2Vec2(_posicion.x + 0.0f , _posicion.y - 0.74f );
	bdy_arma = _mundo->CreateBody(&bdyDef_arma);

	//Llama a las funciones que inicializan las físicas, las imágenes y los sprite en el mundo
	InitPhysicsArma();
	InitImageArma(_tipo);
	InitActorSpriteArma();
}

Arma::~Arma()
{
}

void Arma::InitPhysicsArma()
{
	/*
		Inicializa las físicas del arma y el apoyo del arma en el mundo
	*/
	//Inicializa la física del apoyo del arma
	b2PolygonShape shp_apoyoarma;
	shp_apoyoarma.SetAsBox(0.4f, 0.48f);

	fixDef_apoyoarma.shape = &shp_apoyoarma;
	fixDef_apoyoarma.density = 1.f;
	fixDef_apoyoarma.restitution = 0.1f;
	fixDef_apoyoarma.friction = 0.3f;
	fix_apoyoarma = bdy_apoyoarma->CreateFixture(&fixDef_apoyoarma);

	//Inicializa la física del arma
	b2PolygonShape shp_arma;
	shp_arma.SetAsBox(0.8f, 0.4f);

	fixDef_arma.shape = &shp_arma;
	fixDef_arma.density = 1.f;
	fixDef_arma.restitution = 0.1f;
	fixDef_arma.friction = 0.3f;
	fix_arma = bdy_arma->CreateFixture(&fixDef_arma);
}

void Arma::InitImageArma(int _tipo)
{
	/*
		Inicializa la textura y el sprite correspondiente al arma y el apoyo del arma de acuerdo al parámetro
		que se configura desde Game (puede cambiar la textura del arma)
	*/
	//apoyo del arma
	txt_apoyoarma = new Texture;
	if (!txt_apoyoarma->loadFromFile("assets/apoyoarma" + to_string(_tipo) + ".png"))
	{
		cout << "no carga la imagen del apoyoarma";
	}
	spr_apoyoarma = new Sprite;
	spr_apoyoarma->setTexture(*txt_apoyoarma);

	fig_apoyoarma = new RectangleShape;

	//arma
	txt_arma = new Texture;
	if (!txt_arma->loadFromFile("assets/arma" + to_string(_tipo) + ".png"))
	{
		cout << "no carga la imagen del arma";
	}
	spr_arma = new Sprite;
	spr_arma->setTexture(*txt_arma);

	fig_arma = new RectangleShape;
}

void Arma::InitActorSpriteArma()
{
	//Inicializa el objeto ActorSprite del arma y el apoyo del arma
	actorSprite_apoyoarma = new ActorSprite(bdy_apoyoarma, spr_apoyoarma);
	actorSprite_arma = new ActorSprite(bdy_arma, spr_arma);
}

void Arma::UpdateArma(Vector2f _positionMouseCoordinates)
{
	/*
		Mantiene la posición origen del del arma, pero cambia el ángulo
		Nuevo ángulo del arma = arcotangente (Y mouse - Y arma)/(X mouse - X arma)
	*/
	bdy_arma->SetTransform(bdy_arma->GetPosition(), atan2f(_positionMouseCoordinates.y - bdy_arma->GetPosition().y, _positionMouseCoordinates.x - bdy_arma->GetPosition().x));
}

void Arma::DrawArma(RenderWindow* _ventana)
{
	//Dibuja el arma y el apoyo del arma en la ventana
	actorSprite_apoyoarma->DrawActorSprite(_ventana);
	actorSprite_arma->DrawActorSprite(_ventana);
}

Vector2f Arma::GetPositionArma()
{
	//Define un vector positionArma que guarda la posición en el mundo del arma movil 
	Vector2f positionArma = Vector2f(bdy_arma->GetPosition().x + 0.5f, bdy_arma->GetPosition().y - 2.f);
	return positionArma;
}
