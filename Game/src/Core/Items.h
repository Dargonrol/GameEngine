#pragma once

enum class ItemType
{
    NONE = 0,
    SHIELD,
    MEDIC,
    BOOST,
    STRENGTH
};

typedef struct Item
{
    ItemType itemType;
    int liveTime;
} Item;
