#include <gb/gb.h>
#include "zeldasSpellData.h"

#ifdef CGB
    UINT16 *_spellEquipped = (UINT16 *)0xcb34;
    UINT16 *_zaEngineFlags = (UINT16 *)0xcb50;
#else
    UINT16 *_spellEquipped = (UINT16 *)0xcb33;
    UINT16 *_zaEngineFlags = (UINT16 *)0xcb4f;
#endif

UBYTE UseDeepVramSearch()
{
    return (*_zaEngineFlags & (1 << 0)) != 0;
}

void InitZeldasSpell()
{
    UBYTE _save = _current_bank;
    UBYTE useDeepVramSearch = UseDeepVramSearch();
    
    SWITCH_ROM(6);
        LoadSpell(*_spellEquipped, useDeepVramSearch);    
    SWITCH_ROM(_save);
}
