#ifndef LIB_SIMUNOMICS_TILE_H
#define LIB_SIMUNOMICS_TILE_H


#include <SFML/Graphics.hpp>

class Tile: public sf::Drawable, public sf::Transformable {
public:
    Tile(sf::Texture & texture, sf::Vector2i tileSize, int x, int y);
    bool isTileClicked(const sf::Vector2f& mousePos);
    sf::Vector2i getIndex();
private:
    void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
    sf::ConvexShape m_tileShape;
    sf::Vector2i m_index;
};


#endif // LIB_SIMUNOMICS_TILE_H
