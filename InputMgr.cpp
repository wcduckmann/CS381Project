/*
 * InputMgr.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */
#include<cfloat>

#include <Engine.h>
#include <GfxMgr.h>
#include <InputMgr.h>
#include <EntityMgr.h>
#include <GameMgr.h>
#include <UnitAI.h>
#include <Command.h>
#include <Utils.h>

InputMgr::InputMgr(Engine *engine) : Mgr(engine), OIS::KeyListener(), OIS::MouseListener() {

	this->mInputMgr = 0;
	this->mKeyboard = 0;
	this->mMouse = 0;
	this->keyboardTimer = keyTime;
	deltaDesiredSpeed = 10.0f;
	deltaDesiredHeading = 10.0f;
	deltaDesiredAltitude = 20;
	this->selectionDistanceSquaredThreshold = 10000;
}

InputMgr::~InputMgr() {

}

void InputMgr::Init(){

	  OIS::ParamList pl;
	  size_t windowHandle = 0;
	  std::ostringstream windowHandleStr;

	  engine->gfxMgr->mWindow->getCustomAttribute("WINDOW", &windowHandle);
	  windowHandleStr << windowHandle;
	  pl.insert(std::make_pair(std::string("WINDOW"), windowHandleStr.str()));
	  // insert the following lines right before calling mInputSystem = OIS::InputManager::createInputSystem( paramList );
		#if defined OIS_WIN32_PLATFORM
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
		#elif defined OIS_LINUX_PLATFORM
		pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
		pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
		pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
		pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
		#endif

	  mInputMgr = OIS::InputManager::createInputSystem(pl);

	  mKeyboard = static_cast<OIS::Keyboard*>(
	    mInputMgr->createInputObject(OIS::OISKeyboard, true));
	  mMouse = static_cast<OIS::Mouse*>(
	    mInputMgr->createInputObject(OIS::OISMouse, true));

	  int left, top;
	  unsigned int width, height, depth;

	  engine->gfxMgr->mWindow->getMetrics(width, height, depth, left, top);
	  const OIS::MouseState &ms = mMouse->getMouseState();
	  ms.width = width;
	  ms.height = height;
	  mMouse->setEventCallback(this);
	  mKeyboard->setEventCallback(this);

}



void InputMgr::Stop(){
	if(mInputMgr){
		mInputMgr->destroyInputObject(mMouse);
		mInputMgr->destroyInputObject(mKeyboard);

		OIS::InputManager::destroyInputSystem(mInputMgr);
		mInputMgr = 0;
   	}
}

void InputMgr::Tick(float dt){

	mKeyboard->capture();
	if(mKeyboard->isKeyDown(OIS::KC_ESCAPE)){
		engine->keepRunning = false;
	}
	mMouse->capture();
//	mTrayMgr->frameRenderingQueued(fe);

	UpdateCamera(dt);
	UpdateVelocityAndSelection(dt);

}

void InputMgr::UpdateCamera(float dt){
	float move = 400.0f;
	float rotate = 0.1f;

	 Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;
	 Ogre::Vector3 camCheck = engine->gameMgr->cameraNode->getPosition();

	  if (mKeyboard->isKeyDown(OIS::KC_W)){
		  if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			  dirVec.z -= 2 * move;
		  else
			  dirVec.z -= move;
	  }
	  if (mKeyboard->isKeyDown(OIS::KC_S)){
		  if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			  dirVec.z += 2 * move;
		  else
			  dirVec.z += move;
	  }
	  if (mKeyboard->isKeyDown(OIS::KC_R)){
			  if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
				  dirVec.y += 2 * move;
			  else
				  dirVec.y += move;

	  }
	  if (mKeyboard->isKeyDown(OIS::KC_F)){
		  if(camCheck.y >= 5){
			  if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
				  dirVec.y -= 2 * move;
			  else
				  dirVec.y -= move;
		  }
	  }
	  if (mKeyboard->isKeyDown(OIS::KC_A))
	  {
		  if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			  dirVec.x -= 2 * move;
		  else
			  dirVec.x -= move;
	  }

	  if (mKeyboard->isKeyDown(OIS::KC_D))
	  {
		  if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			  dirVec.x += 2 * move;
		  else
			  dirVec.x += move;
	  }
	  if (mKeyboard->isKeyDown(OIS::KC_Z))
	 	  {
	 		  if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
	 			  engine->gameMgr->cameraNode->yaw(Ogre::Degree(2 * rotate));
	 		  else
	 		  engine->gameMgr->cameraNode->yaw(Ogre::Degree(0.5 * rotate));
	 	  }

	 	  if (mKeyboard->isKeyDown(OIS::KC_X))
	 	  {
	 		  if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
	 			  engine->gameMgr->cameraNode->yaw(Ogre::Degree(2 * -rotate));
	 		  else
	 			  engine->gameMgr->cameraNode->yaw(Ogre::Degree(0.5 * -rotate));
	 	  }

	 	  if (mKeyboard->isKeyDown(OIS::KC_Q))
	 	  {
	 		  if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
	 			  engine->gameMgr->cameraNode->pitch(Ogre::Degree(2 * rotate));
	 		  else
	 			  engine->gameMgr->cameraNode->pitch(Ogre::Degree(0.5 * rotate));
	 	  }

	 	  if (mKeyboard->isKeyDown(OIS::KC_E))
	 	  {
	 		  if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
	 			  engine->gameMgr->cameraNode->pitch(Ogre::Degree(2 * -rotate));
	 		  else
	 			  engine->gameMgr->cameraNode->pitch(Ogre::Degree(0.5 * -rotate));
	 	  }

	  engine->gameMgr->cameraNode->translate(dirVec * dt, Ogre::Node::TS_LOCAL);
}

void InputMgr::UpdateVelocityAndSelection(float dt){
	keyboardTimer -= dt;

	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD8)){
		keyboardTimer = keyTime;
		engine->entityMgr->selectedEntity->desiredSpeed += deltaDesiredSpeed;
	}
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD2)){
		keyboardTimer = keyTime;
		engine->entityMgr->selectedEntity->desiredSpeed -= deltaDesiredSpeed;
	}


	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD9)){
		keyboardTimer = keyTime;
		if(engine->entityMgr->selectedFlyingEntity != 0){
			engine->entityMgr->selectedFlyingEntity->desiredAltitude += deltaDesiredAltitude;
		}
	}
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD3)){
		keyboardTimer = keyTime;
		if(engine->entityMgr->selectedFlyingEntity != 0)
			engine->entityMgr->selectedFlyingEntity->desiredAltitude -= deltaDesiredAltitude;
	}


	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD4)){
		keyboardTimer = keyTime;
		engine->entityMgr->selectedEntity->desiredHeading -= deltaDesiredHeading;
	//turn left is decreasing degrees, turn right is increasing degrees because increasing degrees gives us the +ive Z axis
	}
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD6)){
		keyboardTimer = keyTime;
		engine->entityMgr->selectedEntity->desiredHeading += deltaDesiredHeading;
	}
	engine->entityMgr->selectedEntity->desiredHeading = FixAngle(engine->entityMgr->selectedEntity->desiredHeading);




	//Set velocity to zero....
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_SPACE)){
		keyboardTimer = keyTime;
		engine->entityMgr->selectedEntity->velocity = Ogre::Vector3::ZERO;
		engine->entityMgr->selectedEntity->desiredSpeed = engine->entityMgr->selectedEntity->speed = 0;
		engine->entityMgr->selectedEntity->desiredHeading = engine->entityMgr->selectedEntity->heading;
	}

	//tab handling
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_TAB)){
		keyboardTimer = keyTime;
		engine->entityMgr->SelectNextEntity();
	}
}

void InputMgr::LoadLevel(){

}

bool InputMgr::keyPressed(const OIS::KeyEvent& ke){
	return true;
}

bool InputMgr::keyReleased(const OIS::KeyEvent& ke){
	return true;
}

bool InputMgr::mouseMoved(const OIS::MouseEvent& me){
	return true;
}

bool InputMgr::mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID mid){
	std::cout << "Mouse pressed" << std::endl;
	if(OIS::MB_Left == mid){
		std::cout << "Left mouse press" << std::endl;
		HandleMouseSelection(me);
	}

	if(mid == OIS::MB_Right){
		std::cout << "Right mouse press" << std::endl;
		Ogre::Real screenWidth = Ogre::Root::getSingleton().getAutoCreatedWindow()->getWidth();
		Ogre::Real screenHeight = Ogre::Root::getSingleton().getAutoCreatedWindow()->getHeight();
		OIS::MouseState arg = mMouse->getMouseState();
		bool commandSet = false;
		Ogre::Real offsetX = arg.X.abs / screenWidth;
		Ogre::Real offsetY = arg.Y.abs / screenHeight;

		Ogre::Ray mouseRay = engine->gfxMgr->mCamera->getCameraToViewportRay(offsetX, offsetY);

		std::pair<bool, float> result = mouseRay.intersects(engine->gfxMgr->oceanSurface);
		if(result.first){
			Ogre::Vector3 posUnderMouse = mouseRay.getPoint(result.second);
			float minDistanceSquared = FLT_MAX;
			float distanceSquared; //because squareroot is expensive
			for(unsigned int i = 0; i < engine->entityMgr->entities.size(); i++){
				distanceSquared = posUnderMouse.squaredDistance(engine->entityMgr->entities[i]->position);
				if (distanceSquared < selectionDistanceSquaredThreshold){
					if (distanceSquared < minDistanceSquared){
						Command * inter = new Intercept(engine->entityMgr->selectedEntity, engine->entityMgr->entities[i]);
						if(mKeyboard->isKeyDown(OIS::KC_LSHIFT)){
							engine->entityMgr->selectedEntity->aspects[2]->SetCommand(inter);
							std::cout << "Intercept command added" << std::endl;
							commandSet = true;
						}
						else{
							engine->entityMgr->selectedEntity->aspects[2]->AddCommand(inter);
							std::cout << "Intercept command added" << std::endl;
							commandSet = true;
						}
					}
				}
			}

			if(!commandSet){
				Command * move = new MoveTo(engine->entityMgr->selectedEntity, posUnderMouse);
				if(mKeyboard->isKeyDown(OIS::KC_LSHIFT)){
					engine->entityMgr->selectedEntity->aspects[2]->SetCommand(move);
					std::cout << "MoveTo command added" << std::endl;
					commandSet = true;
				}
				else{
					engine->entityMgr->selectedEntity->aspects[2]->AddCommand(move);
					std::cout << "MoveTo command added" << std::endl;
					commandSet = true;
				}
			}
		}

	}

	return true;
}

bool InputMgr::mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID mid){
	return true;
}

//check if ms.width and ms.height need to be adjusted when things change
void InputMgr::HandleMouseSelection(const OIS::MouseEvent &me){
	const OIS::MouseState &ms = mMouse->getMouseState();
	int index = -1;
	Ogre::Ray mouseRay = engine->gfxMgr->mCamera->getCameraToViewportRay(ms.X.abs/(float) ms.width, ms.Y.abs/(float)ms.height);
	std::pair<bool, float> result = mouseRay.intersects(engine->gfxMgr->oceanSurface);
	if(result.first){
		Ogre::Vector3 posUnderMouse = mouseRay.getPoint(result.second);
		float minDistanceSquared = FLT_MAX;
		float distanceSquared; //because squareroot is expensive
		for(unsigned int i = 0; i < engine->entityMgr->entities.size(); i++){
			distanceSquared = posUnderMouse.squaredDistance(engine->entityMgr->entities[i]->position);
			if (distanceSquared < selectionDistanceSquaredThreshold){
				if (distanceSquared < minDistanceSquared){
					index = i;
					minDistanceSquared = distanceSquared;
				}
			}
		}
		engine->entityMgr->Select(index);
	}
}


