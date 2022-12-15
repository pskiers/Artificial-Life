#include "map.h"

Field *Map::get_field( const unsigned int x, const unsigned int y ) {
    if ( x > m_height || y > m_width )
        return nullptr;
    return &m_fields[x][y];
}