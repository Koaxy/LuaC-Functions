#include <Windows.h>
#include <memory>

#define aslr(x) (x - 0x400000) + (DWORD)GetModuleHandleA(NULL)

namespace roblox_addresses
{
	DWORD luaC_step_addr = aslr(0x1724470);
}

namespace roblox_offsets
{
   DWORD gcobjMarked = 2;
   DWORD gcobjmemcat = 0;
   DWORD gcobject_tt = 1;
   DWORD gc_currentwhite = 20;
   DWORD activememcat = 4;
   DWORD totalBytes = 40;
   DWORD gcThresHold = 48;
}

typedef void(__cdecl* rLuaC_st)(DWORD rL, bool assist);
rLuaC_st r_luaC_step = *reinterpret_cast<rLuaC_st>(roblox_addresses::luaC_step_addr);


class rapi
{
public:
   rapi();
   ~rapi();
   // getGlobalState, returns roblox's global state.

   DWORD getGlobalState(DWORD rL);

   void r_luaC_checkgc(DWORD rL); // Checks the garbage collector
   void r_luaC_initobj(DWORD rL, DWORD obj, DWORD tt);
   
};
