#include "GameObjectFactory.h"

GameObjectFactory* GameObjectFactory::s_instance = NULL;

GameObjectFactory* GameObjectFactory::Instance()
{
    if (s_instance == NULL)
    {
        s_instance = new GameObjectFactory();
    }

    return s_instance;
}

GameObjectFactory::GameObjectFactory()
{
}

GameObjectFactory::~GameObjectFactory()
{
    s_instance = NULL;
}
