#include "LevelParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "TileLayer.h"
#include "ObjectLayer.h"
#include "GameObjectFactory.h"

Level* LevelParser::parseLevel(const char* levelFile)
{
    // create a tiny xml file and load the map file
    TiXmlDocument levelDocument;
    levelDocument.LoadFile(levelFile);

    // create our level
    Level* pLevel = new Level();

    // get the root node from xml map file
    TiXmlElement* pRoot = levelDocument.RootElement();

    pRoot->Attribute("width", &m_width);
    pRoot->Attribute("height", &m_height);
    pRoot->Attribute("tilewidth", &m_tileSize);

    // parse the textures
    for (TiXmlElement* properties = pRoot->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement())
    {
        if (properties->Value() == std::string("properties"))
        {
            for (TiXmlElement* property = properties->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
            {
                parseTextures(property);
            }
        }
    }

    // parse the tilesets
    for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        std::cout << "Value is: " << e->Value() << " Adress: " << e << "\n";
        if (e->Value() == std::string("tileset"))
        {
            parseTilesets(e, pLevel->getTilesets());
        }
    }

    // parse any object layer
    for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL;  e = e->NextSiblingElement())
    {
        //std::cout << "Value is: " << e->Value() << " Adress: " << e << "\n";
        if (e->Value() == std::string("objectgroup") || e->Value() == std::string("layer"))
        {
            if (e->FirstChildElement()->Value() == std::string("object"))
            {
                parseObjectLayers(e, pLevel->getLayers());
            }
            else if (e->FirstChildElement()->Value() == std::string("data"))
            {
                parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets());
            }
        }
    }

    return pLevel;
}

void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets)
{
    // first add tileset to texture manager
    TheTextureManager::Instance()->load(pTilesetRoot->FirstChildElement()->Attribute("source"),
        pTilesetRoot->Attribute("name"), TheGame::Instance()->getRenderer());

    // create a tileset object
    Tileset tileset = { 0, 0, 0, 0, 0, 0, 0, 0, " " };
    pTilesetRoot->FirstChildElement()->Attribute("width", &tileset.width);
    pTilesetRoot->FirstChildElement()->Attribute("height", &tileset.height);
    pTilesetRoot->Attribute("width", &tileset.width);
    pTilesetRoot->Attribute("firstgid", &tileset.firstGridID);
    pTilesetRoot->Attribute("tilewidth", &tileset.tileWidth);
    pTilesetRoot->Attribute("tileheight", &tileset.tileHeight);
    pTilesetRoot->Attribute("spacing", &tileset.spacing);
    pTilesetRoot->Attribute("margin", &tileset.margin);
    pTilesetRoot->Attribute("columns", &tileset.numColumns);
    tileset.name = pTilesetRoot->Attribute("name");

    pTilesets->push_back(tileset);
}

void LevelParser::parseTileLayer(TiXmlElement* pTileRoot, std::vector<Layer*>* pLayers, const std::vector<Tileset>* pTilesets)
{
    TileLayer* pTileLayer = new TileLayer(m_tileSize, *pTilesets);

    //pTileLayer->setColumns(m_width);
    //pTileLayer->setRows(m_height);
    pTileLayer->setNumColumnsOfLevel(m_width);
    pTileLayer->setNumRowsOfLevel(m_height);

    std::vector<std::vector<int>> data;

    std::string ids;
    TiXmlElement* pDataNode = nullptr;

    for (TiXmlElement* e = pTileRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("data"))
        {
            pDataNode = e;
        }
    }

    if (pDataNode == nullptr)
    {
        try {
            //std::cout << "data problem \n";
            throw std::runtime_error("Data Node problem");
        }
        catch (std::runtime_error e)
        {
            std::cout << "Run time error: " << e.what();
            assert(false);
            terminate;
        }
    }

    for (TiXmlNode* e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling())
    {
        TiXmlText* text = e->ToText();
        ids = text->Value();
    }

    //auto size = m_width * m_height * sizeof(int);
    //std::vector<unsigned> gids(size);

    std::vector<std::string> vIds;
    std::stringstream ss(ids);

    while (ss.good())
    {
        std::string substr;
        std::getline(ss, substr, ',');
        vIds.push_back(substr);
    }



    std::vector<int> layerRow(m_width);

    for (int j = 0; j < m_height; ++j)
    {
        data.push_back(layerRow);
    }

    for (int rows = 0; rows < m_height; rows++)
    {
        for (int cols = 0; cols < m_width; cols++)
        {
            /*if (ids.length() <= (rows * m_width + cols))
            {
                std::cout << "ids length is :" << ids << " and index is:"
                    << rows * m_width + cols << "\n";
            }*/
            
            //std::cout << "index of ids is : " << rows * m_width + cols << "\n";
            //std::cout << "data size is : " << data.size() << " data capacity is : " << data.capacity() << "\n";

            //char t = ids[rows * m_width + cols];

            std::stringstream ss2(vIds[rows * m_width + cols]);
            int x = 0;
            ss2 >> x;

            data[rows][cols] = x;

            // for under code include stdlib.h
            //data[rows][cols] = atoi(ss2.str().c_str());
        }
    }

    pTileLayer->setTileIDs(data);
    pLayers->push_back(pTileLayer);
}

void LevelParser::parseTextures(TiXmlElement* pTextureRoot)
{
    std::string value = pTextureRoot->Attribute("value");
    std::string name = pTextureRoot->Attribute("name");
    TheTextureManager::Instance()->load(pTextureRoot->Attribute("value"), pTextureRoot->Attribute("name"), TheGame::Instance()->getRenderer());
}

void LevelParser::parseObjectLayers(TiXmlElement* pObjectElement, std::vector<Layer*>* pLayers)
{
    // create an object layer
    ObjectLayer* pObjectLayer = new ObjectLayer();

    std::cout << pObjectElement->Value() << "\n";

    for (TiXmlElement* e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        std::cout << e->Value() << "\n";

        if (e->Value() == std::string("object"))
        {
            int x, y, width, height, numFrames, callbackID = 0, animSpeed = 0;
            std::string textureID;

            // get the initial nodes type, x and y
            e->Attribute("x", &x);
            e->Attribute("y", &y);
            std::string type = e->Attribute("type");
            GameObject* pGameObject = TheGameObjectFactory::Instance()->create(e->Attribute("type"));

            // get the property values
            for (TiXmlElement* properties = e->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement())
            {
                if (properties->Value() == std::string("properties"))
                {
                    for (TiXmlElement* property = properties->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
                    {
                        if (property->Value() == std::string("property"))
                        {
                            if (property->Attribute("name") == std::string("numFrames"))
                            {
                                property->Attribute("value", &numFrames);
                            }
                            else if (property->Attribute("name") == std::string("textureHeight"))
                            {
                                property->Attribute("value", &height);
                            }
                            else if (property->Attribute("name") == std::string("textureWidth"))
                            {
                                property->Attribute("value", &width);
                            }
                            else if (property->Attribute("name") == std::string("textureID"))
                            {
                                textureID = property->Attribute("value");
                            }
                            else if (property->Attribute("name") == std::string("callbackID"))
                            {
                                property->Attribute("value", &callbackID);
                            }
                            else if (property->Attribute("name") == std::string("animSpeed"))
                            {
                                property->Attribute("value", &animSpeed);
                            }
                        }
                    }
                }
            }

            pGameObject->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed)));
            pObjectLayer->getGameObjects()->push_back(pGameObject);
        }
    }
    pLayers->push_back(pObjectLayer);
}
