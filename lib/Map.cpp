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

    m_vertices.resize(mapWidth * mapHeight * 12);
    m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);

    for (int i = 0; i < mapWidth; i ++) {
        for (int j = 0; j < mapHeight; j ++) {
            int tileNumber = tiles[i + j * mapHeight];

            float offsetX = i * tileSize.x / 2 + j * tileSize.x / 2;
            float offsetY = j * tileSize.y / 2 - i * tileSize.y / 2;

            sf::Vertex * triangles = & m_vertices[(i + j * mapHeight) * 12];

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

void Map::isMapClicked(const sf::Vector2f & mousePos) {

    for (Tile & tile: m_tiles) {
        if (tile.isInsideTile(mousePos)) {
            // tile.elevateVertex(m_vertexPoint.getPosition());
#if DEBUG == 1
            std::cout << tile.getIndex().x << ' ' << tile.getIndex().y << std::endl;
#endif
        }
    }
}

void Map::isMapHovered(const sf::Vector2f & mousePos) {
    for (Tile & tile: m_tiles) {
        if (tile.isInsideTile(mousePos)) {
            m_vertexPoint.setFillColor(sf::Color::White);
            m_vertexPoint.setPosition(tile.getNearestVertex(mousePos));
#if DEBUG == 1
//            std::cout << tile.getIndex().x << ' ' << tile.getIndex().y << std::endl;
#endif
        }
    }
}

void Map::move(sf::View & view, sf::Vector2f offset) {
    view.move(offset);
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    states.texture = & m_tilesTextures[0];

    target.draw(m_vertices, states);

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
