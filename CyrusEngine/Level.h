#pragma once
#include <string>
#include <vector>

#include "Layer.h"
#include "LevelParser.h"

struct Tileset
{
	int firstGridID;
	int tileWidth;
	int tileHeight;
	int width;
	int height;
	int numColumns;
	int spacing;
	int margin;

	std::string name;
};

class Level
{
public:

	Level();
	~Level();

	void update();
	void render();

	void clear();

	std::vector<Tileset>* getTilesets() { return &m_tilesets; }
	std::vector<Layer*>* getLayers() { return &m_layers; }

private:

	/*Level();
	~Level();*/

	std::vector<Tileset> m_tilesets;
	std::vector<Layer*> m_layers;

	friend class LevelParser;
};

