/*
 * main.cpp
 *
 *  Created on: Mar 11, 2019
 *      Author: emjohnson
 */

#include <Engine.h>

int main(int argc, char *argv[]){

	Engine *engine = new Engine();

	engine->Init();
	engine->Run();
	engine->Cleanup();

	return 0;
}

