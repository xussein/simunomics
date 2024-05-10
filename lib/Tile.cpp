#include "Tile.h"

Tile::Tile(sf::Texture & texture, sf::Vector2i tileSize, int x, int y) {
    m_index = {x, y};

    // so this magic shit is beyond my comprehension
    // yet, I wrote it
    // and can't understand how I made it work
    m_tileShape.setPointCount(4);
    m_tileShape.setPoint(0, sf::Vector2f(x * tileSize.x / 2 + y * tileSize.x / 2, y * tileSize.y / 2 - x * tileSize.y / 2));
    m_tileShape.setPoint(1, sf::Vector2f(x * tileSize.x / 2 + y * tileSize.x / 2 + tileSize.x / 2, y * tileSize.y / 2 - x * tileSize.y / 2 - tileSize.y / 2));
    m_tileShape.setPoint(2, sf::Vector2f(x * tileSize.x / 2 + y * tileSize.x / 2 + tileSize.x, y * tileSize.y / 2 - x * tileSize.y / 2));
    m_tileShape.setPoint(3, sf::Vector2f(x * tileSize.x / 2 + y * tileSize.x / 2 + tileSize.x / 2, y * tileSize.y / 2 - x * tileSize.y / 2 + tileSize.y / 2));
    m_tileShape.setTexture(& texture);
}

sf::Vector2i Tile::getIndex() {
    return m_index;
}

void Tile::draw(sf::RenderTarget & target, sf::RenderStates states) const {
    states.transform *= getTransform();

    target.draw(m_tileShape, states);
}

// Checking by using point-in-polygon algorithm
bool Tile::isTileClicked(const sf::Vector2f & mousePos) {
    bool isInside = false;

    for (size_t i = 0; i < m_tileShape.getPointCount(); i++)
    {
        size_t nextIndex = (i + 1) % m_tileShape.getPointCount();
        // TODO: need to understand the algorithm
        if (((m_tileShape.getPoint(i).y > mousePos.y) != (m_tileShape.getPoint(nextIndex).y > mousePos.y)) &&
            (mousePos.x <
             (m_tileShape.getPoint(nextIndex).x - m_tileShape.getPoint(i).x) * (mousePos.y - m_tileShape.getPoint(i).y) /
             (m_tileShape.getPoint(nextIndex).y - m_tileShape.getPoint(i).y) + m_tileShape.getPoint(i).x)) {
            isInside = !isInside;
        }
    }

    return isInside;
}
