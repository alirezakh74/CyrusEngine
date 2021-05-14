#pragma once

#include <map>
#include <iostream>
#include <SDL2/SDL_mixer.h>

enum sound_type
{
	SOUND_MUSIC = 0,
	SOUND_SFX = 1
};

class SoundManager
{
public:

	static SoundManager* Instance();

	bool load(std::string fileName, std::string id, sound_type type);
	void playSound(std::string id, int loop);
	void playMusic(std::string id, int loop);

private:

	SoundManager();
	~SoundManager();

	//SoundManager(const SoundManager&);
	//SoundManager& operator=(const SoundManager&);

	static SoundManager* s_pInstance;

	std::map<std::string, Mix_Chunk*> m_sfxs;
	std::map<std::string, Mix_Music*> m_musics;
};

typedef SoundManager TheSoundManager;

