#include "MinHook.h"
#include "Menu/Menu.hpp"

#include "Reset.hpp"

using tReset = HRESULT(__stdcall*)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
tReset oReset;

HRESULT __stdcall hkReset(IDirect3DDevice9* self, D3DPRESENT_PARAMETERS* presentationParameters)
{
    menu->Reset(true);
    HRESULT result = oReset(self, presentationParameters);
    menu->Reset(false);
    return result;
}

void Reset::InstallHook()
{
    MH_STATUS status;

    if (const auto& module = reinterpret_cast<DWORD>(GetModuleHandleA("d3d9.dll")))
    {
        if (const auto& target = reinterpret_cast<LPVOID>(module + 0xE3880))
        {
            status = MH_CreateHook(target, &hkReset, reinterpret_cast<LPVOID*>(&oReset));
            if (status != MH_OK)
            {
                // err handle
            }

            status = MH_EnableHook(target);
            if (status != MH_OK)
            {
                // err handle
            }
        }
    }
}

void Reset::RemoveHook()
{
    MH_STATUS status;

    if (const auto& module = reinterpret_cast<DWORD>(GetModuleHandleA("d3d9.dll")))
    {
        if (const auto& target = reinterpret_cast<LPVOID>(module + 0xE3880))
        {
            status = MH_DisableHook(target);
            if (status != MH_OK)
            {
                // err handle
            }

            status = MH_RemoveHook(target);
            if (status != MH_OK)
            {
                // err handle
            }
        }
    }
}