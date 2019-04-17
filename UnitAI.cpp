/*
 * UnitAI.cpp
 *
 *  Created on: Apr 6, 2019
 *      Author: wduckhorn
 */

#include "UnitAI.h"
#include "Engine.h"

UnitAI::UnitAI(Entity381 * ent) : Aspect(ent){


}


UnitAI::~UnitAI(){


}

void UnitAI::Tick(float dt){

	Command * tmp;

	if(commands.front() == NULL){

		return;
	}

	for(unsigned int i = 0; i < commands.size(); i++){
		if(!commands.front()->done()){
			commands.front()->tick(dt);
		}
		else{
			std::cout << "Queue Popped" << std::endl;
			tmp = commands.front();
			commands.pop();
			delete tmp;
		}
	}

}

void UnitAI::SetCommand(Command * c){
	while(!commands.empty()){
		commands.pop();
	}
	std::cout << "Commands cleared" << std::endl;
	commands.push(c);
	std::cout << "Command set" << std::endl;
}

void UnitAI::AddCommand(Command * c){
	commands.push(c);
	std::cout << "Command added" << std::endl;
}
