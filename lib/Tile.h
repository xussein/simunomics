#ifndef LIB_SIMUNOMICS_TILE_H
#define LIB_SIMUNOMICS_TILE_H


#include <SFML/Graphics.hpp>
#include <iostream>     // DEBUG: remove

class Tile: public sf::Drawable, public sf::Transformable {
public:
    Tile(sf::Texture & texture, sf::Vector2i tileSize, int x, int y);
    bool isTileClicked(const sf::Vector2i & mousePos);
//    void init(sf::Texture & texture, sf::Vector2i tileSize, int x, int y);
    sf::Vector2i getIndex();
private:
    void draw(sf::RenderTarget & target, const sf::RenderStates & states) const override;
    sf::VertexArray m_vertices;
    sf::Texture m_texture;
    sf::Vector2i m_index;
//    std::vector<sf::Text> m_texts;

};


#endif // LIB_SIMUNOMICS_TILE_H
