
/*
 * Entity381.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */

#include <GfxMgr.h>

#include<Entity381.h>
#include<Physics2D.h>
#include"UnitAI.h"

std::string IntToString(int x){
	char tmp[10000];
	sprintf(tmp, "%i", x);
	return std::string(tmp);
}

Entity381::Entity381(Engine *engine, Ogre::Vector3 pos, int ident){

	this->engine = engine;

	entityType = None;
	meshfilename = std::string();
	position = pos;
	velocity = Ogre::Vector3(0, 0, 0);
	identity = ident;
	isSelected = false;

	health = 1;
	size = 1;


	name = "Entity381";//meshfname + IntToString(identity);
/*
	ogreEntity = engine->gfxMgr->mSceneMgr->createEntity(meshfilename);
	sceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(pos);
	sceneNode->attachObject(ogreEntity);*/
	sceneNode = 0;
	ogreEntity = 0;

	Physics2D* phx = new Physics2D(this);
	aspects.push_back((Aspect*) phx);
	Renderable * renderable = new Renderable(this);
	aspects.push_back((Aspect*)renderable);
	UnitAI * ai = new UnitAI(this);
	aspects.push_back(ai);

	this->acceleration = 0;
	this->desiredHeading = this->heading = 0;
	this->turnRate = 0;
	this->desiredSpeed = this->speed = 0;
	this->minSpeed = this->maxSpeed = 0;

	this->playSound = false;

	this->soundFile = "Boat-Sound.wav";

	this->auioId = 0;


}

Entity381::~Entity381(){

}

void Entity381::Init(){

	name = meshfilename + IntToString(identity);
	ogreEntity = engine->gfxMgr->mSceneMgr->createEntity(meshfilename);
	sceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(position);
	sceneNode->attachObject(ogreEntity);
}

void Entity381::Tick(float dt){
	for(unsigned int i = 0; i < aspects.size(); i++){
		aspects[i]->Tick(dt);
	}
}

//-------------------------------------------------------------------------------------------------------------------------------
DDG51::DDG51(Engine *engine, Ogre::Vector3 pos, int ident):
		Entity381(engine, pos, ident){

	meshfilename = "ddg51.mesh";
	entityType = DDG51Type;
	this->minSpeed = 0;
	this->maxSpeed = 32.0f;//meters per second...
	this->acceleration = 5.0f; // fast
	this->turnRate = 20.0f; //4 degrees per second
	this->health = 2;
	this->size = 2;
	std::cout << "Created: " << this->name << std::endl;
}

DDG51::~DDG51(){

}

//-------------------------------------------------------------------------------------------------------------------------------
Carrier::Carrier(Engine *engine, Ogre::Vector3 pos, int ident):
		Entity381(engine, pos, ident){
	meshfilename = "cvn68.mesh";
	entityType = CarrierType;
	this->minSpeed = 0;
	this->maxSpeed = 40.0f;//meters per second...
	this->acceleration = 5.0f; // slow
	this->turnRate = 10.0f; //2 degrees per second
	this->health = 4;
	this->size = 4;
}

Carrier::~Carrier(){

}
//-------------------------------------------------------------------------------------------------------------------------------

SpeedBoat::SpeedBoat(Engine *engine, Ogre::Vector3 pos, int ident):
		Entity381(engine, pos, ident){
	meshfilename = "cigarette.mesh";
	entityType = SpeedBoatType;
	this->minSpeed = 0;
	this->maxSpeed = 60.0f;//meters per second...
	this->acceleration = 5.0f; // slow
	this->turnRate = 30.0f; //2 degrees per second
	this->health = 1;
	this->size = 1;
}

SpeedBoat::~SpeedBoat(){

}
//-------------------------------------------------------------------------------------------------------------------------------

Frigate::Frigate(Engine *engine, Ogre::Vector3 pos, int ident):
		Entity381(engine, pos, ident){
	meshfilename = "sleek.mesh";
	entityType = FrigateType;
	this->minSpeed = 0;
	this->maxSpeed = 30.0f;//meters per second...
	this->acceleration = 5.0f; // slow
	this->turnRate = 20.0f; //2 degrees per second
	this->health = 2;
	this->size = 2;
}

Frigate::~Frigate(){

}

//-------------------------------------------------------------------------------------------------------------------------------
Alien::Alien(Engine *engine, Ogre::Vector3 pos, int ident):
		Entity381(engine, pos, ident){
	meshfilename = "alienship.mesh";
	entityType = AlienType;
	this->minSpeed = 0;
	this->maxSpeed = 100.0f;//meters per second...
	this->acceleration = 10.0f; // slow
	this->turnRate = 40.0f; //2 degrees per second
	this->health = 1;
	this->size = 1;
}

Alien::~Alien(){

}
//-------------------------------------------------------------------------------------------------------------------------------


