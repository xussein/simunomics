//
// Created by xussein on 5/15/2024.
//

#ifndef SIMUNOMICS_ELEVATIONPOINTER_H
#define SIMUNOMICS_ELEVATIONPOINTER_H


#include <SFML/Graphics/CircleShape.hpp>

class ElevationPointer {
public:
    void setTileIndex(size_t index);
    size_t getTileIndex();
    sf::CircleShape m_vertexPoint;
private:
    size_t m_tileIndex;
};


#endif //SIMUNOMICS_ELEVATIONPOINTER_H
