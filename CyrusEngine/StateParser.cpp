#include "StateParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameObjectFactory.h"
#include "stdio.h"
//#include "android_fopen.h"

bool StateParser::parseState(const char* stateFile, std::string stateID, std::vector<GameObject*>* pObjects, std::vector<std::string>* pTextureID)
{
	//create xml file
	// create the XML document
	TiXmlDocument xmlDoc;

	// load the state file
	//if(!xmlDoc.Parse(file_contents, 0, TIXML_ENCODING_UTF8))
	/*if(!xmlDoc.LoadFile(file_contents))
	{
		std::string str = xmlDoc.ErrorDesc();
	}*/

#if defined(ANDROID)
	char* file_contents = NULL;
	if (read_text(stateFile, &file_contents) != true)
	{
		return false;
	}
	xmlDoc.Parse(file_contents);
	delete[] file_contents;
#elif defined(__WIN32__)
	if (!xmlDoc.LoadFile(stateFile))
	{
		std::cout << "load state: " << xmlDoc.ErrorDesc() << "\n";
	}
#endif

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

	//fclose(android_file);

	// parse process done
	return true;
}

#if defined(ANDROID)
bool StateParser::read_text(const char* source_file, char** destination)
{
	// Open the file
	SDL_RWops* file;
	file = SDL_RWFromFile(source_file, "r+b");

	size_t file_length = SDL_RWseek(file, 0, SEEK_END);
	(*destination) = new char[file_length + 1]; // allow an extra character for '\0'

	// Reset seek to beginning of file and read text
	SDL_RWseek(file, 0, SEEK_SET);
	/*int n_blocks = SDL_RWread(file, (*destination), 1, file_length);
	if (n_blocks <= 0)
	{

	}*/
	SDL_RWclose(file);

	(*destination)[file_length + 1] = '\0';

	return true;
}
#endif

void StateParser::parseObjects(TiXmlElement* pStateRoot, std::vector<GameObject*>* pObjects)
{
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
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

void StateParser::parseTextures(TiXmlElement* pStateRoot, std::vector<std::string>* pTextureIDs)
{
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		std::string filenameAttribue = e->Attribute("filename");
		std::string idAttribue = e->Attribute("ID");
		pTextureIDs->push_back(idAttribue);
		TheTextureManager::Instance()->load(filenameAttribue, idAttribue, TheGame::Instance()->getRenderer());
	}
}
