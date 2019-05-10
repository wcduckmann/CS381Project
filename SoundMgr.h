/*
 * SoundMgr.h
 *
 *  Created on: Oct 30, 2013
 *      Author: sushil
 */

#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_


#include <iostream>
#include <cstring>
#include <vector>

#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include <OgreFrameListener.h>

#include <wave.h>
#include <al.h>
#include <alc.h>
#include <Mgr.h>

class Entity381;

namespace OgreSND {
    const int soundPerEnt = 3;      // max different sounds to randomly choose per entity
	const int maxAudioBuffers = 63; // + 1 for background music
	const int maxAudioSources = 15; // + 1 for background music
	const std::string backgroundMusicFilename = "data/watercraft/sounds/backgroundMusic.wav";
	///home/sushil/workspace/fe1/


	typedef struct {
		ALuint source;
		bool   inUse;
	} SourceInfo;

	typedef struct {
		ALuint buffer;
		std::string bufferFilename;
		WaveInfo *wave;
	} BufferInfo;

	class SoundMgr : public Mgr , public Ogre::FrameListener {
	private:
		//OgreGFX::GraphicsInteractionManager *gim;
		ALCdevice  *device;
		ALCcontext *context;
		ALfloat position[3];
		ALfloat velocity[3];
		ALfloat orientation[6];

		//Buffers and Sources indices

		SourceInfo sourceInfo[maxAudioSources];
		BufferInfo  bufferInfo[maxAudioBuffers];

		//Special treatment for background source and buffer
		ALuint backgroundMusicBuffer, backgroundMusicSource;
                ALuint battleSoundSource; //default battle sound source, not entity specific
		WaveInfo *backgroundWaveInfo;
		//unsigned int scvId;
                //unsigned int soundDictionary[FastEcslent::NENTITYTYPES];
                std::vector <std::string> sourceDictionary;
                
                //First dimension holds types and inner one holds different sounds for that type
                //int creationSoundsDictionary[FastEcslent::NENTITYTYPES][soundPerEnt];
                int selectionSoundsDictionary[6][soundPerEnt];
                //int battleSoundsDictionary[FastEcslent::NENTITYTYPES][soundPerEnt];

		//other formats with time
		std::string getFQFNFromFilename(std::string filename);
		int getBufferId(std::string filename);
		//int firstIndexNotInUse(bool inUse[], int size);
		int getEmptySourceIndex();
		bool resetSource(ALuint sid);
                
                bool isEnabled;

	public:
		SoundMgr(Engine* eng);
		~SoundMgr();
		//default methods
		void initialize();
		void crosslink();
		void init();
		void loadLevel();
		void tick(double dtime);
		void releaseLevel();
		void cleanup ();
                
                void enable();
                void disable();

	    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	    virtual bool frameStarted(const Ogre::FrameEvent& evt);
	    virtual bool frameEnded(const Ogre::FrameEvent& evt);


		void printAudioDevices(const ALCchar *devices);
		int printError(const char *ermsg);
		inline ALenum toALFormat(short channels, short samples);
		void syncListenerToCamera();
                void attachSelectedNodeToSoundIndex(Entity381* ent, unsigned int index);
                //bool playEntityBornSound(FastEcslent::EntityType et, OgreGFX::GFXNode *gfxNode);
                //bool playExplosionSound(FastEcslent::EntityType et, OgreGFX::GFXNode *gfxNode);
                //bool playExplosionSound(OgreGFX::GFXNode *gfxNode);
                bool playSelectionSound(Entity381 * et);
                
		//specific for sound managers everywhere
		bool loadAudio(std::string filename, int sid);
		//bool loadAndBindAudio(std::string filename, bool loop, ALuint &audioId); //return +ive audioId or -ive error code
		bool loadStartBackground();
		bool stopBackground();
		bool pauseBackground();
		bool resumeBackground();

		//bool registerCreate(FastEcslent::EntityType et, std::string filename);
                bool registerSelection(Entity381 * et, std::string filename);
                //bool registerBattleSound(FastEcslent::EntityType et, std::string filename);
                //bool isEntityShip(FastEcslent::EntityType et);
                bool initWatercraftSounds();
                
		bool reserveAudio(std::string filename, bool loop, unsigned int &alSourceInfoIndex);
		bool releaseSource(ALuint audioId);
		bool releaseSourceIndex(int sid);

        // Returns true if the audio is started from the beginning
        // false if error or if already playing and forceRestart is false
        bool playAudio(ALuint audioId, bool forceRestart );
        bool playAudio(ALuint audioId);
        bool playAudioSourceIndex(int sid, bool forceRestart );
        bool playAudioSourceIndex(int sid);
        
        void copySoundState();
        
        bool isAudioPlaying(ALuint audioId);
        bool stopAudio(ALuint audioID );
        bool stopAllAudio( void );
        bool stopAudioSourceIndex(int sid);

        bool pauseAudio(ALuint audioID );
        bool pauseAllAudio( void );
        bool pauseAudioSourceIndex(int sid );

        bool resumeAudio(ALuint audioID );
        bool resumeAllAudio( void );
        bool resumeAudioSourceIndex(int sid);

        bool setSoundPosition(ALuint audioID, Ogre::Vector3 position );

        bool setSoundDisposition(ALuint audioID, Ogre::Vector3 position, Ogre::Vector3 velocity, Ogre::Vector3 direction );

        bool setSound(ALuint audioID, Ogre::Vector3 position,
            Ogre::Vector3 velocity, Ogre::Vector3 direction, float maxDistance,
            bool playNow, bool forceRestart, float minGain );

        bool setListenerDisposition( Ogre::Vector3 position, Ogre::Vector3 velocity, Ogre::Quaternion orientation );

	};
        
        //double volume;
        


}


#endif /* SOUNDMANAGER_H_ */
