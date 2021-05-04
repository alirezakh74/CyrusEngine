#pragma once

#include "Level.h"
#include "tinyxml.h"

#include <vector>

struct Tileset;
class Level;

class LevelParser
{
public:

	Level* parseLevel(const char* levelFile);

private:

	void parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets);
	void parseTileLayer(TiXmlElement* pTileRoot, std::vector<Layer*>* pLayers, const std::vector<Tileset>* pTilesets);

	void parseTextures(TiXmlElement* pTextureRoot);
	void parseObjectLayers(TiXmlElement* pObjectElement, std::vector<Layer*>* pLayers);

	int m_tileSize;
	int m_width; // width of map
	int m_height; // height of map
};

