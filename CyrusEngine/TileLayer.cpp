#include "TileLayer.h"
#include "globals.h"
#include "TextureManager.h"
#include "Game.h"

TileLayer::TileLayer(int tileSize, const std::vector<Tileset>& tilesets)
    : m_tileSize(tileSize), m_tilesets(tilesets), m_numColumns(0), m_numRows(0)
    , m_position(0, 0), m_velocity(0, 0), m_numColumnsOfLevel(0), m_numRowsOfLevel(0)
{
    m_numColumns = screen::width / m_tileSize + 1;
    m_numRows = screen::height / m_tileSize + 5;
    //m_numColumns = 20;
    //m_numRows = 15;
    //m_velocity.setX(0);
    m_velocity.setY(-10);
}

void TileLayer::update()
{
    m_position += m_velocity;

    if (m_position.getY() <= (m_numRowsOfLevel * m_tileSize - (m_numRows * m_tileSize)))
    {
        //m_velocity.setY(-10);
    }
    if (m_position.getY() <= 0)
    {
        //m_velocity.setY(10);
    }

    //if (m_position.getX() >= (m_numColumnsOfLevel * m_tileSize - (m_numColumns * m_tileSize)))
    //{
    //    //m_position.setX(0);
    //    m_velocity.setX(0);
    //}
    //if (m_position.getX() <= 0)
    //{
    //    m_velocity.setX(0);
    //}
}

void TileLayer::render()
{

    if (!firstEnter)
    {
        firstEnter = !firstEnter;
        // set position to bottom of map
        m_position.setY(m_numRowsOfLevel * m_tileSize - m_numRows * m_tileSize);
        m_velocity.setY(-10);
    }

    int x = 0, y = 0, x2 = 0, y2 = 0;

    x = m_position.getX() / m_tileSize;
    y = m_position.getY() / m_tileSize;

    if (m_velocity.getY() != 0 && y >= m_numRowsOfLevel - m_numRows)
    {
        m_velocity.setY(-10);
    }
    if (m_velocity.getY() != 0 && y <= 1)
    {
        m_velocity.setY(10);
    }

    x2 = /*m_position.getX() +*/ int(m_position.getX()) % m_tileSize;
    y2 = /*m_position.getX() +*/ int(m_position.getY()) % m_tileSize;

    /*x2 = x2 & m_tileSize;
    y2 = y2 & m_tileSize;*/

    for (int i = 0; i < m_numRows; i++)
    {
        for (int j = 0; j < m_numColumns; j++)
        {
            int id = m_tileIDs[i + y][j + x];
            if (id == 0)
            {
                continue;
            }

            Tileset tileset = getTilesetByID(id);

            id--;

            TheTextureManager::Instance()->drawTile(tileset.name, tileset.margin, tileset.spacing,
                (j * m_tileSize) - x2, (i * m_tileSize) - y2, m_tileSize,
                m_tileSize, (id - (tileset.firstGridID - 1)) /
                tileset.numColumns, (id - (tileset.firstGridID - 1)) %
                tileset.numColumns, TheGame::Instance()->getRenderer());
        }
    }
}

Tileset TileLayer::getTilesetByID(int tileID)
{
    for (int i = 0; i < m_tilesets.size(); i++)
    {
        if (i + 1 <= m_tilesets.size() - 1)
        {
            if (tileID >= m_tilesets[i].firstGridID && tileID < m_tilesets[i + 1].firstGridID)
            {
                return m_tilesets[i];
            }
        }
        else
        {
            return m_tilesets[i];
        }
    }

    std::cout << "did not find tileset, returning empty tileset\n";
    Tileset t;
    return t;
}
