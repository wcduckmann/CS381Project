/*
 * FlyingEntity381.h
 *
 *  Created on: Mar 7, 2018
 *      Author: sushil
 */

#ifndef FLYINGENTITY381_H_
#define FLYINGENTITY381_H_

#include <Entity381.h>
#include <OgreVector3.h>
#include <Engine.h>

class FlyingEntity381: public Entity381 {
public:
	FlyingEntity381(Engine *engine, Ogre::Vector3 pos, int ident);
	virtual ~FlyingEntity381();
	float minAltitude, maxAltitude;
	float altitude, desiredAltitude, climbRate;
};



class Banshee: public FlyingEntity381 {
public:
	Banshee(Engine *engine, Ogre::Vector3 pos, int ident);
	virtual ~Banshee();
};



#endif /* FLYINGENTITY381_H_ */
