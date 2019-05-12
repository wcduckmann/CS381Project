
/*
 * UiMgr.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: chad
 */

#include <UiMgr.h>
#include <Engine.h>
#include <GfxMgr.h>
#include <InputMgr.h>
#include <EntityMgr.h>
#include <Types381.h>
#include <GameMgr.h>

UiMgr::UiMgr(Engine* eng): Mgr(eng){
	// Initialize the OverlaySystem (changed for Ogre 1.9)
	    mOverlaySystem = new Ogre::OverlaySystem();
	    engine->gfxMgr->mSceneMgr->addRenderQueueListener(mOverlaySystem);

	    //Ogre::WindowEventUtilities::addWindowEventListener(engine->gfxMgr->ogreRenderWindow, this);
}

UiMgr::~UiMgr(){ // before gfxMgr destructor

}

void UiMgr::Init(){
	//init sdktrays

    mInputContext.mKeyboard = engine->inputMgr->mKeyboard;
    mInputContext.mMouse = engine->inputMgr->mMouse;
    mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", engine->gfxMgr->mWindow, mInputContext, this);
    //mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    //mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
    //mTrayMgr->hideCursor();
}

void UiMgr::stop(){

}

void UiMgr::LoadLevel(){

	// Create background material
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("Background", "General");
	material->getTechnique(0)->getPass(0)->createTextureUnitState("water.bmp");
	material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(true);
	material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(true);
	material->getTechnique(0)->getPass(0)->setLightingEnabled(false);

	// Create background rectangle covering the whole screen
	rect = new Ogre::Rectangle2D(true);
	rect->setCorners(-1.0, 1.0, 1.0, -1.0);
	rect->setMaterial("Background");

	// Use infinite AAB to always stay visible
	Ogre::AxisAlignedBox aabInf;
	aabInf.setInfinite();
	rect->setBoundingBox(aabInf);

	// Attach background to the scene
	Ogre::SceneNode* node = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode("Background");
	node->attachObject(rect);

	mTrayMgr->createLabel(OgreBites::TL_CENTER, "Title", "Welcome to Tides of War", 500);
	mTrayMgr->createButton(OgreBites::TL_CENTER, "PlayButton", "Play!", 500);

}

void UiMgr::Tick(float dt){
	mTrayMgr->refreshCursor();

	/*switch(engine->entityMgr->selectedEntity->entityType)
	{
		case DDG51Type:
			infoLabel->setCaption("Type: DDG51");
			infoLabel2->setCaption("Heading: " + std::to_string(engine->entityMgr->selectedEntity->heading));
			infoLabel3->setCaption("Speed: " + std::to_string(engine->entityMgr->selectedEntity->speed));
			break;
		case CarrierType:
			infoLabel->setCaption("Type: Carrier");
			infoLabel2->setCaption("Heading: " + std::to_string(engine->entityMgr->selectedEntity->heading));
			infoLabel3->setCaption("Speed: " + std::to_string(engine->entityMgr->selectedEntity->speed));
			break;
		case SpeedBoatType:
			infoLabel->setCaption("Type: SpeedBoat");
			infoLabel2->setCaption("Heading: " + std::to_string(engine->entityMgr->selectedEntity->heading));
			infoLabel3->setCaption("Speed: " + std::to_string(engine->entityMgr->selectedEntity->speed));
			break;
		case FrigateType:
			infoLabel->setCaption("Type: Frigate");
			infoLabel2->setCaption("Heading: " + std::to_string(engine->entityMgr->selectedEntity->heading));
			infoLabel3->setCaption("Speed: " + std::to_string(engine->entityMgr->selectedEntity->speed));
			break;
		case AlienType:
			infoLabel->setCaption("Type: Alien");
			infoLabel2->setCaption("Heading: " + std::to_string(engine->entityMgr->selectedEntity->heading));
			infoLabel3->setCaption("Speed: " + std::to_string(engine->entityMgr->selectedEntity->speed));
			break;
		case BansheeType:
			infoLabel->setCaption("Type: Banshee");
			infoLabel2->setCaption("Heading: " + std::to_string(engine->entityMgr->selectedEntity->heading));
			infoLabel3->setCaption("Speed: " + std::to_string(engine->entityMgr->selectedEntity->speed));
			break;
		default:
			infoLabel->setCaption("No Unit Selected");
			infoLabel2->setCaption("No Unit Selected");
			infoLabel3->setCaption("No Unit Selected");
			break;
	}*/
}

void UiMgr::windowResized(Ogre::RenderWindow* rw){
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = engine->inputMgr->mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void UiMgr::windowClosed(Ogre::RenderWindow* rw){

}

bool UiMgr::keyPressed(const OIS::KeyEvent &arg) {
	std::cout << "Key Pressed: " << arg.key << std::endl;
	return true;
}
bool UiMgr::keyReleased(const OIS::KeyEvent &arg){
	return true;
}
bool UiMgr::mouseMoved(const OIS::MouseEvent &arg){
    if (mTrayMgr->injectMouseMove(arg)) return true;
	return false;
}
bool UiMgr::mousePressed(const OIS::MouseEvent &me, OIS::MouseButtonID mid) {
	std::cout << "mouse clicked" << std::endl;
	if (mTrayMgr->injectMouseDown(me, mid)) return true;
	return false;
}
bool UiMgr::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
    if (mTrayMgr->injectMouseUp(arg, id)) return true;
    /* normal mouse processing here... */
	return false;
}

void UiMgr::buttonHit(OgreBites::Button *b){
    if(b->getName()=="FireButton")
    {
        /*std::cout <<"Boat Spawned!" << std::endl;
        Ogre::Vector3 pos;
        pos.x = 0;
        pos.y = 0;
        pos.z = -100;
        engine->entityMgr->CreateEntityOfTypeAtPosition(SpeedBoatType,pos);*/
    	Ogre::StringConverter converter;

    	Ogre::String rowValue = converter.toString(rowSlider->getValue());
    	Ogre::String colValue = converter.toString(colSlider->getValue());

        infoBox->appendText("Firing on enemy position: ");
        infoBox->appendText(rowValue);
        infoBox->appendText(", ");
        infoBox->appendText(colValue);
        infoBox->appendText("\n");

        if(engine->gameMgr->AIBoard->Fire(rowSlider->getValue(), colSlider->getValue())){
            infoBox->appendText("Ship has been hit at row ");
            infoBox->appendText(rowValue);
            infoBox->appendText(" and column ");
            infoBox->appendText(colValue);
            infoBox->appendText("\n");



        }
        else{
        	infoBox->appendText("Miss!");
            infoBox->appendText("\n");
        }

        engine->gameMgr->AIMove();
        engine->gameMgr->sendShipAway();

        bool gameLost = engine->gameMgr->playerBoard->checkGameStatus();
        bool gameWon = engine->gameMgr->AIBoard->checkGameStatus();

        if(gameLost){
        	infoBox->appendText("You Lose! Game over. \n");
        	infoBox->appendText("Tides of War was made by Andrew Cooper, Erik Johnson, and Will Duckhorn.\n");

        	mTrayMgr->destroyAllWidgetsInTray(OgreBites::TL_TOPLEFT);
        	mTrayMgr->destroyAllWidgetsInTray(OgreBites::TL_TOPRIGHT);
        	mTrayMgr->destroyAllWidgetsInTray(OgreBites::TL_RIGHT);
        	mTrayMgr->destroyAllWidgetsInTray(OgreBites::TL_BOTTOM);

        	mTrayMgr->createLabel(OgreBites::TL_CENTER, "LoseScreen", "Better luck next time!", 500);
        	mTrayMgr->createLabel(OgreBites::TL_CENTER, "VisCredits", "Andrew Cooper - Visuals", 500);
        	mTrayMgr->createLabel(OgreBites::TL_CENTER, "UICredits", "Erik Johnson - UI", 500);
            mTrayMgr->createLabel(OgreBites::TL_CENTER, "GameCredits", "Will Duckhorn - Gameplay", 500);
        	mTrayMgr->createButton(OgreBites::TL_CENTER, "QuitButton", "Quit", 500);
        }
        else if(gameWon){
        	infoBox->appendText("You win! Game over. \n");
        	infoBox->appendText("Tides of War was made by Andrew Cooper, Erik Johnson, and Will Duckhorn.\n");

        	mTrayMgr->createLabel(OgreBites::TL_CENTER, "WinScreen", "Congratulations, you win!", 500);
        	mTrayMgr->createLabel(OgreBites::TL_CENTER, "VisCredits", "Andrew Cooper - Visuals", 500);
        	mTrayMgr->createLabel(OgreBites::TL_CENTER, "UICredits", "Erik Johnson - UI", 500);
        	mTrayMgr->createLabel(OgreBites::TL_CENTER, "GameCredits", "Will Duckhorn - Gameplay", 500);
        	mTrayMgr->createButton(OgreBites::TL_CENTER, "QuitButton", "Quit", 500);
        }

        clicks++;
        if(clicks >= 2){
        	infoBox->setScrollPercentage(100);
        }

    }
    else if(b->getName()=="PlayButton")
    {

    	spawnButton = mTrayMgr->createButton(OgreBites::TL_LEFT, "spawnDestroyer", "Spawn Destroyer");
    	rowSlider = mTrayMgr->createThickSlider(OgreBites::TL_LEFT, "SpawnRowSlider", "Row: ", 200, 150, 1, 10, 10);
    	colSlider = mTrayMgr->createThickSlider(OgreBites::TL_LEFT, "SpawnColSlider", "Col: ", 200, 150, 1, 10, 10);


    	/*Ogre::StringVector shipOptions;
    	shipOptions.push_back("Select SpeedBoat");
    	shipOptions.push_back("Select Destroyer");
    	shipOptions.push_back("Select Carrier");
    	shipOptions.push_back("Select Frigate");
    	shipOptions.push_back("Select Alien Ship");
    	mTrayMgr->createLongSelectMenu(OgreBites::TL_TOPRIGHT, "MyMenu", "Select Ship", 300, 5,shipOptions);*/

    	mTrayMgr->showBackdrop("ECSLENT/UI");

    	//mLabel = mTrayMgr->createLabel(OgreBites::TL_LEFT,"MyLabel","Label!",250);

    	//infoLabel = mTrayMgr->createLabel(OgreBites::TL_RIGHT, "infoLabel", "No Unit Selected", 250);
    	//infoLabel2 = mTrayMgr->createLabel(OgreBites::TL_RIGHT, "infoLabel2", "No Unit Selected", 250);
    	//infoLabel3 = mTrayMgr->createLabel(OgreBites::TL_RIGHT, "infoLabel3", "No Unit Selected", 250);

    	/*mTrayMgr->createButton(OgreBites::TL_RIGHT, "FireButton", "Fire!");
    	rowSlider = mTrayMgr->createThickSlider(OgreBites::TL_RIGHT, "RowSlider", "Row: ", 200, 150, 1, 10, 10);
    	colSlider = mTrayMgr->createThickSlider(OgreBites::TL_RIGHT, "ColSlider", "Col: ", 200, 150, 1, 10, 10);*/

    	infoBox = mTrayMgr->createTextBox(OgreBites::TL_BOTTOM, "Text Box", "Game Log", 500, 120);

    	/*pbar = mTrayMgr->createProgressBar(OgreBites::TL_TOPLEFT,"HealthBar", "Health", 300, 200);
    	pbar->setProgress(1);*/

    	clicks = 0;

    	engine->gfxMgr->mSceneMgr->destroySceneNode("Background");
    	delete rect;
    	mTrayMgr->destroyAllWidgetsInTray(OgreBites::TL_CENTER);
    }
    else if(b->getName() == "QuitButton"){

    	engine->keepRunning = false;
    }
    else if(b->getCaption() == "Spawn Destroyer"){

    	spawnDestroyer();

    	b->setCaption("Spawn Frigate");
    }
    else if(b->getCaption() == "Spawn Frigate"){

    	spawnFrigate();

    	b->setCaption("Spawn Carrier");
    }
    else if(b->getCaption() == "Spawn Carrier"){

    	spawnCarrier();

    	b->setCaption("Spawn Speedboat");

    	infoBox->setScrollPercentage(100);

    }
    else if(b->getCaption() == "Spawn Speedboat"){

    	spawnSpeedboat();

    	b->setCaption("Spawn Alien");


    }
    else if(b->getCaption() == "Spawn Alien"){

    	spawnAlien();

    	mTrayMgr->destroyAllWidgetsInTray(OgreBites::TL_LEFT);

       	Ogre::StringVector shipOptions;
       	shipOptions.push_back("Select SpeedBoat");
       	shipOptions.push_back("Select Destroyer");
        shipOptions.push_back("Select Carrier");
        shipOptions.push_back("Select Frigate");
        shipOptions.push_back("Select Alien Ship");
        mTrayMgr->createLongSelectMenu(OgreBites::TL_TOPRIGHT, "MyMenu", "Select Ship", 300, 5,shipOptions);

        mTrayMgr->createButton(OgreBites::TL_RIGHT, "FireButton", "Fire!");
        rowSlider = mTrayMgr->createThickSlider(OgreBites::TL_RIGHT, "RowSlider", "Row: ", 200, 150, 1, 10, 10);
        colSlider = mTrayMgr->createThickSlider(OgreBites::TL_RIGHT, "ColSlider", "Col: ", 200, 150, 1, 10, 10);

        pbar = mTrayMgr->createProgressBar(OgreBites::TL_TOPLEFT,"HealthBar", "Health", 300, 200);
        pbar->setProgress(1);

        infoBox->setScrollPercentage(100);
    }
}

void UiMgr::itemSelected(OgreBites::SelectMenu *m){
    Ogre::Vector3 pos;


    switch(m->getSelectionIndex() + 1){
    case 1:
    	//engine->entityMgr->CreateEntityOfTypeAtPosition(SpeedBoatType,pos);
    	//mLabel->setCaption("SpeedBoat has Arrived!");
    	pbar->setProgress(engine->gameMgr->playerBoard->speedboatHealth);
    	break;
    case 2:
    	//engine->entityMgr->CreateEntityOfTypeAtPosition(DDG51Type,pos);
    	//mLabel->setCaption("DDG51 has Arrived!");
    	pbar->setProgress(engine->gameMgr->playerBoard->destroyerHealth * .5);
    	break;
    case 3:
    	//engine->entityMgr->CreateEntityOfTypeAtPosition(CarrierType,pos);
    	//mLabel->setCaption("Carrier has Arrived!");
    	pbar->setProgress(engine->gameMgr->playerBoard->carrierHealth * .25);
    	break;
    case 4:
    	//engine->entityMgr->CreateEntityOfTypeAtPosition(FrigateType,pos);
    	//mLabel->setCaption("Frigate has Arrived!");
    	pbar->setProgress(engine->gameMgr->playerBoard->frigateHealth * .5);
    	break;
    case 5:
    	//engine->entityMgr->CreateEntityOfTypeAtPosition(AlienType,pos);
    	//mLabel->setCaption("Alien ship has Arrived!");
    	pbar->setProgress(engine->gameMgr->playerBoard->alienHealth);
    	break;
    default:
    	break;
    }

}

void UiMgr::spawnDestroyer(){

	Ogre::StringConverter converter;

	Ogre::String rowValue = converter.toString(rowSlider->getValue());
	Ogre::String colValue = converter.toString(colSlider->getValue());

	Ogre::Vector3 dPos = Ogre::Vector3(-500, 0, -50);

	dPos.z = dPos.z + 100 * rowSlider->getValue();

	int row = rowSlider->getValue();
	int col = colSlider->getValue();

	if((dPos.x + 100 * colSlider->getValue()) > 400 ){

		dPos.x = 400;
		col = 9;
	}
	else{

		dPos.x = dPos.x + 100 * colSlider->getValue();
	}

	engine->entityMgr->CreateEntityOfTypeAtPosition(DDG51Type , dPos);

	engine->gameMgr->playerBoard->placeDestroyer(row - 1, col - 1);
	engine->gameMgr->AIBoard->placeDestroyer(row - 1, col - 1);

	infoBox->appendText("Your destroyer has been placed at ");
	infoBox->appendText(rowValue);
	infoBox->appendText(" , ");
	infoBox->appendText(colValue);
	infoBox->appendText(". \n");
}

void UiMgr::spawnFrigate(){

	Ogre::StringConverter converter;

	Ogre::String rowValue = converter.toString(rowSlider->getValue());
	Ogre::String colValue = converter.toString(colSlider->getValue());

	Ogre::Vector3 fPos = Ogre::Vector3(-500, 0, -50);

	fPos.z = fPos.z + 100 * rowSlider->getValue();

	int row = rowSlider->getValue();
	int col = colSlider->getValue();

	if((fPos.x + 100 * colSlider->getValue()) > 400 ){

		fPos.x = 400;
		col = 9;
	}
	else{

		fPos.x = fPos.x + 100 * colSlider->getValue();
	}

	engine->entityMgr->CreateEntityOfTypeAtPosition(FrigateType , fPos);

	engine->gameMgr->playerBoard->placeFrigate(row - 1, col - 1);
	engine->gameMgr->AIBoard->placeFrigate(row - 1, col - 1);

	infoBox->appendText("Your frigate has been placed at ");
	infoBox->appendText(rowValue);
	infoBox->appendText(" , ");
	infoBox->appendText(colValue);
	infoBox->appendText(". \n");
}

void UiMgr::spawnCarrier(){

	Ogre::StringConverter converter;

	Ogre::String rowValue = converter.toString(rowSlider->getValue());
	Ogre::String colValue = converter.toString(colSlider->getValue());

	Ogre::Vector3 cPos = Ogre::Vector3(-400, 0, -50);

	cPos.z = cPos.z + 100 * rowSlider->getValue();

	int row = rowSlider->getValue();
	int col = colSlider->getValue();

	if((cPos.x + 100 * colSlider->getValue()) > 300 ){

		cPos.x = 300;
		col = 7;
	}
	else{

		cPos.x = cPos.x + 100 * colSlider->getValue();
	}

	engine->entityMgr->CreateEntityOfTypeAtPosition(CarrierType , cPos);

	engine->gameMgr->playerBoard->placeCarrier(row - 1, col - 1);
	engine->gameMgr->AIBoard->placeCarrier(row - 1, col - 1);

	infoBox->appendText("Your carrier has been placed at ");
	infoBox->appendText(rowValue);
	infoBox->appendText(" , ");
	infoBox->appendText(colValue);
	infoBox->appendText(". \n");
}

void UiMgr::spawnSpeedboat(){

	Ogre::StringConverter converter;

	Ogre::String rowValue = converter.toString(rowSlider->getValue());
	Ogre::String colValue = converter.toString(colSlider->getValue());

	Ogre::Vector3 sPos = Ogre::Vector3(-550, 0, -50);

	sPos.z = sPos.z + 100 * rowSlider->getValue();

	int row = rowSlider->getValue();
	int col = colSlider->getValue();

	if((sPos.x + 100 * colSlider->getValue()) > 450 ){

		sPos.x = 450;
	}
	else{

		sPos.x = sPos.x + 100 * colSlider->getValue();
	}

	engine->entityMgr->CreateEntityOfTypeAtPosition(SpeedBoatType , sPos);

	engine->gameMgr->playerBoard->placeSpeedboat(row - 1, col - 1);
	engine->gameMgr->AIBoard->placeSpeedboat(row- 1, col - 1);

	infoBox->appendText("Your speedboat has been placed at ");
	infoBox->appendText(rowValue);
	infoBox->appendText(" , ");
	infoBox->appendText(colValue);
	infoBox->appendText(". \n");
}

void UiMgr::spawnAlien(){

	Ogre::StringConverter converter;

	Ogre::String rowValue = converter.toString(rowSlider->getValue());
	Ogre::String colValue = converter.toString(colSlider->getValue());

	Ogre::Vector3 aPos = Ogre::Vector3(-550, 0, -50);

	aPos.z = aPos.z + 100 * rowSlider->getValue();

	int row = rowSlider->getValue();
	int col = colSlider->getValue();

	if((aPos.x + 100 * colSlider->getValue()) > 450 ){

		aPos.x = 450;
	}
	else{

		aPos.x = aPos.x + 100 * colSlider->getValue();
	}

	engine->entityMgr->CreateEntityOfTypeAtPosition(AlienType , aPos);

	engine->gameMgr->playerBoard->placeAlien(row - 1, col - 1);
	engine->gameMgr->AIBoard->placeAlien(row - 1, col - 1);

	infoBox->appendText("Your alien ship has been placed at ");
	infoBox->appendText(rowValue);
	infoBox->appendText(" , ");
	infoBox->appendText(colValue);
	infoBox->appendText(". \n");
}
