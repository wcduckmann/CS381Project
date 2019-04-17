/*
 * main.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#include <Engine.h>

int main(int argc, char *argv[]){

	Engine *engine = new Engine();

	engine->Init();
	engine->Run();
	engine->Cleanup();

	return 0;
}


