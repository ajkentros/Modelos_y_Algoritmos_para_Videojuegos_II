#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SFMLRenderer.h"
#include <list>
#include "Actor.h"

using namespace sf;
using namespace std;

class Ragdoll
{
private:
	
	//identidad del Ragdoll
	int color_ragdoll;							//variable que define el color de cada parte del ragdoll

	b2Body* bdy_ragdoll[6];						//puntero arreglo objeto body del ragdoll
	b2BodyDef bdyDef_ragdoll[6];				//arreglo objeto body def del ragdoll
	b2Fixture* fix_ragdoll[6];					//puntero arreglo Fixture del ragdoll
	b2FixtureDef fixDef_ragdoll[6];				//arreglo objeto Fixture def del ragdoll
	RectangleShape* fig_ragdoll[6];				//puntero arreglo objeto RectangleSahpe del ragdoll
	Actor* actor_ragdoll[6];					//puntero arreglo ovjeto Actor del ragdoll
	
	//resortes de cada parte del ragdoll
	b2DistanceJoint* jnt_ragdoll[5];			//puntero arreglo objeto resorte del ragdoll
	b2DistanceJointDef jntDef_ragdoll[5];		//arreglo objeto def resorte del ragdoll


public:
	//Constructor y destructor del ragdoll
	Ragdoll(Vector2f _posicion, b2World& _mundo1);
	~Ragdoll();

	//Dibuja el ragdoll
	void DrawRagdoll(RenderWindow& _ventana1);
	
	//Aplica fuerza al ragdoll
	void ApplyForceRagdoll(Vector2f _position);

	//Define colores a cada parte del ragdoll
	void ColorsRagdoll(RectangleShape* _fig_ragdoll, int _color_ragdoll);

	//Conversor de radianes a grados
	float rad2deg(float _radians);

	//Retorna el global bound del ragdoll
	FloatRect BoxRagdoll(int i);

	//Retorna la posición del ragdoll en un vector
	Vector2f GetPositionRagdoll(int i);
};

