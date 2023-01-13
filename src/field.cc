#include <random>
#include "field.h"

Field::Field(): m_has_plant( false ), m_resident( nullptr ), m_without_plant(0) {}

void Field::update_plant_state() {
    if (m_has_plant) {
        return;
    }
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> distribution(0.0, 1.0);
    auto random = distribution(rng);
    if ( random + m_without_plant * INCREASE_RATIO > THRESHOLD) {
        m_has_plant = true;
        m_without_plant = 0;
    }
    ++ m_without_plant;
}

bool Field::has_plant() {
    return m_has_plant;
}

void Field::add_plant() {
    m_has_plant = true;
}

void Field::remove_plant() {
    m_has_plant = false;
}

Specimen *Field::get_specimen() {
    return m_resident;
}

void Field::set_resident( Specimen *new_resident ) {
    m_resident = new_resident;
    if ( new_resident && m_has_plant && new_resident->accept_plant())
        m_has_plant = false;
}