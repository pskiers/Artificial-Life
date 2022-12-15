#include "herbivore.h"

Herbivore::Herbivore(Field *position, unsigned int speed, unsigned int sight_range, unsigned int sight_angle,
                     unsigned int time_to_sleep):
                     Specimen( position, speed, sight_range, sight_angle, time_to_sleep ) {}

void Herbivore::describeMyself() {
    std::cout << "Cattle  ";
}