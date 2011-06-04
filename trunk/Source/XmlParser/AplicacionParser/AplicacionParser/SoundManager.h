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
	std::string eatSound;
	void loadPacmanSounds(void);
public:
	SoundManager(void);
	std::string getEatSoundPath();
	void loadSound(std::string path);
	void playSound(std::string path, int timesToPlay);
	~SoundManager(void);
};
