
#include "Ragdoll.h"
#include <box2d/box2d.h>

using namespace std;

Ragdoll::Ragdoll(Vector2f _posicion, b2World& _mundo1) {
	/*
		Inicializa el ragdoll teniendo en cuenta
		0= cabeza, 
		1=torzo, 
		2=brazo izquierdo, 
		3=brazo derecho, 
		4=pierna izquierda, 
		5=pierna derecha
		posicion inicial de la cabeza: x= 50 y = 95
	*/
	bdyDef_ragdoll[0].position = b2Vec2(_posicion.x, _posicion.y);						//cabeza
	bdyDef_ragdoll[1].position = b2Vec2(_posicion.x, _posicion.y + 0.55f);				//torso
	bdyDef_ragdoll[2].position = b2Vec2(_posicion.x + 0.32f, _posicion.y + 0.4f);		//brazo derecho
	bdyDef_ragdoll[3].position = b2Vec2(_posicion.x - 0.32f, _posicion.y + 0.4f);		//brazo izquierdi
	bdyDef_ragdoll[4].position = b2Vec2(_posicion.x + 0.09f, _posicion.y + 1.4f);		//pierna derecha
	bdyDef_ragdoll[5].position = b2Vec2(_posicion.x - 0.09f, _posicion.y + 1.4f);		//pierna izquierda

	//Define a las partes de radgoll como bodys dinámicos
	for (int i = 0; i < 6; i++) 
	{
		bdyDef_ragdoll[i].type = b2_dynamicBody;
		bdy_ragdoll[i] = _mundo1.CreateBody(&bdyDef_ragdoll[i]);
	}
	
	//Instancia el contenedor shape de las partes del radgoll
	b2PolygonShape shape_ragdoll[6];

	//Dimension partes del ragdoll
	shape_ragdoll[0].SetAsBox(0.1f, 0.1f);		//cabeza
	shape_ragdoll[1].SetAsBox(0.2f, 0.4f);		//torso
	shape_ragdoll[2].SetAsBox(0.07f, 0.3f);		//brazo derecho
	shape_ragdoll[3].SetAsBox(0.07f, 0.3f);		//brazo izquierdo
	shape_ragdoll[4].SetAsBox(0.07f, 0.4f);		//pierna derecho
	shape_ragdoll[5].SetAsBox(0.07f, 0.4f);		//pierna izqquierdo

	//Define propiedades de radgoll (densidad, fricción, restitución) y construye cada parte
	for (int i = 0; i < 6; i++) 
	{
		fixDef_ragdoll[i].shape = &shape_ragdoll[i];
		fixDef_ragdoll[i].restitution = 0.3f;
		fixDef_ragdoll[i].density = 1.f;
		fixDef_ragdoll[i].friction = 0.3f;
		fix_ragdoll[i] = bdy_ragdoll[i]->CreateFixture(&fixDef_ragdoll[i]);
	}

	/*
		Define 5 resortes entre partes del cuerpo del radgoll
		0 A 1, 1 a 2, 1 a 3, 1 a 4, 1 a 5
	*/
	//cabeza - torso
	jntDef_ragdoll[0].Initialize(bdy_ragdoll[0], bdy_ragdoll[1], b2Vec2(bdy_ragdoll[0]->GetPosition().x, bdy_ragdoll[0]->GetPosition().y + 0.08f),
		b2Vec2(bdy_ragdoll[1]->GetPosition().x, bdy_ragdoll[1]->GetPosition().y - 0.38f));
	////brazo derecho - torso
	jntDef_ragdoll[1].Initialize(bdy_ragdoll[1], bdy_ragdoll[2], b2Vec2(bdy_ragdoll[1]->GetPosition().x + 0.09f, bdy_ragdoll[1]->GetPosition().y - 0.38f), 
		b2Vec2(bdy_ragdoll[2]->GetPosition().x, bdy_ragdoll[2]->GetPosition().y - 0.3f));
	//brazo izquierdo - torso
	jntDef_ragdoll[2].Initialize(bdy_ragdoll[1], bdy_ragdoll[3], b2Vec2(bdy_ragdoll[1]->GetPosition().x - 0.09f, bdy_ragdoll[1]->GetPosition().y - 0.38f), 
		b2Vec2(bdy_ragdoll[3]->GetPosition().x, bdy_ragdoll[3]->GetPosition().y - 0.3f));
	//pierna derecha - torso
	jntDef_ragdoll[3].Initialize(bdy_ragdoll[1], bdy_ragdoll[4], b2Vec2(bdy_ragdoll[1]->GetPosition().x + 0.09f, bdy_ragdoll[1]->GetPosition().y + 0.38f), 
		b2Vec2(bdy_ragdoll[4]->GetPosition().x, bdy_ragdoll[4]->GetPosition().y - 0.38f));
	//pierna izquierda - torso
	jntDef_ragdoll[4].Initialize(bdy_ragdoll[1], bdy_ragdoll[5], b2Vec2(bdy_ragdoll[1]->GetPosition().x - 0.09f, bdy_ragdoll[1]->GetPosition().y + 0.38f), 
		b2Vec2(bdy_ragdoll[5]->GetPosition().x, bdy_ragdoll[5]->GetPosition().y - 0.38f));

	//Define propiedades de cada resorte
	for (int i = 0; i < 5; i++) {
		jntDef_ragdoll[i].damping = 0.3f;
		jntDef_ragdoll[i].stiffness = 0.9f;
		jntDef_ragdoll[i].length = 0.035f;
		jntDef_ragdoll[i].collideConnected = true;
		
		jnt_ragdoll[i] = (b2DistanceJoint*)_mundo1.CreateJoint(&jntDef_ragdoll[i]);
	}

	//Instancia las figuras de los resortes del tipo RectangleSahpe
	for (int i = 0; i < 6; i++)
	{
		fig_ragdoll[i] = new RectangleShape;
	}

	
	//Instancia los colores de cada parte del ragdoll
	//color de la cabeza
	color_ragdoll = rand() % 7 + 1;
	ColorsRagdoll(fig_ragdoll[0], color_ragdoll);
	//color del torzo
	color_ragdoll = rand() % 7 + 1;
	ColorsRagdoll(fig_ragdoll[1], color_ragdoll);
	//color de los brazos
	ColorsRagdoll(fig_ragdoll[2], color_ragdoll);
	ColorsRagdoll(fig_ragdoll[3], color_ragdoll);
	//color de las piernas
	color_ragdoll = rand() % 7 + 1;
	ColorsRagdoll(fig_ragdoll[4], color_ragdoll);
	ColorsRagdoll(fig_ragdoll[5], color_ragdoll);


	//Instancia los objetos del tipo actor
	for (int i = 0; i < 6; i++) 
	{
		actor_ragdoll[i] = new Actor(bdy_ragdoll[i], fig_ragdoll[i]);
	}
}

Ragdoll::~Ragdoll()
{
}

void Ragdoll::DrawRagdoll(RenderWindow& _ventana1) {
	//Dibuja todas las partes del cuerpo del ragdoll
	for (int i = 0; i < 6; i++) {
		actor_ragdoll[i]->DrawActor(&_ventana1);
	}
}

void Ragdoll::ApplyForceRagdoll(Vector2f _posicion) {
	//Aplica una fuerza al centro del torzo del ragdoll según la posicion del mouse
	bdy_ragdoll[1]->ApplyForceToCenter(b2Vec2(_posicion.x * 80, _posicion.y * 80), false);
}

void Ragdoll::ColorsRagdoll(RectangleShape* figRag, int _color_ragdoll) {
	//Toma una parte del cuerpo numerada y define el color de acuerdo al número que se pasa por parametro
	if (_color_ragdoll == 1)
	{
		figRag->setFillColor(Color::Yellow);
	}
	else if (_color_ragdoll == 2)
	{
		figRag->setFillColor(Color::Red);
	}
	else if (_color_ragdoll == 3)
	{
		figRag->setFillColor(Color::Magenta);
	}
	else if (_color_ragdoll == 4)
	{
		figRag->setFillColor(Color::Green);
	}
	else if (_color_ragdoll == 5)
	{
		figRag->setFillColor(Color::White);
	}
	else if (_color_ragdoll == 6)
	{
		figRag->setFillColor(Color::Cyan);
	}
	else if (_color_ragdoll == 7)
	{
		figRag->setFillColor(Color::Blue);
	}
}

float Ragdoll::rad2deg(float radianes) {
	//Convierte radianes a grados
	return radianes * 180 / 3.14f;
}

FloatRect Ragdoll::BoxRagdoll(int i)
{
	//Retorna el global bound del ragdoll (torzo = 1)
	FloatRect boxRagdoll = fig_ragdoll[i]->getGlobalBounds();
	return boxRagdoll;
}

Vector2f Ragdoll::GetPositionRagdoll(int i)
{
	//Retorna la posición del ragdoll (torzo = 1)
	Vector2f positionRagdoll = Vector2f (fig_ragdoll[i]->getPosition());
	return positionRagdoll;
}