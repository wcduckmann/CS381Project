#ifndef __Entity381_h_
#define __Entity381_h_

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>
#include <Types381.h>

#include <Engine.h>

class Aspect;

class Entity381
{
public:
  Entity381(Engine *engine, Ogre::Vector3 pos, int identity);
  virtual ~Entity381();

  Engine *engine;

  //static data
  int identity;
  std::string name;
  std::string meshfilename;
  Ogre::SceneNode* sceneNode;
  Ogre::Entity*    ogreEntity;
  float acceleration, turnRate;
  float minSpeed, maxSpeed;

  //dynamic data
  Ogre::Vector3 position;
  Ogre::Vector3 velocity;
  bool isSelected;
  float desiredHeading, desiredSpeed;
  float heading, speed;

  //game specific data
  int health, size;

  bool didSelectSoundPlay;

  //sound
  std::string soundFile;
  bool playSound;
  unsigned int auioId;


  EntityTypes entityType;

  std::vector<Aspect* > aspects;

  void Init();

  void Tick(float dt);

protected:


};



class Carrier: public Entity381 {
public:
	Carrier(Engine *engine, Ogre::Vector3 pos, int identity);
	virtual ~Carrier();

};

class DDG51: public Entity381 {
public:
	DDG51(Engine *engine, Ogre::Vector3 pos, int identity);
	virtual ~DDG51();

};

class SpeedBoat: public Entity381 {
public:
	SpeedBoat(Engine *engine, Ogre::Vector3 pos, int identity);
	virtual ~SpeedBoat();

};

class Frigate: public Entity381 {
public:
	Frigate(Engine *engine, Ogre::Vector3 pos, int identity);
	virtual ~Frigate();

};

class Alien: public Entity381 {
public:
	Alien(Engine *engine, Ogre::Vector3 pos, int identity);
	virtual ~Alien();

};


#endif // #ifndef __Entity381_h_
