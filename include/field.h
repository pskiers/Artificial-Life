#ifndef FIELD_H
#define FIELD_H

#include "specimen.h"

#include <optional>

class Specimen;

class Field {
  public:
    Field(): m_has_plant( false ), m_resident( nullptr ) {}
    bool has_plant();
    void update_plant_state();
    void remove_plant();
    Specimen *get_specimen();
    void set_resident( Specimen *new_resident );

  private:
    bool m_has_plant;
    Specimen *m_resident;
};

#endif
