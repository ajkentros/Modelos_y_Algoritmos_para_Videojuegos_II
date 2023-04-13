#pragma once
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
	
	//Identidad del Ragdoll
	b2Body* bdy_ragdoll[6];				//body ragdoll
	b2BodyDef bdyDef_ragdoll[6];		//definiciones del ragdoll
	b2Fixture* fix_ragdoll[6];			//fixture del ragdoll
	b2FixtureDef fixDef_ragdoll[6];		//definiciones del fixture del ragdoll
	Actor* actor_ragdoll[6];			//instancia objeto Actor para el ragdoll
	RectangleShape* fig_ragdoll[6];		//instancia objeto rectángulo para la figura del ragdoll

	//Instancia resortes para cad parte del ragdoll
	b2DistanceJoint* jnt_ragdoll[5];		//constucción del resorte 
	b2DistanceJointDef jntDef_ragdoll[5];	//definiciones de cada resorte

public:
	//constructor de radgoll
	Ragdoll(Vector2f posicion, b2World& mundo1);

	//dibuja radgoll
	void DrawRagdoll(RenderWindow& ventana);
	
};

