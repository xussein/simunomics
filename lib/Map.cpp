#include "Map.h"

bool Map::load(const std::string & tileset, sf::Vector2i tileSize, const int * tiles, size_t mapWidth, size_t mapHeight) {
    // checking if file exists and loading tileset from file path
    if (!m_tileset.loadFromFile(tileset)) {
        return false;   // TODO: throw exception
    } else {
        // Parsing texture file into separate textures and storing them inside vector
        for (int i = 0; i < tilesetXCount; i ++) {      // TODO: consider removing magic number 4 and creating (or calculating) tile number
            for (int j = 0; j < tilesetYCount; j ++) {
                sf::Texture tileTexture;
                sf::IntRect textureRect = {i * tileWidth, j * tileHeight, i * tileWidth + tileWidth, j * tileHeight + tileHeight};
                tileTexture.loadFromFile(tileset, textureRect);
                m_tilesTextures.push_back(tileTexture);
            }
        }
    }

    m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    m_vertices.resize(mapWidth * mapHeight * 12);

    for (int i = 0; i < mapWidth; i ++) {
        for (int j = 0; j < mapHeight; j ++) {
            int tileNumber = tiles[i + j * mapWidth];

            float offsetX = i * tileSize.x / 2 + j * tileSize.x / 2;
            float offsetY = j * tileSize.y / 2 - i * tileSize.y / 2;

            sf::Vertex * triangles = & m_vertices[(i + j * mapWidth) * 12];

            // so there are 4 triangles
            // point O is the center, other points are: 0 - A, 1 - B, 5 - C, 8 - D
            // ABO triangle
            triangles[0].position = sf::Vector2f(offsetX, offsetY + tileSize.y / 2);                   // A (0, h/2)
            triangles[1].position = sf::Vector2f(offsetX + tileSize.x / 2, offsetY);                   // B (w/2, 0)
            triangles[2].position = sf::Vector2f(offsetX + tileSize.x / 2, offsetY + tileSize.y / 2);  // O (w/2, h/2)
            // BOC triangle
            triangles[3].position = triangles[1].position;
            triangles[4].position = triangles[2].position;
            triangles[5].position = sf::Vector2f(offsetX + tileSize.x, offsetY + tileSize.y / 2);      // C (w, h/2)
            // AOD triangle
            triangles[6].position = triangles[0].position;
            triangles[7].position = triangles[2].position;
            triangles[8].position = sf::Vector2f(offsetX + tileSize.x / 2, offsetY + tileSize.y);      // D (w/2, h)
            // DOC triangle
            triangles[9].position = triangles[8].position;
            triangles[10].position = triangles[2].position;
            triangles[11].position = triangles[5].position;

            // ABO triangle
            triangles[0].texCoords = sf::Vector2f(0, tileSize.y / 2);               // A (0, h/2)
            triangles[1].texCoords = sf::Vector2f(tileSize.x / 2, 0);               // B (w/2, 0)
            triangles[2].texCoords = sf::Vector2f(tileSize.x / 2, tileSize.y / 2);  // O (w/2, h/2)
            // BOC triangle
            triangles[3].texCoords = triangles[1].texCoords;
            triangles[4].texCoords = triangles[2].texCoords;
            triangles[5].texCoords = sf::Vector2f(tileSize.x, tileSize.y / 2);         // C (w, h/2)
            // AOD triangle
            triangles[6].texCoords = triangles[0].texCoords;
            triangles[7].texCoords = triangles[2].texCoords;
            triangles[8].texCoords = sf::Vector2f(tileSize.x / 2, tileSize.y);         // D (w/2, h)
            // DOC triangle
            triangles[9].texCoords = triangles[8].texCoords;
            triangles[10].texCoords = triangles[2].texCoords;
            triangles[11].texCoords = triangles[5].texCoords;

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

    m_vertexPoint.setRadius(3);
    m_vertexPoint.setOrigin(3, 3);

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

    states.texture = & m_tilesTextures[0];

    target.draw(m_vertices, states);

    target.draw(m_vertexPoint);

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

void Map::getNearestVertex(sf::Vector2f mousePos) {
    int i = getCurrentlyHoveredTile(mousePos);
#if DEBUG == 1
    std::cout << i << '\n';
#endif
    // m_vertices[2].texCoords - point O, center of the tile
    // comparing mouse position relatively to tile center
    // then calculating distance to a pair of vertices
    // which indexes are: 0 - A, 1 - B, 5 - C, 8 - D (+12 for each tile)
    if (mousePos.x < m_vertices[i + 2].position.x && mousePos.y < m_vertices[i + 2].position.y) {             // upper left quadrangle, ABO
        if (sqrt(pow(mousePos.x - m_vertices[i + 0].position.x, 2) + pow(mousePos.x - m_vertices[i + 0].position.x, 2)) <=
            sqrt(pow(mousePos.x - m_vertices[i + 1].position.x, 2) + pow(mousePos.x - m_vertices[i + 1].position.x, 2))) {
            m_vertexPoint.setPosition(m_vertices[i + 0].position);
        } else {
            m_vertexPoint.setPosition(m_vertices[i + 1].position);
        }
    } else if (mousePos.x < m_vertices[i + 2].position.x && mousePos.y >= m_vertices[i + 2].position.y) {     // lower left quadrangle, AOD
        if (sqrt(pow(mousePos.x - m_vertices[i + 0].position.x, 2) + pow(mousePos.x - m_vertices[i + 0].position.x, 2)) <=
            sqrt(pow(mousePos.x - m_vertices[i + 8].position.x, 2) + pow(mousePos.x - m_vertices[i + 8].position.x, 2))) {
            m_vertexPoint.setPosition(m_vertices[i + 0].position);
        } else {
            m_vertexPoint.setPosition(m_vertices[i + 8].position);
        }
    } else if (mousePos.x >= m_vertices[i + 2].position.x && mousePos.y >= m_vertices[i + 2].position.y) {    // lower right quadrangle, DOC
        if (sqrt(pow(mousePos.x - m_vertices[i + 5].position.x, 2) + pow(mousePos.x - m_vertices[i + 5].position.x, 2)) <=
            sqrt(pow(mousePos.x - m_vertices[i + 8].position.x, 2) + pow(mousePos.x - m_vertices[i + 8].position.x, 2))) {
            m_vertexPoint.setPosition(m_vertices[i + 5].position);
        } else {
            m_vertexPoint.setPosition(m_vertices[i + 8].position);
        }
    } else if (mousePos.x >= m_vertices[i + 2].position.x && mousePos.y < m_vertices[i + 2].position.y) {     // upper right quadrangle, BOC
        if (sqrt(pow(mousePos.x - m_vertices[i + 1].position.x, 2) + pow(mousePos.x - m_vertices[i + 1].position.x, 2)) <=
            sqrt(pow(mousePos.x - m_vertices[i + 5].position.x, 2) + pow(mousePos.x - m_vertices[i + 5].position.x, 2))) {
            m_vertexPoint.setPosition(m_vertices[i + 1].position);
        } else {
            m_vertexPoint.setPosition(m_vertices[i + 5].position);
        }
    }
}

int Map::getCurrentlyHoveredTile(sf::Vector2f mousePos) {
    bool isInside = false;

    // point inside of polygon algorithm, or ray-casting algorithm
    for (int i = 0; i < m_vertices.getVertexCount(); i += 12) {
        // for each of outer points
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

void Map::elevateVertex(int tileIndex) {

}
