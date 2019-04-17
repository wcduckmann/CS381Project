/*
 * Physics3D.h
 *
 *  Created on: Mar 7, 2018
 *      Author: sushil
 */

#ifndef PHYSICS3D_H_
#define PHYSICS3D_H_

#include <FlyingEntity381.h>
#include <Physics2D.h>

class Physics3D: public Physics2D {
public:
	Physics3D(FlyingEntity381* ent);
	virtual ~Physics3D();

	FlyingEntity381 *flyingEntity;

	void Tick(float dt);

};

#endif /* PHYSICS3D_H_ */
