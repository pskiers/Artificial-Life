#include "map.h"

Field *Map::get_field_by_idx( const unsigned int index ) {
    return &m_fields[index];
}
// this is temporary function that will be replaced with iterator over class

Field *Map::get_field(const unsigned int width, const unsigned int height) {
    if (width >= m_width || height >= m_height) {
        return nullptr;
    }
    return &m_fields[width + m_width * height];
}

Map::Map( const unsigned int height, const unsigned int width ):
    m_height( height ), m_width( width ), m_fields( height * width ) {}

unsigned int Map::getHeight() {
    return m_height;
}

unsigned int Map::getWidth() {
    return m_width;
}