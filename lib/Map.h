#ifndef SIMUNOMICS_MAP_H
#define SIMUNOMICS_MAP_H    // TODO: fix name


#include <SFML/Graphics.hpp>
#include "Tile.h"

class Map {
public:
    bool load(const std::string & tileset, sf::Vector2i tileSize, const int * tiles, size_t mapWidth, size_t mapHeight);
    void draw(sf::RenderTarget & target);
    void isMapClicked(const sf::Vector2i & mousePos);
    sf::Vector2f getCenterCoords();
private:
//    void draw(sf::RenderTarget & target, const sf::RenderStates & states) const override;
    sf::VertexArray m_vertices;
    std::vector<Tile> m_tiles;
    sf::Texture m_tileset;
    sf::Vector2f m_centerCoords;
};


#endif //SIMUNOMICS_MAP_H
