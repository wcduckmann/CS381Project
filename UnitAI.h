
/*
 * UnitAI.h
 *
 *  Created on: Apr 5, 2019
 *      Author: wduckhorn
 */

#ifndef INC_UNITAI_H_
#define INC_UNITAI_H_

#include "Aspect.h"
#include "InputMgr.h"
#include <queue>
#include "Types381.h"
#include "Command.h"

class UnitAI: public Aspect {

public:

	std::queue<Command *> commands;

	UnitAI(Entity381 * ent);
	~UnitAI();

	void Tick(float dt);
	void SetCommand(Command * c);
	void AddCommand(Command * c);

};




#endif /* INC_UNITAI_H_ */
