#ifndef FIELD_H
#define FIELD_H

#include "specimen.h"

#include <optional>

class Field {
  public:
    Field(): has_plants_( false ), resident_() {}
    ~Field();
    bool has_plants() {
        return this->has_plants_;
    }
    void update_plant_state();
    void remove_plants() {
        this->has_plants_ = false;
    }
    std::optional<Specimen *> get_specimen() {
        return this->resident_;
    }
    void set_resident( Specimen *new_resident ) {
        this->resident_ = new_resident;
    }

  private:
    bool has_plants_;
    std::optional<Specimen *> resident_;
};

#endif