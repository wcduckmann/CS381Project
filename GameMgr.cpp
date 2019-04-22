
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
	Ogre::Vector3 pos = Ogre::Vector3(-1000, 0, 100);
	engine->entityMgr->CreateEntityOfTypeAtPosition(DDG51Type, pos);
	pos.x += 500;
	engine->entityMgr->CreateEntityOfTypeAtPosition(CarrierType, pos);
	pos.x += 500;
	engine->entityMgr->CreateEntityOfTypeAtPosition(SpeedBoatType, pos);
	pos.x += 500;
	engine->entityMgr->CreateEntityOfTypeAtPosition(FrigateType, pos);
	pos.x += 500;
	engine->entityMgr->CreateEntityOfTypeAtPosition(AlienType, pos);

	pos.x = 0;
	engine->entityMgr->CreateEntityOfTypeAtPosition(BansheeType, pos);

	engine->entityMgr->SelectNextEntity(); //sets selection
}

void GameMgr::MakeBoard(){

	Ogre::Vector3 position = Ogre::Vector3(-1000, 5, 0);

	Ogre::Entity* gridLine = engine->gfxMgr->mSceneMgr->createEntity("cube.mesh");
	Ogre::SceneNode* lineNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(position);
	lineNode->attachObject(gridLine);
	lineNode->setScale(0.5,0,100);

	//Creates horizontal lines for gameboard
	for(int i = 0; i < 20; i++){

		Ogre::Entity* gridLine = engine->gfxMgr->mSceneMgr->createEntity("cube.mesh");
		Ogre::SceneNode* lineNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(position);
		lineNode->attachObject(gridLine);
		lineNode->setScale(0.5,0,100);

		position.x += 1000;

	}

	position = Ogre::Vector3(0, 5, -5000);

	//Creates vertical lines for gameboard
	for(int i = 0; i < 10; i++){

		Ogre::Entity* gridLine = engine->gfxMgr->mSceneMgr->createEntity("cube.mesh");
		Ogre::SceneNode* lineNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(position);
		lineNode->attachObject(gridLine);
		lineNode->setScale(100,0,0.5);

		position.z += 1000;

	}

	Ogre::Entity* wall = engine->gfxMgr->mSceneMgr->createEntity("cube.mesh");
	Ogre::SceneNode* wallNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0,0,0));
	wallNode->attachObject(wall);
	wallNode->setScale(100, 20, 0);
}
