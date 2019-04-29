/*
 * FlyingEntity381.cpp
 *
 *  Created on: Mar 7, 2018
 *      Author: sushil
 */

#include <Physics3D.h>
#include "FlyingEntity381.h"

FlyingEntity381::FlyingEntity381(Engine *engine, Ogre::Vector3 pos, int ident):
	Entity381(engine, pos, ident) {
	// TODO Auto-generated constructor stub
	minAltitude = 0;
	maxAltitude = 1000;
	altitude = 0;
	desiredAltitude = 0;
	climbRate = 1;
	aspects.clear();
	Physics3D * phx = new Physics3D(this);
	Renderable *renderable = new Renderable(this);
	aspects.push_back((Aspect *) phx);
	aspects.push_back((Aspect *) renderable);
}

FlyingEntity381::~FlyingEntity381() {
	// TODO Auto-generated destructor stub
}


Banshee::Banshee(Engine *engine, Ogre::Vector3 pos, int ident):
		FlyingEntity381(engine, pos, ident) {
	// TODO Auto-generated constructor stub
	meshfilename = "banshee.mesh";
	entityType = BansheeType;

	acceleration = 10.0f;
	turnRate = 10.0f;

	minSpeed = 0;
	maxSpeed = 100;

	climbRate = 20;
	altitude = 20;
	desiredAltitude = 20;
	this->position.y = 20;
	maxAltitude = 1000;
	minAltitude = 10;
}

Banshee::~Banshee() {
	// TODO Auto-generated destructor stub
}
