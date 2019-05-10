

/*
 * GameMgr.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#include <Engine.h>

#include <EntityMgr.h>
#include <GameMgr.h>
#include <GfxMgr.h>
#include <UiMgr.h>
#include <Aspect.h>
#include <UnitAI.h>

#include <iostream>
#include <Types381.h>

#include <cstdlib>
#include <ctime>

#include <OgreOverlay.h>
#include <OgreSceneNode.h>


GameMgr::GameMgr(Engine *engine): Mgr(engine) {
	cameraNode = 0;
	playerBoard = new Board();
	AIBoard = new Board();

	for(int i= 0; i < 5; i++){

		alreadySunk[i] = 0;
	}
}

GameMgr::~GameMgr() {
	// TODO Auto-generated destructor stub
}

void GameMgr::Init(){

}

void GameMgr::LoadLevel(){

	  engine->gfxMgr->mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	  engine->gfxMgr->mCamera->lookAt(Ogre::Vector3(0, 0, 0));
	  Ogre::Light* light = engine->gfxMgr->mSceneMgr->createLight("MainLight");
	  light->setPosition(20.0, 80.0, 50.0);

	  // a fixed point in the ocean so you can see relative motion
	  /*
	  Ogre::Entity* ogreEntityFixed = engine->gfxMgr->mSceneMgr->createEntity("robot.mesh");
	  Ogre::SceneNode* sceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 100, -200));
	  sceneNode->attachObject(ogreEntityFixed);
	  sceneNode->showBoundingBox(true);
	  */
	  // A node to attach the camera to so we can move the camera node instead of the camera.
	  cameraNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	  cameraNode->setPosition(0, 1300, 500);
	  cameraNode->pitch(Ogre::Degree(-80));
	  cameraNode->attachObject(engine->gfxMgr->mCamera);

	  engine->gfxMgr->MakeSky();
	  //engine->gfxMgr->MakeFog();
	  engine->gfxMgr->MakeGround();

	  std::srand(std::time(NULL));
	  MakeBoard();
	  //MakeEntities();
}

void GameMgr::MakeEntities(){
	Ogre::Vector3 pos = Ogre::Vector3(-400, 0, 50);
	playerBoard->placeDestroyer(0, 0);
	AIBoard->placeDestroyer(0, 0);
	engine->entityMgr->CreateEntityOfTypeAtPosition(DDG51Type, pos);
	pos.x += 100;
	pos.z += 100;
	playerBoard->placeCarrier(1, 0);
	AIBoard->placeCarrier(1, 0);
	engine->entityMgr->CreateEntityOfTypeAtPosition(CarrierType, pos);
	pos.x = -450;
	pos.z += 100;
	playerBoard->placeSpeedboat(2, 0);
	AIBoard->placeSpeedboat(2, 0);
	engine->entityMgr->CreateEntityOfTypeAtPosition(SpeedBoatType, pos);
	pos.x = -400;
	pos.z += 100;
	playerBoard->placeFrigate(3, 0);
	AIBoard->placeFrigate(3, 0);
	engine->entityMgr->CreateEntityOfTypeAtPosition(FrigateType, pos);
	pos.x = -450;
	pos.z += 100;
	playerBoard->placeAlien(4, 0);
	AIBoard->placeAlien(4, 0);
	engine->entityMgr->CreateEntityOfTypeAtPosition(AlienType, pos);
	/*
	pos.x = 0;
	engine->entityMgr->CreateEntityOfTypeAtPosition(BansheeType, pos);
	*/
	engine->entityMgr->SelectNextEntity(); //sets selection
}

void GameMgr::MakeBoard(){

	Ogre::Vector3 position = Ogre::Vector3(-500, 5, 0);

	//Creates vertical lines for gameboard
	for(int i = 0; i < 10; i++){

		Ogre::Entity* gridLine = engine->gfxMgr->mSceneMgr->createEntity("cube.mesh");
		Ogre::SceneNode* lineNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(position);
		lineNode->attachObject(gridLine);
		lineNode->setScale(0.1,0,20);

		position.x += 100;

	}

	position = Ogre::Vector3(0, 5, -1000);

	//Creates horizontal lines for gameboard
	for(int i = 0; i < 20; i++){

		Ogre::Entity* gridLine = engine->gfxMgr->mSceneMgr->createEntity("cube.mesh");
		Ogre::SceneNode* lineNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(position);
		lineNode->attachObject(gridLine);
		lineNode->setScale(10,0,0.1);

		position.z += 100;

	}

	Ogre::Entity* wallMid = engine->gfxMgr->mSceneMgr->createEntity("cube.mesh");
	Ogre::SceneNode* wallMNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0,0,0));
	wallMNode->attachObject(wallMid);
	wallMNode->setScale(10, 20, 0);

	Ogre::Entity* wallLeft = engine->gfxMgr->mSceneMgr->createEntity("cube.mesh");
	Ogre::SceneNode* wallLNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(-500,0,0));
	wallLNode->attachObject(wallLeft);
	wallLNode->setScale(0, 10, 20);

	Ogre::Entity* wallRight = engine->gfxMgr->mSceneMgr->createEntity("cube.mesh");
	Ogre::SceneNode* wallRNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(500,0,0));
	wallRNode->attachObject(wallRight);
	wallRNode->setScale(0, 10, 20);

	Ogre::Entity* wallBot = engine->gfxMgr->mSceneMgr->createEntity("cube.mesh");
	Ogre::SceneNode* wallBNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0,0,-1000));
	wallBNode->attachObject(wallBot);
	wallBNode->setScale(10, 10, 0);

	Ogre::Entity* wallTop = engine->gfxMgr->mSceneMgr->createEntity("cube.mesh");
	Ogre::SceneNode* wallTNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0,0,1000));
	wallTNode->attachObject(wallTop);
	wallTNode->setScale(10, 10, 0);
}

void GameMgr::AIMove(){

	sinkAiShip();

	int row = 1 + std::rand() % 10;
	int col = 1 + std::rand() % 10;

	Ogre::StringConverter converter;



	Ogre::String rowValue = converter.toString(row);
	Ogre::String colValue = converter.toString(col);
	if(playerBoard->Fire(row, col)){
		engine->uiMgr->infoBox->appendText("Your ship has been hit at row ");
		engine->uiMgr->infoBox->appendText(rowValue);
		engine->uiMgr->infoBox->appendText(" and column ");
		engine->uiMgr->infoBox->appendText(colValue);
		engine->uiMgr->infoBox->appendText("\n");
	}
	else{
		engine->uiMgr->infoBox->appendText("The enemy has missed");
		engine->uiMgr->infoBox->appendText("\n");
	}


}

void GameMgr::sendShipAway(){
	Ogre::Vector3 goAway = Ogre::Vector3(1000, 0, 1000);

	if(playerBoard->alienHealth == 0){
		MoveTo * move = new MoveTo(engine->entityMgr->entities[4], goAway);
		engine->entityMgr->entities[4]->aspects[2]->AddCommand(move);

	}

	if(playerBoard->speedboatHealth == 0){
		MoveTo * move = new MoveTo(engine->entityMgr->entities[2], goAway);
		engine->entityMgr->entities[2]->aspects[2]->AddCommand(move);

	}

	if(playerBoard->frigateHealth == 0){
		MoveTo * move = new MoveTo(engine->entityMgr->entities[3], goAway);
		engine->entityMgr->entities[3]->aspects[2]->AddCommand(move);

	}

	if(playerBoard->carrierHealth == 0){
		MoveTo * move = new MoveTo(engine->entityMgr->entities[1], goAway);
		engine->entityMgr->entities[1]->aspects[2]->AddCommand(move);

	}

	if(playerBoard->destroyerHealth == 0){
		MoveTo * move = new MoveTo(engine->entityMgr->entities[0], goAway);
		engine->entityMgr->entities[0]->aspects[2]->AddCommand(move);

	}
}

void GameMgr::sinkAiShip(){

	   if(AIBoard->carrierHealth == 0 && alreadySunk[0] == 0){
		   engine->uiMgr->infoBox->appendText("You sunk the enemy carrier! \n");
		   alreadySunk[0] = 1;
	   }
	   else if(AIBoard->alienHealth == 0 && alreadySunk[1] == 0){
	       engine->uiMgr->infoBox->appendText("You sunk the enemy alien ship! \n");
	       alreadySunk[1] = 1;
	   }
	   else if(AIBoard->frigateHealth == 0 && alreadySunk[2] == 0){
	       engine->uiMgr->infoBox->appendText("You sunk the enemy frigate! \n");
	       alreadySunk[2] = 1;
	   }
	   else if(AIBoard->speedboatHealth == 0 && alreadySunk[3] == 0){
	       engine->uiMgr->infoBox->appendText("You sunk the enemy speedboat! \n");
	       alreadySunk[3] = 1;
	   }
	   else if(AIBoard->destroyerHealth == 0 && alreadySunk[4] == 0){
	       engine->uiMgr->infoBox->appendText("You sunk the enemy destroyer! \n");
	       alreadySunk[4] = 1;
	   }
}
