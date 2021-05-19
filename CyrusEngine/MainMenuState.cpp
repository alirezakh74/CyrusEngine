#include "MainMenuState.h"

#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "ImageObject.h"
#include "PlayState.h"
#include "InputHandler.h"
#include "StateParser.h"
#include "SoundManager.h"

const std::string MainMenuState::s_mainMenuStateID = "MAINMENUSTATE";

MainMenuState::MainMenuState()
{
    SoundManager* s_mgr = SoundManager::Instance();
    s_mgr->load("assets/menu.mp3", "menu", sound_type::SOUND_MUSIC);
    s_mgr->playMusic("menu", -1);
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::update()
{
    /*if (!m_gameObjects.empty() && !m_bExitingFromState)
    {
        for (int i = 0; i < m_gameObjects.size(); ++i)
        {
            m_gameObjects[i]->update();
        }
    }*/

    GameState::update();
}

void MainMenuState::render()
{
    /*if (!m_gameObjects.empty() && !m_bExitingFromState)
    {
        for (int i = 0; i < m_gameObjects.size(); ++i)
        {
            m_gameObjects[i]->draw();
        }
    }*/

    GameState::render();
}

bool MainMenuState::onEnter()
{
    /*if (!TheTextureManager::Instance()->load("assets/playFa.png", "play", TheGame::Instance()->getRenderer()))
    {
        return false;
    }

    if (!TheTextureManager::Instance()->load("assets/exitFa.png", "exit", TheGame::Instance()->getRenderer()))
    {
        return false;
    }

    if (!TheTextureManager::Instance()->load("assets/man.png", "ali", TheGame::Instance()->getRenderer()))
    {
        return false;
    }*/

    //m_bExitingFromState = false;
    GameState::onEnter();

    StateParser stateParser;
    stateParser.parseState("assets/test.xml", s_mainMenuStateID, &m_gameObjects, &m_textureIDList);

    m_callbacks.push_back(0);
    m_callbacks.push_back(s_menuToPlay);
    m_callbacks.push_back(s_exitFromMenu);

    setCallbacks(m_callbacks);

    std::cout << "entering Main Menu State" << std::endl;
    return true;
}

bool MainMenuState::onExit()
{
    //for (int i = 0; i < m_gameObjects.size(); ++i)
    //{
    //    m_gameObjects[i]->clean();
    //    //delete m_gameObjects[i];
    //}

    //m_gameObjects.clear();

    ///*TheTextureManager::Instance()->clearFromTextureMap("play");
    //TheTextureManager::Instance()->clearFromTextureMap("exit");
    //TheTextureManager::Instance()->clearFromTextureMap("ali");*/

    //for (int i = 0; i < m_textureIDList.size(); ++i)
    //{
    //    TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    //}

    //m_bExitingFromState = true;

    //TheSoundManager::Instance()->stopMusic();
    GameState::onExit();

    std::cout << "exiting Main Menu State" << std::endl;
    return true;
}

std::string MainMenuState::getStateID() const
{
    return s_mainMenuStateID;
}

void MainMenuState::setCallbacks(const std::vector<Callback> &callbacks)
{
    for (int i = 0; i < m_gameObjects.size(); ++i)
    {
        if (dynamic_cast<MenuButton*>(m_gameObjects[i]))
        {
            MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
            pButton->setCallback(m_callbacks[pButton->getCallbackID()]);
        }
    }
}

void MainMenuState::s_menuToPlay()
{
    TheGame::Instance()->getGameStateMachine()->changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu()
{
    TheGame::Instance()->quit();
}
