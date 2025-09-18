#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>

namespace Pong {

struct Entity {
    std::string name;
    std::vector<Component> components;
};

} // Pong

#endif //ENTITY_H
