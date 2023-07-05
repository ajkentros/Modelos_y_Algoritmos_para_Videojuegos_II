#include "Suelo.h"

Suelo::Suelo(b2World* &_mundo, b2Vec2 _posicion)
{
	//Inicializa el Suelo tomando los datos de la posición del suelo y el mundo que recibe de la clase Game
	bdyDef_suelo.type = b2_staticBody;
	bdyDef_suelo.position = b2Vec2(_posicion);
	bdy_suelo = _mundo->CreateBody(&bdyDef_suelo);

	//Llama a las funciones: inicia la física, la imagen del suelo y el sprite del suelo para imprimirlo en el mundo de box2d
	InitPhysicsSuelo();
	InitImageSuelo();
	InitActorSpriteSuelo();
}

Suelo::~Suelo()
{
}

void Suelo::InitPhysicsSuelo()
{
	//Inicializa la física del suelo
	b2PolygonShape shape_suelo;										//polígono contenedor del suelo
	shape_suelo.SetAsBox(10.f, 0.8f);

	fixDef_suelo.shape = &shape_suelo;
	fixDef_suelo.restitution = 0.f;
	fixDef_suelo.friction = 0.3f;
	fixDef_suelo.density = 1.f;
	fix_suelo = bdy_suelo->CreateFixture(&fixDef_suelo);
}

void Suelo::InitImageSuelo()
{
	//Inicializa la textura y el Sprite del suelo
	txt_suelo = new Texture;
	txt_suelo->loadFromFile("assets/suelo.jpg");
	spr_suelo = new Sprite;
	spr_suelo->setTexture(*txt_suelo);

	fig_suelo = new RectangleShape;
}

void Suelo::InitActorSpriteSuelo()
{
	//Inicializa el ActorSprite del suelo en el mundo de box2D
	actorSprite_suelo = new ActorSprite(bdy_suelo, spr_suelo);
}

void Suelo::DrawSuelo(RenderWindow* _ventana)
{
	//Dibuja el suelo (no cambia con las escenas)
	actorSprite_suelo->DrawActorSprite(_ventana);
}

FloatRect Suelo::GetBoxSuelo()
{
	FloatRect box_suelo = spr_suelo->getGlobalBounds();
	return box_suelo;
}
