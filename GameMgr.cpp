
/*
 * GameMgr.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#include <Engine.h>

#include <EntityManager.h>
#include <GameMgr.h>
#include <GfxMgr.h>

#include <iostream>
#include <Types381.h>

#include <OgreOverlay.h>
#include <OgreSceneNode.h>


GameMgr::GameMgr(Engine *engine): Mgr(engine) {
	cameraNode = 0;
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
	  cameraNode->setPosition(0, 200, 500);
	  cameraNode->attachObject(engine->gfxMgr->mCamera);

	  engine->gfxMgr->MakeSky();
	  //engine->gfxMgr->MakeFog();
	  engine->gfxMgr->MakeGround();


	  MakeBoard();
	  MakeEntities();
}

void GameMgr::MakeEntities(){
	Ogre::Vector3 pos = Ogre::Vector3(-400, 0, 250);
	engine->entityMgr->CreateEntityOfTypeAtPosition(DDG51Type, pos);
	pos.x += 200;
	engine->entityMgr->CreateEntityOfTypeAtPosition(CarrierType, pos);
	pos.x += 200;
	engine->entityMgr->CreateEntityOfTypeAtPosition(SpeedBoatType, pos);
	pos.x += 200;
	engine->entityMgr->CreateEntityOfTypeAtPosition(FrigateType, pos);
	pos.x += 200;
	engine->entityMgr->CreateEntityOfTypeAtPosition(AlienType, pos);

	pos.x = 0;
	engine->entityMgr->CreateEntityOfTypeAtPosition(BansheeType, pos);

	engine->entityMgr->SelectNextEntity(); //sets selection
}

void GameMgr::MakeBoard(){

	Ogre::Vector3 position = Ogre::Vector3(-500, 5, 0);

	Ogre::Entity* gridLine = engine->gfxMgr->mSceneMgr->createEntity("cube.mesh");
	Ogre::SceneNode* lineNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(position);
	lineNode->attachObject(gridLine);
	lineNode->setScale(0.5,0,10);

	//Creates vertical lines for gameboard
	for(int i = 0; i < 10; i++){

		Ogre::Entity* gridLine = engine->gfxMgr->mSceneMgr->createEntity("cube.mesh");
		Ogre::SceneNode* lineNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(position);
		lineNode->attachObject(gridLine);
		lineNode->setScale(0.25,0,20);

		position.x += 100;

	}

	position = Ogre::Vector3(0, 5, -1000);

	//Creates horizontal lines for gameboard
	for(int i = 0; i < 20; i++){

		Ogre::Entity* gridLine = engine->gfxMgr->mSceneMgr->createEntity("cube.mesh");
		Ogre::SceneNode* lineNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(position);
		lineNode->attachObject(gridLine);
		lineNode->setScale(10,0,0.25);

		position.z += 100;

	}

	Ogre::Entity* wallMid = engine->gfxMgr->mSceneMgr->createEntity("cube.mesh");
	Ogre::SceneNode* wallMNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0,0,0));
	wallMNode->attachObject(wallMid);
	wallMNode->setScale(10, 20, 0);

	Ogre::Entity* wallLeft = engine->gfxMgr->mSceneMgr->createEntity("cube.mesh");
	Ogre::SceneNode* wallLNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(-500,0,0));
	wallLNode->attachObject(wallLeft);
	wallLNode->setScale(0.5, 10, 20);

	Ogre::Entity* wallRight = engine->gfxMgr->mSceneMgr->createEntity("cube.mesh");
	Ogre::SceneNode* wallRNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(500,0,0));
	wallRNode->attachObject(wallRight);
	wallRNode->setScale(0.5, 10, 20);

	Ogre::Entity* wallBot = engine->gfxMgr->mSceneMgr->createEntity("cube.mesh");
	Ogre::SceneNode* wallBNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0,0,-1000));
	wallBNode->attachObject(wallBot);
	wallBNode->setScale(10, 10, 0.5);

	Ogre::Entity* wallTop = engine->gfxMgr->mSceneMgr->createEntity("cube.mesh");
	Ogre::SceneNode* wallTNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0,0,1000));
	wallTNode->attachObject(wallTop);
	wallTNode->setScale(10, 10, 0.5);
}
