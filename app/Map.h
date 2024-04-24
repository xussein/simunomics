#ifndef SIMUNOMICS_MAP_H
#define SIMUNOMICS_MAP_H    // TODO: fix name


#include <SFML/Graphics.hpp>

class Map: public sf::Drawable, public sf::Transformable {
public:
    bool load(const std::string & tileset, sf::Vector2u tileSize, const int * tiles, unsigned int width, unsigned int height);
private:
    void draw(sf::RenderTarget & target, const sf::RenderStates & states) const override;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};


#endif //SIMUNOMICS_MAP_H
