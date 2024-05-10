#ifndef LIB_SIMUNOMICS_MAP_H
#define LIB_SIMUNOMICS_MAP_H    // TODO: fix name


#include <SFML/Graphics.hpp>

#include "Tile.h"
#include "Constants.h"

#if DEBUG == 1
#include <iostream>
#endif

class Map {
public:
    bool load(const std::string & tileset, sf::Vector2i tileSize, const int * tiles, size_t mapWidth, size_t mapHeight);
    void draw(sf::RenderTarget & target);
    void isMapClicked(const sf::Vector2f & mousePos);
    static void move(sf::View & view, sf::Vector2f offset);
    sf::Vector2f getCenterCoords();
private:
    std::vector<Tile> m_tiles;
    std::vector<sf::Texture> m_tilesTextures;
    sf::Texture m_tileset;
    sf::Vector2f m_centerCoords;
};


#endif // LIB_SIMUNOMICS_MAP_H
