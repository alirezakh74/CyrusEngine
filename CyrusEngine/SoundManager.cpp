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
}

SoundManager::SoundManager()
{
    Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
}

SoundManager::~SoundManager()
{
    Mix_CloseAudio();
}
