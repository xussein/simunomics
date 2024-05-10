#include "Map.h"

bool Map::load(const std::string & tileset, sf::Vector2i tileSize, const int * tiles, size_t mapWidth, size_t mapHeight) {
    // checking if file exists and loading tileset from file path
    if (!m_tileset.loadFromFile(tileset)) {
        return false;   // TODO: throw exception
    } else {
        // Parsing texture file into separate textures and storing them inside vector
        for (int i = 0; i < tilesetXCount; i ++) {      // TODO: consider removing magic number 4 and creating (or calculating) tile number
            for (int j = 0; j < tilesetYCount; j ++) {
                sf::Texture tileTexture;
                sf::IntRect textureRect = {i * tileWidth, j * tileHeight, i * tileWidth + tileWidth, j * tileHeight + tileHeight};
                tileTexture.loadFromFile(tileset, textureRect);
                m_tilesTextures.push_back(tileTexture);
            }
        }
    }

    for (int i = 0; i < mapWidth; i ++) {
        for (int j = 0; j < mapHeight; j ++) {
            int tileNumber = tiles[i + j * mapHeight];
            m_tiles.emplace_back(m_tilesTextures[tileNumber], tileSize, i, j);
        }
    }
    return true;
}

sf::Vector2f Map::getCenterCoords() {
    return m_centerCoords;
}

void Map::draw(sf::RenderTarget & target) {
    for (Tile & tile: m_tiles) {
        target.draw(tile);
    }
}

void Map::isMapClicked(const sf::Vector2f & mousePos) {
    for (Tile & tile: m_tiles) {
        if (tile.isTileClicked(mousePos)) {
#if DEBUG == 1
            std::cout << tile.getIndex().x << ' ' << tile.getIndex().y << std::endl;
#endif
        }
    }
}

void Map::move(sf::View & view, sf::Vector2f offset) {
    view.move(offset);
}
