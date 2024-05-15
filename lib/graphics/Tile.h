#ifndef LIB_SIMUNOMICS_TILE_H
#define LIB_SIMUNOMICS_TILE_H


#include <SFML/Graphics.hpp>
#include <cmath>

#include "../Constants.h"

#if DEBUG == 1
#include <iostream>
#endif

class Tile: public sf::Drawable, public sf::Transformable {
public:
    Tile(sf::Texture & texture, sf::Vector2i tileSize, int x, int y);
    bool isInsideTile(const sf::Vector2f& mousePos);
    sf::Vector2i getIndex();
    sf::Vector2f getNearestVertex(const sf::Vector2f & mousePos);
    void elevateVertex(sf::Vector2f currentVertex);
private:
    void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
    sf::VertexArray m_vertices;
    sf::Texture m_texture;
    sf::Vector2i m_index;
    sf::Vector2i m_tileSize;
    int m_zIndex;
};


#endif // LIB_SIMUNOMICS_TILE_H
