#include "Cajas.h"

Cajas::Cajas(b2World*& _mundo, Vector2f _offsetCajas, int _tipo, int _cantidadCajas)
{
	//Inicializa caja fija
	/*
		cantidad de cajas: parámetro que se define en Game
		por cada caja (3) en la escena (podría cambiarse en Game, según la dificultad) =>
			incializa las cajas fijas
			incializa las cajas móviles
			controla el desplazamiento de las cajas según el nivel del juego (la dificultad aparece según el valor de gameLevel)
		Inicia las physics de las cajas
		Inicia las imágenes de las cajas según el nivel del juego
		Inicia los sprite de las cajas

	 */

	cantidadCajas = _cantidadCajas;
	for (int i = 0; i < cantidadCajas; i++)
	{
		//Inicializa caja fija
		bdyDef_cajaFija[i].type = b2_staticBody;
		bdyDef_cajaFija[i].position = b2Vec2(coordenadaX_cajaFija + _offsetCajas.x, coordenadaY_cajaFija + _offsetCajas.y);
		bdy_cajaFija[i] = _mundo->CreateBody(&bdyDef_cajaFija[i]);

		//Inicializa caja movil
		float coordenadaX_cajaMovil = coordenadaX_cajaFija - 0.3f;
		float coordenadaY_cajaMovil = coordenadaY_cajaFija - 0.45f;
		bdyDef_cajaMovil[i].type = b2_dynamicBody;
		bdyDef_cajaMovil[i].position = b2Vec2(coordenadaX_cajaMovil + _offsetCajas.x, coordenadaY_cajaMovil + _offsetCajas.y);
		bdy_cajaMovil[i] = _mundo->CreateBody(&bdyDef_cajaMovil[i]);

		_offsetCajas.x += 2.5f;
		_offsetCajas.y -= 1.21f + ((_tipo - 1) * 1.005f);
	}

	InitPhysicsCajas(_mundo);
	InitImageCajas(_tipo);
	InitActorSpriteCajas();
}

Cajas::~Cajas()
{
}

void Cajas::InitPhysicsCajas(b2World*& _mundo)
{
	/*
		por cada caja =>
			se define el body, fixture de las cajas fijas en el mundo 
			se define el body, fixture de las cajas móviles en el mundo
	*/
	for (int i = 0; i < cantidadCajas; i++)
	{
		//Inicializa la física de las cajas fijas
		b2PolygonShape shape_cajaFija;
		shape_cajaFija.SetAsBox(0.5f, 0.5f);

		fixDef_cajaFija[i].shape = &shape_cajaFija;
		fixDef_cajaFija[i].density = 1.f;
		fixDef_cajaFija[i].restitution = 0.0f;
		fixDef_cajaFija[i].friction = 0.3f;

		fix_cajaFija[i] = bdy_cajaFija[i]->CreateFixture(&fixDef_cajaFija[i]);

		//Inicializa la física de las cajas móviles
		b2PolygonShape shape_cajaMovil;
		shape_cajaMovil.SetAsBox(0.4f, 0.4f);

		fixDef_cajaMovil[i].shape = &shape_cajaMovil;
		fixDef_cajaMovil[i].density = 1.f;
		fixDef_cajaMovil[i].restitution = 0.0f;
		fixDef_cajaMovil[i].friction = 0.3f;

		fix_cajaMovil[i] = bdy_cajaMovil[i]->CreateFixture(&fixDef_cajaMovil[i]);
	}

	//crea un resorte entre la caja móvil 3 y la caja fija 2 (no se hace con la la cF0 o cF2 porque no funciona bien el resorte)
	jntDef_cajaMovil.Initialize(bdy_cajaFija[2], bdy_cajaMovil[2],
		b2Vec2(bdy_cajaFija[2]->GetPosition().x, bdy_cajaFija[2]->GetPosition().y + 0.5f),
		b2Vec2(bdy_cajaFija[2]->GetPosition().x, bdy_cajaMovil[2]->GetPosition().y + 5.4f));

	jntDef_cajaMovil.damping = 0.1f;
	jntDef_cajaMovil.stiffness = 0.1f;
	jntDef_cajaMovil.length = 5.f;
	jntDef_cajaMovil.collideConnected = true;
	jnt_cajaMovil = (b2DistanceJoint*)_mundo->CreateJoint(&jntDef_cajaMovil);
}

void Cajas::InitImageCajas(int _tipo)
{
	/*
		por cada caja =>
			se crea la textura según el tipo (parámetro definido en Game)
			se crea el sprite según el tipo (parámetro definido en Game)
	*/
	for (int i = 0; i < cantidadCajas; i++)
	{
		//cajas fijas
		txt_cajaFija[i] = new Texture;
		if (!txt_cajaFija[i]->loadFromFile("assets/cajaFija0.jpg"))
		{
			cout << "no carga la imagen de la caja fija";
		}
		spr_cajaFija[i] = new Sprite;
		spr_cajaFija[i]->setTexture(*txt_cajaFija[i]);

		//caja móvil
		txt_cajaMovil[i] = new Texture;
		if (!txt_cajaMovil[i]->loadFromFile("assets/cajaMovil" + to_string(_tipo) + ".jpg"))
		{
			cout << "no carga la imagen de la caja móvil";
		}
		spr_cajaMovil[i] = new Sprite;
		spr_cajaMovil[i]->setTexture(*txt_cajaMovil[i]);

	}

	for (int i = 0; i < 3; i++)
	{
		fig_cajaFija[i] = new RectangleShape;		//obstáculo caja fija
		fig_cajaMovil[i] = new RectangleShape;		//obstáculo caja móvil
	}
}

void Cajas::InitActorSpriteCajas()
{
	/*
		por cada caja =>
			se crean los Actores Sprite de cada caja fija y móvil
	*/
	for (int i = 0; i < cantidadCajas; i++) {
		actorSprite_cajaFija[i] = new ActorSprite(bdy_cajaFija[i], spr_cajaFija[i]);
		actorSprite_cajaMovil[i] = new ActorSprite(bdy_cajaMovil[i], spr_cajaMovil[i]);
	}
}

void Cajas::DrawCajas(RenderWindow* _ventana)
{
	/*
		por cada caja =>
			se dibujan las cajas en el escenario
	*/

	for (int i = 0; i < cantidadCajas; i++)
	{
		actorSprite_cajaFija[i]->DrawActorSprite(_ventana);
		actorSprite_cajaMovil[i]->DrawActorSprite(_ventana);
	}

}

FloatRect Cajas::GetBoxCajaMovil(int _i)
{
	//según la caja móvil (recibe un parámetro) se retorna el global bound de la caja móvil
	FloatRect boxCaja = spr_cajaMovil[_i]->getGlobalBounds();
	return boxCaja;
}

FloatRect Cajas::GetBoxCajaFija(int _i)
{
	//según la caja fija (recibe un parámetro) se retorna el global bound de la caja fija
	FloatRect boxCaja = spr_cajaFija[_i]->getGlobalBounds();
	return boxCaja;
}
