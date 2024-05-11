#include "Tile.h"

Tile::Tile(sf::Texture & texture, sf::Vector2i tileSize, int x, int y) {
    m_index = {x, y};
    m_zIndex = 0;
    m_texture = texture;

//    m_tileShape.setPointCount(4);
//    m_tileShape.setPoint(0, sf::Vector2f(x * tileSize.x / 2 + y * tileSize.x / 2, y * tileSize.y / 2 - x * tileSize.y / 2));
//    m_tileShape.setPoint(1, sf::Vector2f(x * tileSize.x / 2 + y * tileSize.x / 2 + tileSize.x / 2, y * tileSize.y / 2 - x * tileSize.y / 2 - tileSize.y / 2));
//    m_tileShape.setPoint(2, sf::Vector2f(x * tileSize.x / 2 + y * tileSize.x / 2 + tileSize.x, y * tileSize.y / 2 - x * tileSize.y / 2));
//    m_tileShape.setPoint(3, sf::Vector2f(x * tileSize.x / 2 + y * tileSize.x / 2 + tileSize.x / 2, y * tileSize.y / 2 - x * tileSize.y / 2 + tileSize.y / 2));
//    m_tileShape.setTexture(& texture);

    // so this magic shit is beyond my comprehension
    // yet, I wrote it
    // and can't understand how I made it work
    m_vertices.resize(6);
    m_vertices.setPrimitiveType(sf::PrimitiveType::TriangleFan);

    m_vertices[0].position = sf::Vector2f(x * tileSize.x / 2 + y * tileSize.x / 2 + tileSize.x / 2, y * tileSize.y / 2 - x * tileSize.y / 2 - tileSize.y / 2);
    m_vertices[1].position = sf::Vector2f(x * tileSize.x / 2 + y * tileSize.x / 2, y * tileSize.y / 2 - x * tileSize.y / 2);
    m_vertices[2].position = sf::Vector2f(x * tileSize.x / 2 + y * tileSize.x / 2 + tileSize.x / 2, y * tileSize.y / 2 - x * tileSize.y / 2 - tileSize.y / 2);
    m_vertices[3].position = sf::Vector2f(x * tileSize.x / 2 + y * tileSize.x / 2 + tileSize.x, y * tileSize.y / 2 - x * tileSize.y / 2);
    m_vertices[4].position = sf::Vector2f(x * tileSize.x / 2 + y * tileSize.x / 2 + tileSize.x / 2, y * tileSize.y / 2 - x * tileSize.y / 2 + tileSize.y / 2);
    m_vertices[5].position = m_vertices[1].position;

//    m_vertices[0].texCoords = sf::Vector2f(x * tileSize.x / 2 + y * tileSize.x / 2 + tileSize.x / 2, y * tileSize.y / 2 - x * tileSize.y / 2 - tileSize.y / 2);
    m_vertices[1].texCoords = sf::Vector2f(tileSize.x / 2 + tileSize.x / 2, tileSize.y / 2 - tileSize.y / 2);
    m_vertices[2].texCoords = sf::Vector2f(x * tileSize.x / 2 + y * tileSize.x / 2 + tileSize.x / 2, y * tileSize.y / 2 - x * tileSize.y / 2 - tileSize.y / 2);
    m_vertices[3].texCoords = sf::Vector2f(x * tileSize.x / 2 + y * tileSize.x / 2 + tileSize.x, y * tileSize.y / 2 - x * tileSize.y / 2);
    m_vertices[4].texCoords = sf::Vector2f(x * tileSize.x / 2 + y * tileSize.x / 2 + tileSize.x / 2, y * tileSize.y / 2 - x * tileSize.y / 2 + tileSize.y / 2);
//    m_vertices[5].texCoords = sf::Vector2f(x * tileSize.x / 2 + y * tileSize.x / 2, y * tileSize.y / 2 - x * tileSize.y / 2);

#if DEBUG == 1
    std::cout << "index: " << x << ' ' << y << '\n';
    std::cout << '(' << m_vertices[0].position.x << ' ' << m_vertices[0].position.y << "), ";
    std::cout << '(' << m_vertices[1].position.x << ' ' << m_vertices[1].position.y << "), ";
    std::cout << '(' << m_vertices[2].position.x << ' ' << m_vertices[2].position.y << "), ";
    std::cout << '(' << m_vertices[3].position.x << ' ' << m_vertices[3].position.y << "), ";
    std::cout << '(' << m_vertices[4].position.x << ' ' << m_vertices[4].position.y << "), ";
    std::cout << '(' << m_vertices[5].position.x << ' ' << m_vertices[5].position.y << ")\n";
    std::cout << "--------------------------------------------------------------" << '\n';
#endif
}

sf::Vector2i Tile::getIndex() {
    return m_index;
}

void Tile::draw(sf::RenderTarget & target, sf::RenderStates states) const {
    states.transform *= getTransform();

    states.texture = & m_texture;

    target.draw(m_vertices, states);

#if DEBUG == 1
    // DEBUG: selecting index of tile and showing its indexes
    if (m_index.x == 0 && m_index.y == 3) {
        for (int i = 0; i < 6; i ++) {
            sf::Font font;
            if (!font.loadFromFile("res/fonts/cour.ttf")) {
                std::cerr << "[ERR] Failed to load font!\n";
            }
            sf::Text text;
            text.setFont(font);
            text.setString(std::to_string(i));
            text.setFillColor(sf::Color::Blue);
            text.setPosition(m_vertices[i].position);
            target.draw(text);
        }
    }
#endif
}

// Checking by using point-in-polygon algorithm
bool Tile::isTileClicked(const sf::Vector2f & mousePos) {
    bool isInside = false;

    for (size_t i = 0; i < m_vertices.getVertexCount(); i++)
    {
        size_t nextIndex = (i + 1) % m_vertices.getVertexCount();
        // TODO: need to understand the algorithm
        if (((m_vertices[i].position.y > mousePos.y) != (m_vertices[nextIndex].position.y > mousePos.y)) &&
            (mousePos.x <
             (m_vertices[nextIndex].position.x - m_vertices[i].position.x) * (mousePos.y - m_vertices[i].position.y) /
             (m_vertices[nextIndex].position.y - m_vertices[i].position.y) + m_vertices[i].position.x)) {
            isInside = !isInside;
        }
    }

    return isInside;
}
