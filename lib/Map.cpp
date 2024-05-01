#include <iostream>
#include "Map.h"

bool Map::load(const std::string & tileset, sf::Vector2i tileSize, const int * tiles, unsigned int mapWidth,
               unsigned int mapHeight) {
    // checking if file exists
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

            sf::Vertex * triangles = & m_vertices[(i + j * mapWidth) * 6];

//            triangles[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
//            triangles[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
//            triangles[2].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
//            triangles[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
//            triangles[4].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
//            triangles[5].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
//
//            triangles[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
//            triangles[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
//            triangles[2].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
//            triangles[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
//            triangles[4].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
//            triangles[5].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);

//            triangles[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
//            triangles[1].position = sf::Vector2f(i * tileSize.x + tileSize.x / 2, j * tileSize.y - tileSize.y / 2);
//            triangles[2].position = sf::Vector2f(i * tileSize.x + tileSize.x / 2, j * tileSize.y + tileSize.y / 2);
//            triangles[3].position = sf::Vector2f(i * tileSize.x + tileSize.x / 2, j * tileSize.y - tileSize.y / 2);
//            triangles[4].position = sf::Vector2f(i * tileSize.x + tileSize.x / 2, j * tileSize.y + tileSize.y / 2);
//            triangles[5].position = sf::Vector2f(i * tileSize.x + tileSize.x, j * tileSize.y);

            // so this magic shit is beyond my comprehension
            // yet, I wrote it
            // and can't understand how I made it work
            triangles[0].position = sf::Vector2f(i * tileSize.x / 2 + j * tileSize.x / 2, j * tileSize.y / 2 - i * tileSize.y / 2);
            triangles[1].position = sf::Vector2f(i * tileSize.x / 2 + j * tileSize.x / 2 + tileSize.x / 2, j * tileSize.y / 2 - i * tileSize.y / 2 - tileSize.y / 2);
            triangles[2].position = sf::Vector2f(i * tileSize.x / 2 + j * tileSize.x / 2 + tileSize.x / 2, j * tileSize.y / 2 - i * tileSize.y / 2 + tileSize.y / 2);
            triangles[3].position = sf::Vector2f(i * tileSize.x / 2 + j * tileSize.x / 2 + tileSize.x / 2, j * tileSize.y / 2 - i * tileSize.y / 2 - tileSize.y / 2);
            triangles[4].position = sf::Vector2f(i * tileSize.x / 2 + j * tileSize.x / 2 + tileSize.x / 2, j * tileSize.y / 2 - i * tileSize.y / 2 + tileSize.y / 2);
            triangles[5].position = sf::Vector2f(i * tileSize.x / 2 + j * tileSize.x / 2 + tileSize.x, j * tileSize.y / 2 - i * tileSize.y / 2);

            // TODO: remove debug
            std::cout << i << ' ' << j << std::endl;
            std::cout << i * tileSize.x << ' ' << j * tileSize.y << std::endl;
            std::cout << i * tileSize.x + tileSize.x / 2 << ' ' << j * tileSize.y - tileSize.y / 2 << std::endl;
            std::cout << i * tileSize.x + tileSize.x / 2 << ' ' << j * tileSize.y + tileSize.y / 2 << std::endl;
            std::cout << i * tileSize.x + tileSize.x / 2 << ' ' << j * tileSize.y - tileSize.y / 2 << std::endl;
            std::cout << i * tileSize.x + tileSize.x / 2 << ' ' << j * tileSize.y + tileSize.y / 2 << std::endl;
            std::cout << i * tileSize.x + tileSize.x << ' ' << j * tileSize.y << std::endl;

//            triangles[0].color = sf::Color::Cyan;
//            triangles[1].color = sf::Color::Yellow;
//            triangles[2].color = sf::Color::White;
//            triangles[3].color = sf::Color::Green;
//            triangles[4].color = sf::Color::Red;
//            triangles[5].color = sf::Color::Blue;

            // TODO: fix texture coordinates (somehow managed to flip them)
            triangles[0].texCoords = sf::Vector2f(0, tileSize.y / 2);
            triangles[1].texCoords = sf::Vector2f(tileSize.x / 2, tileSize.y);
            triangles[2].texCoords = sf::Vector2f(tileSize.x / 2, 0);
            triangles[3].texCoords = sf::Vector2f(tileSize.x / 2, tileSize.y);
            triangles[4].texCoords = sf::Vector2f(tileSize.x / 2, 0);
            triangles[5].texCoords = sf::Vector2f(tileSize.x, tileSize.y / 2);

        }
    }

    return true;
}

void Map::draw(sf::RenderTarget & target, const sf::RenderStates & states) const {
    sf::RenderStates newStates = states;

    newStates.transform *= getTransform();

    newStates.texture = & m_tileset;

    target.draw(m_vertices, newStates);    // TODO: restore newStates in function
}
