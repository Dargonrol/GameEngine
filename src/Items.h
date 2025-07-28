#pragma once

enum class ItemType
{
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
