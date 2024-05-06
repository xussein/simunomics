#include "Tile.h"

Tile::Tile(sf::Texture & texture, sf::Vector2i tileSize, int x, int y) {
    m_index = {x, y};

    m_texture = texture;

    m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    m_vertices.resize(6);

    // so this magic shit is beyond my comprehension
    // yet, I wrote it
    // and can't understand how I made it work
    m_vertices[0].position = sf::Vector2f(x * tileSize.x / 2 + y * tileSize.x / 2, y * tileSize.y / 2 - x * tileSize.y / 2);
    m_vertices[1].position = sf::Vector2f(x * tileSize.x / 2 + y * tileSize.x / 2 + tileSize.x / 2, y * tileSize.y / 2 - x * tileSize.y / 2 - tileSize.y / 2);
    m_vertices[2].position = sf::Vector2f(x * tileSize.x / 2 + y * tileSize.x / 2 + tileSize.x / 2, y * tileSize.y / 2 - x * tileSize.y / 2 + tileSize.y / 2);
    m_vertices[3].position = sf::Vector2f(x * tileSize.x / 2 + y * tileSize.x / 2 + tileSize.x / 2, y * tileSize.y / 2 - x * tileSize.y / 2 - tileSize.y / 2);
    m_vertices[4].position = sf::Vector2f(x * tileSize.x / 2 + y * tileSize.x / 2 + tileSize.x / 2, y * tileSize.y / 2 - x * tileSize.y / 2 + tileSize.y / 2);
    m_vertices[5].position = sf::Vector2f(x * tileSize.x / 2 + y * tileSize.x / 2 + tileSize.x, y * tileSize.y / 2 - x * tileSize.y / 2);

    // TODO: fix texture coordinates (somehow managed to flip them)
    m_vertices[0].texCoords = sf::Vector2f(0, tileSize.y / 2);
    m_vertices[1].texCoords = sf::Vector2f(tileSize.x / 2, tileSize.y);
    m_vertices[2].texCoords = sf::Vector2f(tileSize.x / 2, 0);
    m_vertices[3].texCoords = sf::Vector2f(tileSize.x / 2, tileSize.y);
    m_vertices[4].texCoords = sf::Vector2f(tileSize.x / 2, 0);
    m_vertices[5].texCoords = sf::Vector2f(tileSize.x, tileSize.y / 2);

//    // DEBUG: showing vertices number
//    sf::Font font;
//    if (!font.loadFromFile("res/fonts/cour.ttf")) {
//        std::cerr << "[ERR] Font loading failed!" << std::endl;
//    }
//
//    std::cout << m_vertices.getVertexCount() << std::endl;
////    m_texts.resize(m_vertices.getVertexCount());
//    sf::Text m_texts[6] = {sf::Text(font), sf::Text(font), sf::Text(font), sf::Text(font), sf::Text(font), sf::Text(font)};
//
//    for (int i = 0; i < m_vertices.getVertexCount(); i ++) {
//        sf::Text text(font, std::to_string(i));
//        text.setString(std::to_string(i));
//        text.setFillColor(sf::Color::Blue);
//        text.setOutlineColor(sf::Color::White);
//        sf::Vector2f currPos = m_vertices[i].position;
//        text.setPosition(currPos);
//        m_texts[i] = text;
//    }

//    for (const sf::Text & text: m_texts) {
//        std::cout << text.getPosition().x << ' ' << text.getPosition().y << ' ' << * text.getString().getData() << std::endl;
//    }
}

sf::Vector2i Tile::getIndex() {
    return m_index;
}

void Tile::draw(sf::RenderTarget & target, const sf::RenderStates & states) const {
    sf::RenderStates newStates = states;

    newStates.transform *= getTransform();

    newStates.texture = & m_texture;

//    for (int i = 0; i < m_vertices.getVertexCount(); i ++) {
//        target.draw(m_texts[i], newStates);
//    }

    target.draw(m_vertices, newStates);
}

bool Tile::isTileClicked(const sf::Vector2i & mousePos) {
    bool isInside = false;

    for (size_t i = 0; i < m_vertices.getVertexCount(); i++)        // TODO: instead of computing getVertexCount() set it to const 6
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
