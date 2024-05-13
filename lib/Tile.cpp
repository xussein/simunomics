#include <cmath>
#include "Tile.h"

Tile::Tile(sf::Texture & texture, sf::Vector2i tileSize, int x, int y) {
    m_index = {x, y};
    m_zIndex = 0;
    m_texture = texture;
    m_tileSize = tileSize;

    m_vertices.resize(12);
    m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);

    float offsetX = x * tileSize.x / 2 + y * tileSize.x / 2;
    float offsetY = y * tileSize.y / 2 - x * tileSize.y / 2;

    // so this magic shit is beyond my comprehension
    // yet, I wrote it
    // and can't understand how I made it work
    // ABO triangle
    m_vertices[0].position = sf::Vector2f(offsetX, offsetY + tileSize.y / 2);                   // A (0, h/2)
    m_vertices[1].position = sf::Vector2f(offsetX + tileSize.x / 2, offsetY);                   // B (w/2, 0)
    m_vertices[2].position = sf::Vector2f(offsetX + tileSize.x / 2, offsetY + tileSize.y / 2);  // O (w/2, h/2)
    // BOC triangle
    m_vertices[3].position = m_vertices[1].position;
    m_vertices[4].position = m_vertices[2].position;
    m_vertices[5].position = sf::Vector2f(offsetX + tileSize.x + m_zIndex * tileSize.x / 2, offsetY + tileSize.y / 2);      // C (w, h/2)
    // AOD triangle
    m_vertices[6].position = m_vertices[0].position;
    m_vertices[7].position = m_vertices[2].position;
    m_vertices[8].position = sf::Vector2f(offsetX + tileSize.x / 2 + m_zIndex * tileSize.x / 2, offsetY + tileSize.y);      // D (w/2, h)
    // DOC triangle
    m_vertices[9].position = m_vertices[8].position;
    m_vertices[10].position = m_vertices[2].position;
    m_vertices[11].position = m_vertices[5].position;

    // ABO triangle
    m_vertices[0].texCoords = sf::Vector2f(0, tileSize.y / 2);               // A (0, h/2)
    m_vertices[1].texCoords = sf::Vector2f(tileSize.x / 2, 0);               // B (w/2, 0)
    m_vertices[2].texCoords = sf::Vector2f(tileSize.x / 2, tileSize.y / 2);  // O (w/2, h/2)
    // BOC triangle
    m_vertices[3].texCoords = m_vertices[1].texCoords;
    m_vertices[4].texCoords = m_vertices[2].texCoords;
    m_vertices[5].texCoords = sf::Vector2f(tileSize.x, tileSize.y / 2);         // C (w, h/2)
    // AOD triangle
    m_vertices[6].texCoords = m_vertices[0].texCoords;
    m_vertices[7].texCoords = m_vertices[2].texCoords;
    m_vertices[8].texCoords = sf::Vector2f(tileSize.x / 2, tileSize.y);         // D (w/2, h)
    // DOC triangle
    m_vertices[9].texCoords = m_vertices[8].texCoords;
    m_vertices[10].texCoords = m_vertices[2].texCoords;
    m_vertices[11].texCoords = m_vertices[5].texCoords;

#if DEBUG == 1
//    std::cout << "index: " << x << ' ' << y << '\n';
//    for (int i = 0; i < m_vertices.getVertexCount(); i ++) {
//        std::cout << '(' << m_vertices[i].position.x << ' ' << m_vertices[i].position.y << "), ";
//    }
//    std::cout << "\n--------------------------------------------------------------" << '\n';
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
    if (m_index.x == 0 && m_index.y == 0) {
        for (int i = 0; i < m_vertices.getVertexCount(); i ++) {
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
bool Tile::isInsideTile(const sf::Vector2f & mousePos) {
    bool isInside = false;

    for (size_t i = 0; i < 4; i++)
    {
        size_t nextIndex = (i + 1) % 4;
        // TODO: need to understand the algorithm
        if (((m_vertices[outerVerticesIndexes[i]].position.y > mousePos.y) != (m_vertices[outerVerticesIndexes[nextIndex]].position.y > mousePos.y)) &&
            (mousePos.x <
             (m_vertices[outerVerticesIndexes[nextIndex]].position.x - m_vertices[outerVerticesIndexes[i]].position.x) * (mousePos.y - m_vertices[outerVerticesIndexes[i]].position.y) /
             (m_vertices[outerVerticesIndexes[nextIndex]].position.y - m_vertices[outerVerticesIndexes[i]].position.y) + m_vertices[outerVerticesIndexes[i]].position.x)) {
            isInside = !isInside;
        }
    }

    return isInside;
}

sf::Vector2f Tile::getNearestVertex(const sf::Vector2f & mousePos) {
    // m_vertices[2].texCoords - point O, center of the tile
    // comparing mouse position relatively to tile center
    // then calculating distance to a pair of vertices
    // which indexes are: 0 - A, 1 - B, 5 - C, 8 - D
    if (mousePos.x < m_vertices[2].position.x && mousePos.y < m_vertices[2].position.y) {             // upper left quadrangle, ABO
        if (sqrt(pow(mousePos.x - m_vertices[0].position.x, 2) + pow(mousePos.x - m_vertices[0].position.x, 2)) <=
            sqrt(pow(mousePos.x - m_vertices[1].position.x, 2) + pow(mousePos.x - m_vertices[1].position.x, 2))) {
            return m_vertices[0].position;
        } else {
            return m_vertices[1].position;
        }
    } else if (mousePos.x < m_vertices[2].position.x && mousePos.y >= m_vertices[2].position.y) {     // lower left quadrangle, AOD
        if (sqrt(pow(mousePos.x - m_vertices[0].position.x, 2) + pow(mousePos.x - m_vertices[0].position.x, 2)) <=
            sqrt(pow(mousePos.x - m_vertices[8].position.x, 2) + pow(mousePos.x - m_vertices[8].position.x, 2))) {
            return m_vertices[0].position;
        } else {
            return m_vertices[8].position;
        }
    } else if (mousePos.x >= m_vertices[2].position.x && mousePos.y >= m_vertices[2].position.y) {    // lower right quadrangle, DOC
        if (sqrt(pow(mousePos.x - m_vertices[5].position.x, 2) + pow(mousePos.x - m_vertices[5].position.x, 2)) <=
            sqrt(pow(mousePos.x - m_vertices[8].position.x, 2) + pow(mousePos.x - m_vertices[8].position.x, 2))) {
            return m_vertices[5].position;
        } else {
            return m_vertices[8].position;
        }
    } else if (mousePos.x >= m_vertices[2].position.x && mousePos.y < m_vertices[2].position.y) {     // upper right quadrangle, BOC
        if (sqrt(pow(mousePos.x - m_vertices[1].position.x, 2) + pow(mousePos.x - m_vertices[1].position.x, 2)) <=
            sqrt(pow(mousePos.x - m_vertices[5].position.x, 2) + pow(mousePos.x - m_vertices[5].position.x, 2))) {
            return m_vertices[1].position;
        } else {
            return m_vertices[5].position;
        }
    }
}

void Tile::elevateVertex(sf::Vector2f currentVertex) {
    if (m_zIndex == 0) {
        m_zIndex ++;
        for (size_t i = 0; i < m_vertices.getVertexCount(); i++) {
            if (m_vertices[i].position.x == currentVertex.x && m_vertices[i].position.y == currentVertex.y) {
                m_vertices[i].position.y -= m_zIndex * m_tileSize.y / 2;
            }
        }
    }
}
