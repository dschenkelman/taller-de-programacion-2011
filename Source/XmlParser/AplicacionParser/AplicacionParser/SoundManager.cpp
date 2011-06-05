#include "StdAfx.h"
#include "SoundManager.h"
#include <sstream>
#include <string>

using namespace std;

SoundManager::SoundManager(void) : lastChannel(0), 
eatSound("sounds/eat.wav"), eatGhostSound("sounds/eatGhost.wav"),
backgroundSound("sounds/siren.wav"), diesSound("sounds/dies.wav"), wonSound("sounds/won.wav")
{
	if(Mix_OpenAudio(AUDIO_RATE, AUDIO_FORMAT, AUDIO_CHANNELS, AUDIO_BUFFERS) != 0) 
	{
		stringstream msg;
		msg << "Unable to initialize audio" << Mix_GetError();
		throw std::exception(msg.str().c_str());
	}

	this->loadPacmanSounds();
}

void SoundManager::loadPacmanSounds()
{
	this->loadSound(this->backgroundSound);
	this->loadSound(this->eatSound);
	this->loadSound(this->eatGhostSound);
	this->loadSound(this->diesSound);
	this->loadSound(this->wonSound);
}

std::string SoundManager::getEatPath(void)
{
	return this->eatSound;
}

std::string SoundManager::getEatGhostPath(void)
{
	return this->eatGhostSound;
}

std::string SoundManager::getBackgroundPath(void)
{
	return this->backgroundSound;
}

std::string SoundManager::getDiesPath(void)
{
	return this->diesSound;
}

std::string SoundManager::getWonPath(void)
{
	return this->wonSound;
}

void SoundManager::loadSound(string path)
{
	Mix_Chunk* audioChunk = NULL;
 
	audioChunk = Mix_LoadWAV(path.c_str());
	if(audioChunk == NULL) 
	{
		stringstream msg;
		msg << "Unable to load WAV file:" << Mix_GetError();
		throw std::exception(msg.str().c_str());
	}

	this->audioChunks[path] = audioChunk;
	this->audioChannels[path] = this->lastChannel;

	this->lastChannel++;
}

void SoundManager::playSound(string path, int timesToPlay)
{
	int channel = -1;

	if (this->audioChannels.find(path) != this->audioChannels.end())
	{
		channel = this->audioChannels[path];
	}

	if (channel > -1 && Mix_Playing(channel))
	{
		return;
	}
 
	Mix_Chunk* audioChunk = this->audioChunks[path];

	channel = Mix_PlayChannel(channel, audioChunk, timesToPlay - 1);
	if(channel == -1) 
	{
		stringstream msg;
		msg << "Unable to play WAV file:" << Mix_GetError();
		throw std::exception(msg.str().c_str());
	}

	this->audioChannels[path] = channel;
}


void SoundManager::pauseSound(string path)
{
	int channel = this->audioChannels[path];
	Mix_HaltChannel(channel);
}

bool SoundManager::isSoundPlaying(string path)
{
	int channel = this->audioChannels[path];
	
	// playing is 1, not playing 0
	return Mix_Playing(channel) == 1;
}

SoundManager::~SoundManager(void)
{
	std::map<std::string, Mix_Chunk*>::iterator iter;
	for (iter = this->audioChunks.begin(); iter != this->audioChunks.end(); iter++) 
	{
		Mix_FreeChunk(iter->second);
	}

	Mix_CloseAudio();
}

