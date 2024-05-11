#ifndef LIB_SIMUNOMICS_TILE_H
#define LIB_SIMUNOMICS_TILE_H


#include <SFML/Graphics.hpp>

#include "Constants.h"

#if DEBUG == 1
#include <iostream>
#endif

class Tile: public sf::Drawable, public sf::Transformable {
public:
    Tile(sf::Texture & texture, sf::Vector2i tileSize, int x, int y);
    bool isTileClicked(const sf::Vector2f& mousePos);
    sf::Vector2i getIndex();
private:
    void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
    sf::ConvexShape m_tileShape;
    sf::VertexArray m_vertices;
    sf::Texture m_texture;
    sf::Vector2i m_index;
    int m_zIndex;
};


#endif // LIB_SIMUNOMICS_TILE_H
