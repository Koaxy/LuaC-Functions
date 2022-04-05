#include "rapi.h"


#define cast_to(t, exp) ((t)(exp))
#define cast_int(i) cast_to(int, (i))
#define bitmask(b) (1 << (b))
#define bit2mask(b1, b2) (bitmask(b1) | bitmask(b2))

#define WHITE0BIT 0
#define WHITE1BIT 1
#define BLACKBIT 2
#define FIXEDBIT 3
#define WHITEBITS bit2mask(WHITE0BIT, WHITE1BIT)

#define r_luaC_white(g) cast_to(uint8_t, (roblox_offsets::gc_currentwhite) & WHITEBITS)

rapi::rapi()
{
    // Initialize the RAPI
}
rapi::~rapi()
{
 // Derefrence the pointer to the RAPI class
}

DWORD rapi::getGlobalState(DWORD rL)
{
    DWORD gs = (rL + 0x18) - *reinterpret_cast<DWORD*>(rL + 0x18);
    return gs;
}

void rapi::r_luaC_initobj(DWORD rL, DWORD obj, DWORD tt)
{
    DWORD globalState = this->getGlobalState(rL);
    obj = *reinterpret_cast<DWORD*>(rL + roblox_offsets::gcobjMarked) = r_luaC_white(globalState);
    obj = *reinterpret_cast<DWORD*>(rL + roblox_offsets::gcobject_tt) = tt;
    obj = *reinterpret_cast<DWORD*>(rL + roblox_offsets::gcobjmemcat) = roblox_offsets::activememcat;
}

void rapi::r_luaC_checkgc(DWORD rL)
{
    // Check the garbage collector
    if (this->getGlobalState(rL + roblox_offsets::totalBytes) >= this->getGlobalState(rL + roblox_offsets::gcThresHold)) 
    {
        r_luaC_step(rL, true);
    }
}
