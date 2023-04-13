#include "Ragdoll.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

Ragdoll::Ragdoll(Vector2f posicion, b2World& mundo1)
{
	//define posición de 0= cabeza, 1=torzo, 2=brazo izquierdo, 30brazo derecho, 4=pierna izquierda, 5=pierna derecha
	bdyDef_ragdoll[0].position = b2Vec2(posicion.x, posicion.y);					//cabeza
	bdyDef_ragdoll[1].position = b2Vec2(posicion.x, posicion.y + 0.55f);			//torzo
	bdyDef_ragdoll[2].position = b2Vec2(posicion.x + 0.32f, posicion.y + 0.4f);		//brazo derecho
	bdyDef_ragdoll[3].position = b2Vec2(posicion.x - 0.32f, posicion.y + 0.4f);		//brazo izquierdo
	bdyDef_ragdoll[4].position = b2Vec2(posicion.x + 0.09f, posicion.y + 1.4f);		//pierna derecha
	bdyDef_ragdoll[5].position = b2Vec2(posicion.x - 0.09f, posicion.y + 1.4f);		//pierna izquierda

	//define a las partes de radgoll como bodys dinámicos
	for (int i = 0; i < 6; i++)
	{
		bdyDef_ragdoll[i].type = b2_dynamicBody;
		bdy_ragdoll[i] = mundo1.CreateBody(&bdyDef_ragdoll[i]);
	}

	//instancia el contenedor shape de las partes del radgoll
	b2PolygonShape shape_ragdoll[6];		//contenedor shape de las partes del ragdoll

	//define las dimensiones de cada parte del radgoll
	shape_ragdoll[0].SetAsBox(0.1f, 0.2f);
	shape_ragdoll[1].SetAsBox(0.2f, 0.4f);
	shape_ragdoll[2].SetAsBox(0.07f, 0.3f);
	shape_ragdoll[3].SetAsBox(0.07f, 0.3f);
	shape_ragdoll[4].SetAsBox(0.07f, 0.4f);
	shape_ragdoll[5].SetAsBox(0.07f, 0.4f);

	//define propiedades de radgoll (densidad, fricción, restitución) y construye cada parte
	for (int i = 0; i < 6; i++)
	{
		fixDef_ragdoll[i].shape = &shape_ragdoll[i];
		fixDef_ragdoll[i].density = 1.1f;
		fixDef_ragdoll[i].friction = 0.3f;
		fixDef_ragdoll[i].restitution = 0.1f;

		fix_ragdoll[i] = bdy_ragdoll[i]->CreateFixture(&fixDef_ragdoll[i]);
	}

	/*
	define 5 resortes entre partes del cuerpo del radgoll
		0 A 1, 1 a 2, 1 a 3, 1 a 4, 1 a 5
	*/
	jntDef_ragdoll[0].Initialize(bdy_ragdoll[0], bdy_ragdoll[1], b2Vec2(bdy_ragdoll[0]->GetPosition().x, bdy_ragdoll[0]->GetPosition().y + 0.08f),
		b2Vec2(bdy_ragdoll[1]->GetPosition().x, bdy_ragdoll[1]->GetPosition().y - 0.38f));

	jntDef_ragdoll[1].Initialize(bdy_ragdoll[1], bdy_ragdoll[2], b2Vec2(bdy_ragdoll[1]->GetPosition().x + 0.09f, bdy_ragdoll[1]->GetPosition().y - 0.38f),
		b2Vec2(bdy_ragdoll[2]->GetPosition().x, bdy_ragdoll[2]->GetPosition().y - 0.3f));

	jntDef_ragdoll[2].Initialize(bdy_ragdoll[1], bdy_ragdoll[3], b2Vec2(bdy_ragdoll[1]->GetPosition().x - 0.09f, bdy_ragdoll[1]->GetPosition().y - 0.38f),
		b2Vec2(bdy_ragdoll[3]->GetPosition().x, bdy_ragdoll[3]->GetPosition().y - 0.3f));

	jntDef_ragdoll[3].Initialize(bdy_ragdoll[1], bdy_ragdoll[4], b2Vec2(bdy_ragdoll[1]->GetPosition().x + 0.09f, bdy_ragdoll[1]->GetPosition().y + 0.38f),
		b2Vec2(bdy_ragdoll[4]->GetPosition().x, bdy_ragdoll[4]->GetPosition().y - 0.38f));

	jntDef_ragdoll[4].Initialize(bdy_ragdoll[1], bdy_ragdoll[5], b2Vec2(bdy_ragdoll[1]->GetPosition().x - 0.09f, bdy_ragdoll[1]->GetPosition().y + 0.38f),
		b2Vec2(bdy_ragdoll[5]->GetPosition().x, bdy_ragdoll[5]->GetPosition().y - 0.38f));

	//define propiedades de cada resorte
	for (int i = 0; i < 5; i++)
	{
		jntDef_ragdoll[i].damping = 0.3f;
		jntDef_ragdoll[i].stiffness = 2.0f;
		jntDef_ragdoll[i].collideConnected = true;
		jntDef_ragdoll[i].length = 0.025f;

		jnt_ragdoll[i] = (b2DistanceJoint*)mundo1.CreateJoint(&jntDef_ragdoll[i]);
	}

	//instancia las figuras de los resortes del tipo RectangleSahpe
	for (int i = 0; i < 6; i++)
	{
		fig_ragdoll[i] = new RectangleShape;
	}

	//define el color de cada parte del radgoll
	fig_ragdoll[0]->setFillColor(Color::Red);
	fig_ragdoll[1]->setFillColor(Color::Green);
	fig_ragdoll[2]->setFillColor(Color::Blue);
	fig_ragdoll[3]->setFillColor(Color::Blue);
	fig_ragdoll[4]->setFillColor(Color::Yellow);
	fig_ragdoll[5]->setFillColor(Color::Yellow);

	//instancia los objetos del tipo actor
	for (int i = 0; i < 6; i++)
	{
		actor_ragdoll[i] = new Actor(bdy_ragdoll[i], fig_ragdoll[i]);
	}
}

//dibuja radgoll
void Ragdoll::DrawRagdoll(RenderWindow& ventana)
{
	//dibuja todas las partes del cuerpo del ragdoll
	for (int i = 0; i < 6; i++) {
		actor_ragdoll[i]->DrawActor(&ventana);
	}
}


