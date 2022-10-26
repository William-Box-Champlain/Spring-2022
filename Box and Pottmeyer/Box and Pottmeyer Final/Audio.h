#pragma once
#include <iostream>
#include <Trackable.h>
#include <SDL.h>
//#include <SDL_audio.h>
#include <SDL_mixer.h>
#include <vector>

using namespace std;

class Audio : public Trackable
{
public:
	Audio();
	~Audio();

	void addSound(const char* filename);
	void playSound(const int sound) const;

private:
	vector<Mix_Chunk*>mAudioFiles;
};