/*
 * Engine.h
 *
 *  Created on: Mar 11, 2019
 *      Author: emjohnson
 */

#ifndef INC_ENGINE_H_
#define INC_ENGINE_H_


class EntityMgr;
class GameMgr;
class GfxMgr;
class InputMgr;
class UiMgr;
class SoundMgr;

class Engine {
public:
	Engine();
	virtual ~Engine();

	EntityMgr *entityMgr;
	GameMgr   *gameMgr;
	GfxMgr    *gfxMgr;
	InputMgr  *inputMgr;
	UiMgr	  *uiMgr;
	//OgreSND::SoundMgr*	soundMgr;

	void Init();
	void Run();
	void TickAll(float dt);
	void Cleanup();

	bool keepRunning;
};


#endif /* INC_ENGINE_H_ */
