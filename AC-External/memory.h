#include <iostream>
#include <Windows.h>
#include "main.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#define DIRECTINPUT_VERSION 0x0800

DWORD procID;
HWND GD_window;

struct Player {
    char unknown1[4];
    float x;
    float y;
    float z;
    char unknown2[0x30];
    float yaw;
    float pitch;
    char unknown3[0x2f0];
    int dead;
};


// Our player
Player* player = NULL;

uintptr_t GetModuleBaseAddress(const char* modName) {
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procID);
    if (hSnap != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry)) {
            do {
                if (!strcmp(modEntry.szModule, modName)) {
                    CloseHandle(hSnap);
                    return (uintptr_t)modEntry.modBaseAddr;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
}
uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets)
{
    uintptr_t addr = ptr;
    for (unsigned int i = 0; i < offsets.size(); ++i)
    {
        ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
        addr += offsets[i];
    }
    return addr;
}
float euclidean_distance(float x, float y) {
    return sqrtf((x * x) + (y * y));
}
uintptr_t ModuleBase = GetModuleBaseAddress("ac_client.exe");
HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);

uintptr_t PlayerBase = ModuleBase + 0x109B74;
uintptr_t entitylist = ModuleBase + 0x10F4F8;
uintptr_t entityslot = 0x4;
std::vector<unsigned int> entity1_xpos_offset = { entityslot, 0x4 };
std::vector<unsigned int> entity1_ypos_offset = { entityslot, 0x8 };
std::vector<unsigned int> entity1_zpos_offset = { entityslot, 0x40 };
std::vector<unsigned int> entity1_health_offset = { entityslot, 0xF8 };
std::vector<unsigned int> zpos_offset = { 0x40 };
std::vector<unsigned int> ypos_offset = { 0x8 };
std::vector<unsigned int> xpos_offset = { 0x4 };
std::vector<unsigned int> entity1_pitch_offset = { 0x4, 0x44 };
std::vector<unsigned int> pitch_offset = { 0x44 };