#ifndef ZELDAS_INVENTORY_CORE_H
#define ZELDAS_INVENTORY_CORE_H

#include <gb/gb.h>

typedef enum
{
    ZELDA_WEAPON_UNDEFINED = 0,
    ZELDA_WEAPON_WAND,
    ZELDA_WEAPON_BOWANDARROW,
    ZELDA_WEAPON_BROADSWORD,
    ZELDA_WEAPON_CALM,
    ZELDA_WEAPON_FEATHER,
    ZELDA_WEAPON_RINGSOFFIRE,
    ZELDA_WEAPON_FIRESTORM,
    ZELDA_WEAPON_GOLDNECKLACE,
    ZELDA_WEAPON_HAMMER,
    ZELDA_WEAPON_JADEAMULET,
    ZELDA_WEAPON_JOUST,
    ZELDA_WEAPON_JADERING,
    ZELDA_WEAPON_DAGGER,
    ZELDA_WEAPON_NOISE,
    ZELDA_WEAPON_PYROS,
    ZELDA_WEAPON_ROARSTICK,
    ZELDA_WEAPON_SHORTAXE,
    ZELDA_WEAPON_TURQUOISERING,
    ZELDA_WEAPON_BOOMERANG,
} ZELDA_WEAPONS;

typedef enum
{
    ZELDA_TREASURE_UNDEFINED = 0,
    ZELDA_TREASURE_LADDER,
    ZELDA_TREASURE_CANDLE,
    ZELDA_TREASURE_BONE,
    ZELDA_TREASURE_BLACKORB,
    ZELDA_TREASURE_BOUQUET,
    ZELDA_TREASURE_TICKETB,
    ZELDA_TREASURE_EMPTYBOTTLE,
    ZELDA_TREASURE_WATERBOTTLE,
    ZELDA_TREASURE_COAL,
    ZELDA_TREASURE_DIAMOND,
    ZELDA_TREASURE_FLUTE,
    ZELDA_TREASURE_PLANK,
    ZELDA_TREASURE_KNIFE,
    ZELDA_TREASURE_HARP,
    ZELDA_TREASURE_TICKETA,
    ZELDA_TREASURE_LIFEPOTION,
    ZELDA_TREASURE_RUG,
    ZELDA_TREASURE_MAGICSHIELD,
    ZELDA_TREASURE_SALTCELLAR,
    ZELDA_TREASURE_RAFT,
    ZELDA_TREASURE_REDBOOTS,
    ZELDA_TREASURE_REPELLENT,
    ZELDA_TREASURE_REDBOW,
    ZELDA_TREASURE_VIALOFWIND,
    ZELDA_TREASURE_GOLDENBOOTS,
    // ZELDA_TREASURE_COMPASS1,
    // ZELDA_TREASURE_COMPASS2,
    // ZELDA_TREASURE_COMPASS3,
    // ZELDA_TREASURE_COMPASS4,
    // ZELDA_TREASURE_COMPASS5,
    // ZELDA_TREASURE_COMPASS6,
    // ZELDA_TREASURE_COMPASS7,
    // ZELDA_TREASURE_MAP1,
    // ZELDA_TREASURE_MAP2,
    // ZELDA_TREASURE_MAP3,
    // ZELDA_TREASURE_MAP4,
    // ZELDA_TREASURE_MAP5,
    // ZELDA_TREASURE_MAP6,
    // ZELDA_TREASURE_MAP7,
    // ZELDA_TREASURE_KEY,
} ZELDA_TREASURES;

/**
 * Initialise the inventory screen by combining the static background 
 * with the dynamic weapon and treasure panels.
 */
void InitZeldaInventory();

/**
 * Call back when the user has interacted with the inventory.
 * Either clicking on a scroll arrow or equipping an item.
 */
void CheckForInventoryInteraction();

#endif
