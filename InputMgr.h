/*
 * InputMgr.h
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#ifndef INPUTMGR_H_
#define INPUTMGR_H_

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#  include <SdkTrays.h>
#  include <SdkCameraMan.h>
#include <Mgr.h>

class Engine;

class InputMgr:
		public Mgr,
		public OIS::KeyListener,
		public OIS::MouseListener{
		//public Ogre::WindowEventListener {

public:
	InputMgr(Engine *engine);
	virtual ~InputMgr();

	virtual bool keyPressed(const OIS::KeyEvent& ke);
	virtual bool keyReleased(const OIS::KeyEvent& ke);

	virtual bool mouseMoved(const OIS::MouseEvent& me);
	virtual bool mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id);

	OIS::InputManager* mInputMgr;
	OIS::Keyboard* mKeyboard;
	OIS::Mouse* mMouse;



	void Init();
	void Stop();
	void Tick(float dt);
	void LoadLevel();

	float keyboardTimer;
	constexpr static float keyTime = 0.1f;
	float deltaDesiredSpeed, deltaDesiredHeading, deltaDesiredAltitude;
	void UpdateCamera(float dt);
	void UpdateVelocityAndSelection(float dt);

	void HandleMouseSelection(const OIS::MouseEvent& me);
	float selectionDistanceSquaredThreshold;


};

#endif /* INPUTMGR_H_ */
