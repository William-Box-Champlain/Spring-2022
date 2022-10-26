#include "Audio.h"

Audio::Audio()
{
	//init sounds
	SDL_Init(SDL_INIT_AUDIO);

	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 4096;

	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Coouln't init audio: %s", Mix_GetError());
		exit(-1);
	}
}

Audio::~Audio()
{
	SDL_Quit();
}

void Audio::addSound(const char* filename)
{
	Mix_Chunk* tmpChunk = Mix_LoadWAV(filename);
	if (tmpChunk != nullptr)
	{
		mAudioFiles.push_back(tmpChunk);
		std::cout << (mAudioFiles.size() - 1) << ". Loaded sound path: " << filename << endl;
	}
}

void Audio::playSound(const int sound) const
{
	if (sound > mAudioFiles.size() - 1)
	{
		std::cout << "Error: sound outside of range" << endl;
	}
	else
	{
		Mix_PlayChannel(-1, mAudioFiles[sound], 0);

		std::cout << "Playing sound: " << sound << endl;
	}
}
