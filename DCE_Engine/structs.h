#pragma once
#include <cstdint>
#include "entity.h"

enum EntityType { BRIDGE, TOWN, ROAD_JUNCTION };
enum Faction { RED, BLUE, CIV, NONE };

struct Location {
    float latitude;
    float longitude;
};

struct RawEntity {
    long id;
    EntityType type;
    std::string name;
    float lat;
    float lon;
    float value;
    float size;
};

struct EntityGraph {
    float value;
    Entity* nearbyEntity;
};