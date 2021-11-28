#include "SoundManager.h"

SoundManager* SoundManager::s_pInstance = NULL;

SoundManager* SoundManager::Instance()
{
    if (s_pInstance == NULL)
        s_pInstance = new SoundManager();

    return s_pInstance;
}

bool SoundManager::load(std::string fileName, std::string id, sound_type type)
{
    if (type == SOUND_MUSIC)
    {
		if (m_musics[id] != nullptr)
		{
			return true;
		}

        Mix_Music* pMusic = Mix_LoadMUS(fileName.c_str());
        if (pMusic == NULL)
        {
            std::cout << "Could not load music: ERROR - " << Mix_GetError() << std::endl;
            return false;
        }

        m_musics[id] = pMusic;
        return true;
    }
    else if (type == SOUND_SFX)
    {
		if (m_sfxs[id] != nullptr)
		{
			return true;
		}

        Mix_Chunk* pSfx = Mix_LoadWAV(fileName.c_str());
        if (pSfx == NULL)
        {
            std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;
            return false;
        }

        m_sfxs[id] = pSfx;
        return true;
    }

    return false;
}

void SoundManager::playSound(std::string id, int loop)
{
    Mix_PlayChannel(-1, m_sfxs[id], loop);
}

void SoundManager::playMusic(std::string id, int loop)
{
    Mix_PlayMusic(m_musics[id], loop);
    //if (Mix_PlayingMusic() == 0)
    //{
    //    Mix_PlayMusic(m_musics[id], loop);
    //}
    //else
    //{
    //    // if music is played, pause it
    //    Mix_PauseMusic();
    //}
}

void SoundManager::pauseMusic()
{
    if (Mix_PlayingMusic() == 1)
    {
        Mix_PauseMusic();
    }

    /*if (Mix_PausedMusic() == 1)
    {
        Mix_ResumeMusic();
    }*/
}

void SoundManager::stopSound()
{
    Mix_HaltChannel(-1);
}

void SoundManager::stopMusic()
{
    //Mix_PauseMusic();
    Mix_HaltMusic();
}

void SoundManager::clean()
{
    for (auto sfx : m_sfxs)
    {
        Mix_FreeChunk(sfx.second);
    }
    for (auto music : m_musics)
    {
        Mix_FreeMusic(music.second);
    }

    Mix_CloseAudio();

    //s_pInstance = nullptr;
}

SoundManager::SoundManager()
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
}

SoundManager::~SoundManager()
{
    //Mix_CloseAudio();
}
