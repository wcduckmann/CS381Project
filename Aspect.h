
#ifndef __Aspect_h_
#define __Aspect_h_

#include<OgreVector3.h>
#include "Command.h"
class Entity381;    //Forward declaration of the Entity381 class

class Aspect
{
public:
  Aspect(Entity381* ent);
  virtual ~Aspect();

  Entity381* entity;
  virtual void AddCommand(Command *c);
  virtual void SetCommand(Command *c);
  virtual void Tick(float dt);


protected:

};



class Renderable : Aspect
{
public:
	Renderable(Entity381* ent);
	~Renderable();

	void Tick(float dt);
};



#endif // #ifndef __Aspect_h_
