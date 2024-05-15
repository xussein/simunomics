#ifndef LIB_SIMUNOMICS_MAP_H
#define LIB_SIMUNOMICS_MAP_H    // TODO: fix name


#include <SFML/Graphics.hpp>
#include <cmath>

//#include "Tile.h"
#include "../Constants.h"
#include "ElevationPointer.h"

#if DEBUG == 1
#include <iostream>
#endif

class Map: public sf::Drawable, public sf::Transformable {
public:
    bool load(const std::string & tileset, sf::Vector2i tileSize, const int * tiles, size_t mapWidth, size_t mapHeight);
//    void draw(sf::RenderTarget & target);
//    void isMapClicked(const sf::Vector2f & mousePos);
//    void isMapHovered(const sf::Vector2f & mousePos);
    static void move(sf::View & view, sf::Vector2f offset);
    sf::Vector2f getCenterCoords();
    void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
    int getNearestVertex(sf::Vector2f mousePos);
    int getCurrentlyHoveredTile(sf::Vector2f mousePos);
    void elevateVertex();
private:
//    std::vector<Tile> m_tiles;
    sf::Vector2i m_mapSize;
    std::vector<sf::Texture> m_tilesTextures;
    sf::Texture m_tileset;
    sf::VertexArray m_vertices;
    sf::Vector2f m_centerCoords;
    ElevationPointer m_elevationPointer;
};


#endif // LIB_SIMUNOMICS_MAP_H
