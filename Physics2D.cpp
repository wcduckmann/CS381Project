/*
 * Physics2D.cpp
 *
 *  Created on: Mar 1, 2018
 *      Author: sushil
 */


#include <Physics2D.h>
#include <Entity381.h>
#include <Utils.h>

Physics2D::Physics2D(Entity381* ent):Aspect(ent){

}

Physics2D::~Physics2D(){

}


void Physics2D::Tick(float dt){
	//first, get new speed from desired speed
	if(entity->desiredSpeed > entity->speed){
		entity->speed += entity->acceleration * dt;
	} else if (entity->desiredSpeed < entity->speed){
		entity->speed -= entity->acceleration * dt;
	}
	entity->speed = Clamp(entity->minSpeed, entity->maxSpeed, entity->speed);

	//When I try to go from a heading of 350 to a heading of 10,
	//I should turn to right/starboard not keep decreasing heading till I get to 10 because it is 20 degrees from -10 (350) to +10 by turning to port/right and
	//340 degrees from 350 (-10) to 10 by turning left/port

	//now, get new heading from desired heading
	if(entity->desiredHeading > entity->heading){
		if(entity->desiredHeading - entity->heading > 180)
			entity->heading -= entity->turnRate * dt;
		else
			entity->heading += entity->turnRate * dt;
	} else if (entity->desiredHeading < entity->heading){
		if(entity->desiredHeading - entity->heading < -180)
			entity->heading += entity->turnRate * dt;
		else
			entity->heading -= entity->turnRate * dt;;
	}
	entity->heading = FixAngle(entity->heading);

	//Now do the trig
	entity->velocity.y = 0.0f; // just to be safe, we do not want ships in the air.
	entity->velocity.x = Ogre::Math::Cos(Ogre::Degree(entity->heading)) * entity->speed; //adjacent/hyp
	entity->velocity.z = Ogre::Math::Sin(Ogre::Degree(entity->heading)) * entity->speed; //opposite/hyp

	//This does not change!
	entity->position = entity->position + entity->velocity * dt;
}
