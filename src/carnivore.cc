#include "carnivore.h"

Carnivore::Carnivore(Field *position, unsigned int speed, unsigned int sight_range, unsigned int sight_angle,
                     unsigned int time_to_sleep):
                     Specimen( position, speed, sight_range, sight_angle, time_to_sleep ){}

void Carnivore::describeMyself() {
    std::cout << "I am the beast!\n";
}