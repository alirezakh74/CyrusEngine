#include "StateParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameObjectFactory.h"

bool StateParser::parseState(const char* stateFile, std::string stateID, std::vector<GameObject*>* pObjects, std::vector<std::string>* pTextureID)
{
    //create xml file
    TiXmlDocument xmlDoc;

    if (!xmlDoc.LoadFile(stateFile))
    {
        std::cerr << xmlDoc.ErrorDesc() << ": " << stateFile << "\n";
        return false;
    }

    TiXmlElement* pRoot = xmlDoc.RootElement(); // <STATES>

    //assert(pRoot != NULL);

    TiXmlElement* pStateRoot = 0;

    //find state root that we need and passed by StateID argument
    for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if (e->Value() == stateID)
        {
            pStateRoot = e;
        }
    }

    //assert(pStateRoot != NULL);
    if (pStateRoot == NULL)
    {
        std::cout << "there is no element name as " << stateID << "\n";
        return false;
    }

    TiXmlElement* pTextureRoot = 0;

    //find texture root, and then we can use it for parse child texuture elements
    for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("TEXTURES"))
        {
            pTextureRoot = e;
        }
    }

    // parse textures
    parseTextures(pTextureRoot, pTextureID);

    // find OBJECTS element
    TiXmlElement* pObjectRoot = 0;

    for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("OBJECTS"))
        {
            pObjectRoot = e;
        }
    }

    // parse objects
    parseObjects(pObjectRoot, pObjects);

    // parse process done
    return true;
}

void StateParser::parseObjects(TiXmlElement* pStateRoot, std::vector<GameObject*> *pObjects)
{
    for(TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        int x, y, width, height, numFrames, animSpeed, callbackID;

        std::string typeObject = e->Attribute("type");
        std::string textureID = e->Attribute("textureID");

        e->Attribute("x", &x);
        e->Attribute("y", &y);
        e->Attribute("width", &width);
        e->Attribute("height", &height);
        e->Attribute("numFrames", &numFrames);
        e->Attribute("animSpeed", &animSpeed);
        e->Attribute("callbackID", &callbackID);

        GameObject* pGameObject = TheGameObjectFactory::Instance()->create(typeObject);
        pGameObject->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed)));
        pObjects->push_back(pGameObject);
    }
}

void StateParser::parseTextures(TiXmlElement* pStateRoot, std::vector<std::string> *pTextureIDs)
{
    for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        std::string filenameAttribue = e->Attribute("filename");
        std::string idAttribue = e->Attribute("ID");
        pTextureIDs->push_back(idAttribue);
        TheTextureManager::Instance()->load(filenameAttribue, idAttribue, TheGame::Instance()->getRenderer());
    }
}
