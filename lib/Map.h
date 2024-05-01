#ifndef SIMUNOMICS_MAP_H
#define SIMUNOMICS_MAP_H    // TODO: fix name


#include <SFML/Graphics.hpp>

class Map: public sf::Drawable, public sf::Transformable {
public:
    bool load(const std::string & tileset, sf::Vector2i tileSize, const int * tiles, unsigned int mapWidth, unsigned int mapHeight);
    sf::VertexArray m_vertices;     // TODO: set back to private, debugging
private:
    void draw(sf::RenderTarget & target, const sf::RenderStates & states) const override;

    sf::Texture m_tileset;
};


#endif //SIMUNOMICS_MAP_H
