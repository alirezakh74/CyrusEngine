#pragma once

#include "Layer.h"

#include "Vector2D.h"
#include <vector>
#include "Level.h"

class TileLayer : public Layer
{
public:

	TileLayer(int tileSize, const std::vector<Tileset>& tilesets);
	~TileLayer();

	virtual void update() override;
	virtual void render() override;

	void setTileIDs(const std::vector<std::vector<int>>& data)
	{
		m_tileIDs = data;
	}

	void setTileSize(int tileSize) { m_tileSize = tileSize; }

	Tileset getTilesetByID(int tileID);

	void setColumns(int cols) { m_numColumns = cols; }
	void setRows(int rows) { m_numRows = rows; }
	void setNumColumnsOfLevel(int columns) { m_numColumnsOfLevel = columns; }
	void setNumRowsOfLevel(int rows) { m_numRowsOfLevel = rows; }

private:

	int m_numColumns;
	int m_numRows;
	int m_tileSize;
	int m_numColumnsOfLevel;
	int m_numRowsOfLevel;


	Vector2D m_position;
	Vector2D m_velocity;

	bool firstEnter = false;

	const std::vector<Tileset>& m_tilesets;
	std::vector < std::vector<int>> m_tileIDs;
};

