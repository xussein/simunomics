#include "Map.h"

bool Map::load(const std::string & tileset, sf::Vector2i tileSize, const int * tiles, size_t mapWidth, size_t mapHeight) {
    m_mapSize.x = mapWidth;
    m_mapSize.y = mapHeight;
    m_tileSize = tileSize;
    // checking if file exists and loading tileset from file path
    if (!m_tileset.loadFromFile(tileset)) {
        return false;   // TODO: throw exception
    } /*else {
        // Parsing texture file into separate textures and storing them inside vector
        for (int i = 0; i < tilesetXCount; i ++) {      // TODO: consider removing magic number 4 and creating (or calculating) tile number
            for (int j = 0; j < tilesetYCount; j ++) {
                sf::Texture tileTexture;
                sf::IntRect textureRect = {i * tileWidth, j * tileHeight, i * tileWidth + tileWidth, j * tileHeight + tileHeight};
                tileTexture.loadFromFile(tileset, textureRect);
                m_tilesTextures.push_back(tileTexture);
            }
        }
    }*/

    m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    m_vertices.resize(mapWidth * mapHeight * 12);

    for (int i = 0; i < mapWidth; i ++) {
        for (int j = 0; j < mapHeight; j ++) {

            float oX = i * tileSize.x / 2 + j * tileSize.x / 2;
            float oY = j * tileSize.y / 2 - i * tileSize.y / 2;

            sf::Vertex * triangles = & m_vertices[(i + j * mapWidth) * 12];

            // There are 4 triangles at the base of the rhombus.
            // Point O is the center, other points are: 0 - A, 1 - B, 5 - C, 8 - D. Triangles, built clockwise:
            // 1. ABO triangle
            triangles[0].position = sf::Vector2f(oX, oY + tileSize.y / 2);                   // A (0, h/2)
            triangles[1].position = sf::Vector2f(oX + tileSize.x / 2, oY);                   // B (w/2, 0)
            triangles[2].position = sf::Vector2f(oX + tileSize.x / 2, oY + tileSize.y / 2);  // O (w/2, h/2)
            // 2. BOC triangle
            triangles[3].position = triangles[1].position;                                         // B (w/2, 0)
            triangles[4].position = triangles[2].position;                                         // O (w/2, h/2)
            triangles[5].position = sf::Vector2f(oX + tileSize.x, oY + tileSize.y / 2);      // C (w, h/2)
            // 3. AOD triangle
            triangles[6].position = triangles[0].position;                                         // A (0, h/2)
            triangles[7].position = triangles[2].position;                                         // O (w/2, h/2)
            triangles[8].position = sf::Vector2f(oX + tileSize.x / 2, oY + tileSize.y);      // D (w/2, h)
            // 4. DOC triangle
            triangles[9].position = triangles[8].position;                                         // D (w/2, h)
            triangles[10].position = triangles[2].position;                                        // O (w/2, h/2)
            triangles[11].position = triangles[5].position;                                        // C (w, h/2)

            // tileNumber defines which tile is taken from imported tile textures (from file):
            int tileNumber = tiles[i + j * mapWidth];

            // Calculating offset for tile set:
            int tX = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tY = tileNumber / (m_tileset.getSize().y / tileSize.y);

            // TexCoords are calulated relatively to polygon vertex positions. All triangles, built clockwise:
            // 1. ABO triangle
            triangles[0].texCoords = sf::Vector2f(tX * tileSize.x, tY * tileSize.y + tileSize.y / 2);                   // A (0, h/2)
            triangles[1].texCoords = sf::Vector2f(tX * tileSize.x + tileSize.x / 2, tY * tileSize.y);                   // B (w/2, 0)
            triangles[2].texCoords = sf::Vector2f(tX * tileSize.x + tileSize.x / 2, tY * tileSize.y + tileSize.y / 2);  // O (w/2, h/2)
            // 2. BOC triangle
            triangles[3].texCoords = triangles[1].texCoords;                                                                  // B (w/2, 0)
            triangles[4].texCoords = triangles[2].texCoords;                                                                  // O (w/2, h/2)
            triangles[5].texCoords = sf::Vector2f(tX * tileSize.x + tileSize.x, tY * tileSize.y + tileSize.y / 2);      // C (w, h/2)
            // 3. AOD triangle
            triangles[6].texCoords = triangles[0].texCoords;                                                                  // A (0, h/2)
            triangles[7].texCoords = triangles[2].texCoords;                                                                  // O (w/2, h/2)
            triangles[8].texCoords = sf::Vector2f(tX * tileSize.x + tileSize.x / 2, tY * tileSize.y + tileSize.y);      // D (w/2, h)
            // 4. DOC triangle
            triangles[9].texCoords = triangles[8].texCoords;                                                                  // D (w/2, h)
            triangles[10].texCoords = triangles[2].texCoords;                                                                 // O (w/2, h/2)
            triangles[11].texCoords = triangles[5].texCoords;                                                                 // C (w, h/2)

//            // TexCoords are calulated relatively to polygon vertex positions. All triangles, built clockwise:
//            // 1. ABO triangle
//            triangles[0].texCoords = sf::Vector2f(0, tileSize.y / 2);               // A (0, h/2)
//            triangles[1].texCoords = sf::Vector2f(tileSize.x / 2, 0);               // B (w/2, 0)
//            triangles[2].texCoords = sf::Vector2f(tileSize.x / 2, tileSize.y / 2);  // O (w/2, h/2)
//            // 2. BOC triangle
//            triangles[3].texCoords = triangles[1].texCoords;                              // B (w/2, 0)
//            triangles[4].texCoords = triangles[2].texCoords;                              // O (w/2, h/2)
//            triangles[5].texCoords = sf::Vector2f(tileSize.x, tileSize.y / 2);         // C (w, h/2)
//            // 3. AOD triangle
//            triangles[6].texCoords = triangles[0].texCoords;                              // A (0, h/2)
//            triangles[7].texCoords = triangles[2].texCoords;                              // O (w/2, h/2)
//            triangles[8].texCoords = sf::Vector2f(tileSize.x / 2, tileSize.y);         // D (w/2, h)
//            // 4. DOC triangle
//            triangles[9].texCoords = triangles[8].texCoords;                              // D (w/2, h)
//            triangles[10].texCoords = triangles[2].texCoords;                             // O (w/2, h/2)
//            triangles[11].texCoords = triangles[5].texCoords;                             // C (w, h/2)

//            triangles[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
//            triangles[1].position = sf::Vector2f(i * tileSize.x + tileSize.x / 2, j * tileSize.y - tileSize.y / 2);
//            triangles[2].position = sf::Vector2f(i * tileSize.x + tileSize.x / 2, j * tileSize.y + tileSize.y / 2);
//            triangles[3].position = sf::Vector2f(i * tileSize.x + tileSize.x / 2, j * tileSize.y - tileSize.y / 2);
//            triangles[4].position = sf::Vector2f(i * tileSize.x + tileSize.x / 2, j * tileSize.y + tileSize.y / 2);
//            triangles[5].position = sf::Vector2f(i * tileSize.x + tileSize.x, j * tileSize.y);

//            m_tiles.emplace_back(m_tilesTextures[tileNumber], tileSize, i, j);

#if DEBUG == 1
            std::cout << "index: " << i << ' ' << j << '\n';
            for (int z = 0; z < 12; z ++) {
                std::cout << '(' << triangles[z].position.x << ' ' << triangles[z].position.y << "), ";
            }
            std::cout << "\n";
            for (int z = 0; z < 12; z ++) {
                std::cout << '(' << triangles[z].texCoords.x << ' ' << triangles[z].texCoords.y << "), ";
            }
            std::cout << "\n--------------------------------------------------------------" << '\n';
#endif
        }
    }

    m_elevationPointer.m_vertexPoint.setRadius(3);
    m_elevationPointer.m_vertexPoint.setOrigin(3, 3);

    return true;
}

sf::Vector2f Map::getCenterCoords() {
    return m_centerCoords;
}

//void Map::draw(sf::RenderTarget & target) {
//    target.draw(m_vertexPoint);
////    m_tiles.reserve(m_tiles.size());
//    for (Tile & tile: m_tiles) {
//        target.draw(tile);
//    }
//}

//void Map::isMapClicked(const sf::Vector2f & mousePos) {
//
//    for (Tile & tile: m_tiles) {
//        if (tile.isInsideTile(mousePos)) {
//            // tile.elevateVertex(m_vertexPoint.getPosition());
//#if DEBUG == 1
//            std::cout << tile.getIndex().x << ' ' << tile.getIndex().y << std::endl;
//#endif
//        }
//    }
//}

//void Map::isMapHovered(const sf::Vector2f & mousePos) {
//    for (Tile & tile: m_tiles) {
//        if (tile.isInsideTile(mousePos)) {
//            m_vertexPoint.setFillColor(sf::Color::White);
////            m_vertexPoint.setPosition(tile.getNearestVertex(mousePos));
//#if DEBUG == 1
////            std::cout << tile.getIndex().x << ' ' << tile.getIndex().y << std::endl;
//#endif
//        }
//    }
//}

void Map::move(sf::View & view, sf::Vector2f offset) {
    view.move(offset);
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    states.texture = & m_tileset;

    target.draw(m_vertices, states);

    target.draw(m_elevationPointer.m_vertexPoint);

#if DEBUG == 1
    // DEBUG: selecting index of tile and showing its indexes

        for (int i = 0; i < 12; i ++) {
            sf::Font font;
            if (!font.loadFromFile("res/fonts/cour.ttf")) {
                std::cerr << "[ERR] Failed to load font!\n";
            }
            sf::Text text;
            text.setFont(font);
            text.setString(std::to_string(i));
            text.setFillColor(sf::Color::Blue);
            text.setPosition(m_vertices[i + 64].position);
            target.draw(text);
        }

#endif
}

// TODO: consider void instead of int
int Map::getNearestVertex(sf::Vector2f mousePos) {
    int i = getCurrentlyHoveredTile(mousePos);
#if DEBUG == 1
//    std::cout << i << '\n';
#endif
    // m_vertices[2].texCoords - point O, center of the tile
    // comparing mouse position relatively to tile center
    // then calculating distance to a pair of vertices
    // which indexes are: 0 - A, 1 - B, 5 - C, 8 - D (+12 for each tile)
    if (mousePos.x < m_vertices[i + 2].position.x && mousePos.y < m_vertices[i + 2].position.y) {             // upper left quadrangle, ABO
        if (sqrt(pow(mousePos.x - m_vertices[i + 0].position.x, 2) + pow(mousePos.x - m_vertices[i + 0].position.x, 2)) <=
            sqrt(pow(mousePos.x - m_vertices[i + 1].position.x, 2) + pow(mousePos.x - m_vertices[i + 1].position.x, 2))) {
            m_elevationPointer.m_vertexPoint.setPosition(m_vertices[i + 0].position);
            m_elevationPointer.setTileIndex(i + 0);
            return i + 0;
        } else {
            m_elevationPointer.m_vertexPoint.setPosition(m_vertices[i + 1].position);
            m_elevationPointer.setTileIndex(i + 1);
            return i + 1;
        }
    } else if (mousePos.x < m_vertices[i + 2].position.x && mousePos.y >= m_vertices[i + 2].position.y) {     // lower left quadrangle, AOD
        if (sqrt(pow(mousePos.x - m_vertices[i + 0].position.x, 2) + pow(mousePos.x - m_vertices[i + 0].position.x, 2)) <=
            sqrt(pow(mousePos.x - m_vertices[i + 8].position.x, 2) + pow(mousePos.x - m_vertices[i + 8].position.x, 2))) {
            m_elevationPointer.m_vertexPoint.setPosition(m_vertices[i + 0].position);
            m_elevationPointer.setTileIndex(i + 0);
            return i + 0;
        } else {
            m_elevationPointer.m_vertexPoint.setPosition(m_vertices[i + 8].position);
            m_elevationPointer.setTileIndex(i + 8);
            return i + 8;
        }
    } else if (mousePos.x >= m_vertices[i + 2].position.x && mousePos.y >= m_vertices[i + 2].position.y) {    // lower right quadrangle, DOC
        if (sqrt(pow(mousePos.x - m_vertices[i + 5].position.x, 2) + pow(mousePos.x - m_vertices[i + 5].position.x, 2)) <=
            sqrt(pow(mousePos.x - m_vertices[i + 8].position.x, 2) + pow(mousePos.x - m_vertices[i + 8].position.x, 2))) {
            m_elevationPointer.m_vertexPoint.setPosition(m_vertices[i + 5].position);
            m_elevationPointer.setTileIndex(i + 5);
            return i + 5;
        } else {
            m_elevationPointer.m_vertexPoint.setPosition(m_vertices[i + 8].position);
            m_elevationPointer.setTileIndex(i + 8);
            return i + 8;
        }
    } else if (mousePos.x >= m_vertices[i + 2].position.x && mousePos.y < m_vertices[i + 2].position.y) {     // upper right quadrangle, BOC
        if (sqrt(pow(mousePos.x - m_vertices[i + 1].position.x, 2) + pow(mousePos.x - m_vertices[i + 1].position.x, 2)) <=
            sqrt(pow(mousePos.x - m_vertices[i + 5].position.x, 2) + pow(mousePos.x - m_vertices[i + 5].position.x, 2))) {
            m_elevationPointer.m_vertexPoint.setPosition(m_vertices[i + 1].position);
            m_elevationPointer.setTileIndex(i + 1);
            return i + 1;
        } else {
            m_elevationPointer.m_vertexPoint.setPosition(m_vertices[i + 5].position);
            m_elevationPointer.setTileIndex(i + 5);
            return i + 5;
        }
    }
}

int Map::getCurrentlyHoveredTile(sf::Vector2f mousePos) {
    bool isInside = false;

    // Point inside of polygon algorithm, or ray-casting algorithm:
    for (int i = 0; i < m_vertices.getVertexCount(); i += 12) {
        // For each of outer points:
        for (size_t j = 0; j < 4; j ++)
        {
            size_t nextIndex = (j + 1) % 4;
            // TODO: need to understand the algorithm
            if (((m_vertices[outerVerticesIndexes[j] + i].position.y > mousePos.y) != (m_vertices[outerVerticesIndexes[nextIndex] + i].position.y > mousePos.y)) &&
                (mousePos.x <
                 (m_vertices[outerVerticesIndexes[nextIndex] + i].position.x - m_vertices[outerVerticesIndexes[j] + i].position.x) * (mousePos.y - m_vertices[outerVerticesIndexes[j] + i].position.y) /
                 (m_vertices[outerVerticesIndexes[nextIndex] + i].position.y - m_vertices[outerVerticesIndexes[j] + i].position.y) + m_vertices[outerVerticesIndexes[j] + i].position.x)) {
                isInside = !isInside;
            }
        }
        if (isInside) {
            return i;
        }
    }
    return -1;
}

void Map::elevateVertex() {
    int vertexIndex = m_elevationPointer.getTileIndex();
#if DEBUG == 1
    std::cout << vertexIndex << ' '
              << vertexIndex % ((m_mapSize.x) * 12) << ' '
              << m_mapSize.x * 12 - 7 << ' '
              << m_vertices.getVertexCount() << '\n';
#endif
    // if vertex is left (point A) in the current tile and in order to stay inside VertexArray
    if (vertexIndex % 12 == 0 && vertexIndex - 12 * (m_mapSize.x + 1) >= 0 && vertexIndex % (m_mapSize.x * 12) != 0) {
        // two A vertices
        m_vertices[vertexIndex].position.y -= m_tileSize.y / 2;
        m_vertices[vertexIndex + 6].position.y -= m_tileSize.y / 2;
        // two B vertices
        m_vertices[vertexIndex - 11].position.y -= m_tileSize.y / 2;
        m_vertices[vertexIndex - 9].position.y -= m_tileSize.y / 2;
        // two C vertices
        m_vertices[vertexIndex - 12 * (m_mapSize.x + 1) + 5].position.y -= m_tileSize.y / 2;
        m_vertices[vertexIndex - 12 * (m_mapSize.x + 1) + 11].position.y -= m_tileSize.y / 2;
        // two D vertices
        m_vertices[vertexIndex - 12 * m_mapSize.x + 8].position.y -= m_tileSize.y / 2;
        m_vertices[vertexIndex - 12 * m_mapSize.x + 9].position.y -= m_tileSize.y / 2;
#if DEBUG == 1
        std::cout << "elevation is allowed, left (point A)\n";
#endif
    // if vertex is upper (point B) in the current tile and in order to stay inside VertexArray
    } else if (vertexIndex % 12 == 1 && vertexIndex - 12 * m_mapSize.x >= 1 && vertexIndex % (m_mapSize.x * 12) != (m_mapSize.x * 12 - 11)) {
        // two A vertices
        m_vertices[vertexIndex].position.y -= m_tileSize.y / 2;
        m_vertices[vertexIndex + 6].position.y -= m_tileSize.y / 2;
        // two B vertices
        m_vertices[vertexIndex].position.y -= m_tileSize.y / 2;
        m_vertices[vertexIndex + 2].position.y -= m_tileSize.y / 2;
        // two C vertices
        m_vertices[vertexIndex - 12 * (m_mapSize.x + 1) + 5].position.y -= m_tileSize.y / 2;
        m_vertices[vertexIndex - 12 * (m_mapSize.x + 1) + 11].position.y -= m_tileSize.y / 2;
        // two D vertices
        m_vertices[vertexIndex - 12 * m_mapSize.x + 8].position.y -= m_tileSize.y / 2;
        m_vertices[vertexIndex - 12 * m_mapSize.x + 9].position.y -= m_tileSize.y / 2;
#if DEBUG == 1
        std::cout << "elevation is allowed, upper (point B)\n";
#endif
    // if vertex is right (point C) in the current tile and in order to stay inside VertexArray
    } else if (vertexIndex % 12 == 5 && vertexIndex + 12 * (m_mapSize.x + 1) < m_vertices.getVertexCount() && vertexIndex % (m_mapSize.x * 12) != (m_mapSize.x * 12 - 7)) {
#if DEBUG == 1
        std::cout << "elevation is allowed, right (point C)\n";
#endif
    // if vertex is lower (point D) in the current tile and in order to stay inside VertexArray
    } else if (vertexIndex % 12 == 8 && vertexIndex + 12 * m_mapSize.x < m_vertices.getVertexCount() && vertexIndex % (m_mapSize.x * 12) != 8) {
#if DEBUG == 1
            std::cout << "elevation is allowed, lower (point D)\n";
#endif
    }
}

