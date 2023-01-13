#ifndef FIELD_H
#define FIELD_H

#include "specimen.h"


class Specimen;

class Field {
  public:
    Field();
    bool has_plant();
    void update_plant_state();
    void add_plant();
    void remove_plant();
    Specimen *get_specimen();
    void set_resident( Specimen *new_resident );

  private:
    bool m_has_plant;
    Specimen *m_resident;
    unsigned int m_without_plant;
};

#endif
