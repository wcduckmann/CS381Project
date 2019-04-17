/*
 * Command.cpp
 *
 *  Created on: Apr 6, 2019
 *      Author: wduckhorn
 */

#include "Command.h"
#include "Utils.h"

Command::Command(){
	entity = NULL;
}

Command::Command(Entity381 * ent){
	entity = ent;
}

Command::~Command(){

}

void Command::init(){

}

void Command::tick(float dt){

}

bool Command::done(){
	return false;
}
MoveTo::MoveTo(Entity381 * ent, Ogre::Vector3 location) : Command(ent){
	isFinished = false;
	targetLocation = location;
	std::cout << "MoveTo object created" << std::endl;
}

MoveTo::~MoveTo(){

}

void MoveTo::init(){

}

void MoveTo::tick(float dt){
	Ogre::Real distance = targetLocation.distance(entity->position);

	if(distance < MOVE_DISTANCE_THRESHOLD){
		std::cout << "Ship is at target location" << std::endl;
		entity->desiredSpeed = 0;
		entity->velocity = Ogre::Vector3::ZERO;
		isFinished = true;
		return;
	}

	Ogre::Vector3 difference = targetLocation - entity->position;
	Ogre::Radian angle = Ogre::Math::ATan2(difference.z, difference.x);
	float heading = angle.valueDegrees();

	heading = FixAngle(heading);

	entity->desiredHeading = heading;

	entity->desiredSpeed = entity->maxSpeed;
}

bool MoveTo::done(){
	return isFinished;
}

Intercept::Intercept(Entity381 * ent, Entity381 * boat) : Command(ent) {
	isFinished = false;
	targetBoat = boat;
	targetLocation = targetBoat->position;
}

Intercept::~Intercept(){

}

void Intercept::init(){

}

void Intercept::tick(float dt){

	Ogre::Real distance = targetBoat->position.distance(entity->position);

	if(distance < MOVE_DISTANCE_THRESHOLD){
		std::cout << "Ship intercepted" << std::endl;
		entity->desiredSpeed = 0;
		entity->velocity = Ogre::Vector3::ZERO;
		isFinished = true;
		return;
	}


	Ogre::Vector3 relativeVelocity = targetBoat->velocity - entity->velocity;
	Ogre::Vector3 targetDiff = targetBoat->position - targetLocation;
	Ogre::Vector3 nextPos = targetBoat->position + targetDiff;
	Ogre::Vector3 interceptLocation = nextPos - entity->position;
	Ogre::Vector3 timeNeeded = interceptLocation / relativeVelocity;

	targetLocation = targetBoat->position + (targetBoat->velocity * timeNeeded);

	Ogre::Radian angle = Ogre::Math::ATan2(targetLocation.z, targetLocation.x);
	float heading = angle.valueDegrees();

	heading = FixAngle(heading);

	entity->desiredHeading = heading;

	entity->desiredSpeed = entity->maxSpeed;

	targetLocation = targetBoat->position;
}

bool Intercept::done(){
	return isFinished;
}
