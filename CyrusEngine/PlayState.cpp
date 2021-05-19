#include "PlayState.h"

#include "InputHandler.h"
#include "Game.h"
#include "MainMenuState.h"
//#include "StateParser.h"
#include "PauseState.h"
#include "SoundManager.h"

const std::string PlayState::s_playStateID = "PLAYSTATE";

PlayState::PlayState() : m_pLevel(nullptr)
{
    SoundManager* s_mgr = TheSoundManager::Instance();
    s_mgr->load("assets/bgm1.mp3", "bgm1", sound_type::SOUND_MUSIC);
    s_mgr->playMusic("bgm1", -1);
}

PlayState::~PlayState()
{
}

void PlayState::update()
{
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
    {
        TheGame::Instance()->getGameStateMachine()->changeState(new MainMenuState());
    }
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_BACKSPACE))
    {
        TheGame::Instance()->getGameStateMachine()->pushState(new PauseState());
    }

    /*for (auto gameObject : m_gameObjects)
    {
        gameObject->update();
    }*/
    GameState::update();

    if(m_pLevel != nullptr)
        m_pLevel->update();
}

void PlayState::render()
{
    /*for (auto gameObject : m_gameObjects)
    {
        gameObject->draw();
    }*/
    GameState::render();

    if(m_pLevel != nullptr)
        m_pLevel->render();
}

bool PlayState::onEnter()
{
    GameState::onEnter();

    /*StateParser stateParser;
    stateParser.parseState("assets/test.xml", s_playStateID, &m_gameObjects, &m_textureIDList);*/

    LevelParser levelParser;
    m_pLevel = levelParser.parseLevel("assets/maptest.tmx");

    std::cout << "entering Play State" << std::endl;
    return true;
}

bool PlayState::onExit()
{
    //TheSoundManager::Instance()->stopMusic();
    GameState::onExit();

    std::cout << "exiting Play State" << std::endl;
    return true;
}

std::string PlayState::getStateID() const
{
    return s_playStateID;
}
