/*
 * Command.h
 *
 *  Created on: Apr 5, 2019
 *      Author: wduckhorn
 */

#ifndef INC_COMMAND_H_
#define INC_COMMAND_H_


#include "Entity381.h"
#include "InputMgr.h"
#include "Types381.h"

class Command {

public:
	Command();
	Command(Entity381 * ent);
	virtual ~Command();

	virtual void init();
	virtual void tick(float dt);
	virtual bool done();

	Entity381 * entity;
};

class MoveTo: public Command {

public:
	MoveTo(Entity381 * ent, Ogre::Vector3 location);
	~MoveTo();

	void init();
	void tick(float dt);
	bool done();

	Ogre::Vector3 targetLocation;
	float MOVE_DISTANCE_THRESHOLD = 150;

	bool isFinished;

};



class Intercept: public Command {

public:
	Intercept(Entity381 * ent, Entity381 * boat);
	~Intercept();

	void init();
	void tick(float dt);
	bool done();

	Ogre::Vector3 targetLocation;
	float MOVE_DISTANCE_THRESHOLD = 100;

	bool isFinished;
	Entity381* targetBoat;
};


#endif /* INC_COMMAND_H_ */
