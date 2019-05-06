/*
 * GameMgr.h
 *
 *  Created on: Mar 11, 2019
 *      Author: emjohnson
 */

#ifndef GAMEMGR_H_
#define GAMEMGR_H_

#include <Mgr.h>
#include <Board.h>

class GameMgr: public Mgr {
public:
	GameMgr(Engine *engine);
	virtual ~GameMgr();

	void Init();
	void LoadLevel();

	void MakeGround();
	void MakeSky();
	void MakeEntities();
	void MakeBoard();
	void AIMove();
	void sendShipAway();
	void sinkAiShip();

	Ogre::SceneNode *cameraNode;
	Board * playerBoard;
	Board * AIBoard;

	int alreadySunk[5];

};

#endif /* GAMEMGR_H_ */
