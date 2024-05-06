#include <iostream>
#include "Map.h"

bool Map::load(const std::string & tileset, sf::Vector2i tileSize, const int * tiles, size_t mapWidth, size_t mapHeight) {
    // checking if file exists and loading tileset from file path
    if (!m_tileset.loadFromFile(tileset)) {
        return false;
    }

    // setting primitive type and resize array for vertices (x6 for two triangles)
    m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    m_vertices.resize(mapWidth * mapHeight * 6);

    for (int i = 0; i < mapWidth; i ++) {
        for (int j = 0; j < mapHeight; j ++) {
            int tileNumber = tiles[i + j * mapHeight];

            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().y / tileSize.y);

            m_tiles.emplace_back(m_tileset, tileSize, i, j);

/*            sf::Vertex * triangles = & m_vertices[(i + j * mapWidth) * 6];

            // so this magic shit is beyond my comprehension
            // yet, I wrote it
            // and can't understand how I made it work
            triangles[0].position = sf::Vector2f(i * tileSize.x / 2 + j * tileSize.x / 2, j * tileSize.y / 2 - i * tileSize.y / 2);
            triangles[1].position = sf::Vector2f(i * tileSize.x / 2 + j * tileSize.x / 2 + tileSize.x / 2, j * tileSize.y / 2 - i * tileSize.y / 2 - tileSize.y / 2);
            triangles[2].position = sf::Vector2f(i * tileSize.x / 2 + j * tileSize.x / 2 + tileSize.x / 2, j * tileSize.y / 2 - i * tileSize.y / 2 + tileSize.y / 2);
            triangles[3].position = sf::Vector2f(i * tileSize.x / 2 + j * tileSize.x / 2 + tileSize.x / 2, j * tileSize.y / 2 - i * tileSize.y / 2 - tileSize.y / 2);
            triangles[4].position = sf::Vector2f(i * tileSize.x / 2 + j * tileSize.x / 2 + tileSize.x / 2, j * tileSize.y / 2 - i * tileSize.y / 2 + tileSize.y / 2);
            triangles[5].position = sf::Vector2f(i * tileSize.x / 2 + j * tileSize.x / 2 + tileSize.x, j * tileSize.y / 2 - i * tileSize.y / 2);

            // TODO: fix texture coordinates (somehow managed to flip them)
            triangles[0].texCoords = sf::Vector2f(0, tileSize.y / 2);
            triangles[1].texCoords = sf::Vector2f(tileSize.x / 2, tileSize.y);
            triangles[2].texCoords = sf::Vector2f(tileSize.x / 2, 0);
            triangles[3].texCoords = sf::Vector2f(tileSize.x / 2, tileSize.y);
            triangles[4].texCoords = sf::Vector2f(tileSize.x / 2, 0);
            triangles[5].texCoords = sf::Vector2f(tileSize.x, tileSize.y / 2);
*/



        }
    }
    return true;
}

//void Map::draw(sf::RenderTarget & target, const sf::RenderStates & states) const {
//    sf::RenderStates newStates = states;
//
//    newStates.transform *= getTransform();
//
//    newStates.texture = & m_tileset;
//
//    target.draw(m_vertices, newStates);    // TODO: restore newStates in function
//}

sf::Vector2f Map::getCenterCoords() {
    return m_centerCoords;
}

void Map::draw(sf::RenderTarget & target) {
    for (Tile & tile: m_tiles) {
        target.draw(tile);
    }
}

void Map::isMapClicked(const sf::Vector2i & mousePos) {
    bool isInside = false;
    for (Tile & tile: m_tiles) {
        if (tile.isTileClicked(mousePos)) {
            std::cout << tile.getIndex().x << ' ' << tile.getIndex().y << std::endl;
//            return isInside;
        }
    }
//    return isInside;
}
