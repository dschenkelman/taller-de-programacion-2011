#pragma once
#include "sdl/sdl.h"
#include "sdl/SDL_mixer.h"
#include <string>
#include <map>

class SoundManager
{
	static const int AUDIO_RATE = 44100;
	static const Uint16 AUDIO_FORMAT = AUDIO_S8;
	static const int AUDIO_CHANNELS = 2;
	static const int AUDIO_BUFFERS = 2048;
	std::map<std::string, Mix_Chunk*> audioChunks; 
	std::map<std::string, int> audioChannels; 
	std::string backgroundSound;
	std::string eatSound;
	std::string eatGhostSound;
	std::string diesSound;
	std::string wonSound;
	std::string bonusSound;
	std::string collisionSound;
	void loadPacmanSounds(void);
	int lastChannel;
public:
	SoundManager(void);
	std::string getEatPath(void);
	std::string getEatGhostPath(void);
	std::string getBackgroundPath(void);
	std::string getDiesPath(void);
	std::string getWonPath(void);
	std::string getBonusPath(void);
	std::string getCollisionPath(void);
	void loadSound(std::string path);
	void playSound(std::string path, int timesToPlay);
	void pauseSound(std::string path);
	bool isSoundPlaying(std::string path);
	~SoundManager(void);
};
