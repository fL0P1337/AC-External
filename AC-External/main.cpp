#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#define DIRECTINPUT_VERSION 0x0800
#include "main.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include ".\memory.h"
#define M_PI 3.14159265358979323846

DWORD entity1_healthInt;
float entity1_xposInt;
float entity1_zposInt;
float entity1_yposInt;
float entity1_pitchInt;
DWORD player_healthInt;
float player_xposInt;
float player_zposInt;
float player_yposInt;
float player_pitchInt;

int main(int, char**)
{
    bool health = false;
    bool ammo = false;
    bool firerate = false;
    bool armor = false;
    bool aimbotX = false;


    RECT desktop;
    GetWindowRect(GetDesktopWindow(), &desktop);
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, AppClass, NULL };
    RegisterClassEx(&wc);
    hwnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_LAYERED, AppClass, AppName, WS_POPUP, (desktop.right / 2) - (WindowWidth / 2), (desktop.bottom / 2) - (WindowHeight / 2), WindowWidth, WindowHeight, 0, 0, wc.hInstance, 0);

    //SetLayeredWindowAttributes(hwnd, 0, 255, LWA_ALPHA);
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, ULW_COLORKEY);

    if (CreateDeviceD3D(hwnd) < 0)
    {
        CleanupDeviceD3D();
        UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    DefaultFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\segoeui.ttf", 20.0f, NULL, io.Fonts->GetGlyphRangesCyrillic());
    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    static bool open = true;
    DWORD dwFlag = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
    char somelogin[25] = "";
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }
        if (!open) ExitProcess(EXIT_SUCCESS);
        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();

        // health
        if (health) {
            uintptr_t ModuleBase = GetModuleBaseAddress("ac_client.exe");
            uintptr_t PlayerBase = ModuleBase + 0x109B74;
            hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
            std::vector<unsigned int> healthOffset = { 0xF8 };
            int infinitehealth = 999999;
            uintptr_t healthbaseaddress = FindDMAAddy(hProcess, PlayerBase, healthOffset);
            WriteProcessMemory(hProcess, (LPVOID)healthbaseaddress, &infinitehealth, sizeof(infinitehealth), nullptr);

        }
        else {
            uintptr_t ModuleBase = GetModuleBaseAddress("ac_client.exe");
            uintptr_t PlayerBase = ModuleBase + 0x109B74;
            hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
            std::vector<unsigned int> healthOffset = { 0xF8 };
            int infinitehealth = 100;
            uintptr_t healthbaseaddress = FindDMAAddy(hProcess, PlayerBase, healthOffset);
            WriteProcessMemory(hProcess, (LPVOID)healthbaseaddress, &infinitehealth, sizeof(infinitehealth), nullptr);
        }

        // armor
        if (armor) {
            uintptr_t ModuleBase = GetModuleBaseAddress("ac_client.exe");
            uintptr_t PlayerBase = ModuleBase + 0x109B74;
            hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
            std::vector<unsigned int> armorOffset = { 0xFC };
            int infinitearmor = 999999;;
            uintptr_t armorbaseaddress = FindDMAAddy(hProcess, PlayerBase, armorOffset);
            WriteProcessMemory(hProcess, (LPVOID)armorbaseaddress, &infinitearmor, sizeof(infinitearmor), nullptr);
        }
        else {
            uintptr_t ModuleBase = GetModuleBaseAddress("ac_client.exe");
            uintptr_t PlayerBase = ModuleBase + 0x109B74;
            hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
            std::vector<unsigned int> armorOffset = { 0xFC };
            int infinitearmor = 0;
            uintptr_t armorbaseaddress = FindDMAAddy(hProcess, PlayerBase, armorOffset);
            WriteProcessMemory(hProcess, (LPVOID)armorbaseaddress, &infinitearmor, sizeof(infinitearmor), nullptr);
        }

        //ammo
        if (ammo) {
            uintptr_t ModuleBase = GetModuleBaseAddress("ac_client.exe");
            uintptr_t PlayerBase = ModuleBase + 0x109B74;
            hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
            std::vector<unsigned int> healthOffset = { 0x150 };
            int infiniteammo = 999999;;
            uintptr_t armorbaseaddress = FindDMAAddy(hProcess, PlayerBase, healthOffset);
            WriteProcessMemory(hProcess, (LPVOID)armorbaseaddress, &infiniteammo, sizeof(infiniteammo), nullptr);
        }
        else {
            uintptr_t ModuleBase = GetModuleBaseAddress("ac_client.exe");
            uintptr_t PlayerBase = ModuleBase + 0x109B74;
            hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
            std::vector<unsigned int> healthOffset = { 0x150 };
            int infiniteammo = 20;
            uintptr_t ammobaseaddress = FindDMAAddy(hProcess, PlayerBase, healthOffset);
            WriteProcessMemory(hProcess, (LPVOID)ammobaseaddress, &infiniteammo, sizeof(infiniteammo), nullptr);
        }
        // firerate
        if (firerate) {
            uintptr_t ModuleBase = GetModuleBaseAddress("ac_client.exe");
            uintptr_t PlayerBase = ModuleBase + 0x109B74;
            hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
            std::vector<unsigned int> firerate_offset = { 0x178 };
            int firerate = -120;;
            uintptr_t armorbaseaddress = FindDMAAddy(hProcess, PlayerBase, firerate_offset);
            WriteProcessMemory(hProcess, (LPVOID)armorbaseaddress, &firerate, sizeof(firerate), nullptr);
        }
        else {
            uintptr_t ModuleBase = GetModuleBaseAddress("ac_client.exe");
            uintptr_t PlayerBase = ModuleBase + 0x109B74;
            hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
            std::vector<unsigned int> firerate_offset = { 0x178 };
            int firerate = 120;
            uintptr_t ammobaseaddress = FindDMAAddy(hProcess, PlayerBase, firerate_offset);
            WriteProcessMemory(hProcess, (LPVOID)ammobaseaddress, &firerate, sizeof(firerate), nullptr);
        }
        if (aimbotX) {
            uintptr_t ModuleBase = GetModuleBaseAddress("ac_client.exe");
            uintptr_t PlayerBase = ModuleBase + 0x109B74;
            uintptr_t entitylist = ModuleBase + 0x10F4F8;
            uintptr_t entity1_zpos = FindDMAAddy(hProcess, entitylist, entity1_zpos_offset);
            uintptr_t entity1_ypos = FindDMAAddy(hProcess, entitylist, entity1_ypos_offset);
            uintptr_t entity1_xpos = FindDMAAddy(hProcess, entitylist, entity1_xpos_offset);
            uintptr_t player_zpos = FindDMAAddy(hProcess, PlayerBase, zpos_offset);
            uintptr_t player_ypos = FindDMAAddy(hProcess, PlayerBase, ypos_offset);
            uintptr_t player_xpos = FindDMAAddy(hProcess, PlayerBase, xpos_offset);
            uintptr_t entity1_health = FindDMAAddy(hProcess, entitylist, entity1_health_offset);
            uintptr_t entity1_pitch = FindDMAAddy(hProcess, entitylist, entity1_pitch_offset);
            uintptr_t player_pitch = FindDMAAddy(hProcess, PlayerBase, pitch_offset);
            ReadProcessMemory(hProcess, (void*)player_xpos, &player_xposInt, sizeof(player_xposInt), nullptr);
            ReadProcessMemory(hProcess, (void*)player_ypos, &player_yposInt, sizeof(player_yposInt), nullptr);
            ReadProcessMemory(hProcess, (void*)player_zpos, &player_zposInt, sizeof(player_zposInt), nullptr);
            ReadProcessMemory(hProcess, (void*)entity1_xpos, &entity1_xposInt, sizeof(entity1_yposInt), nullptr);
            ReadProcessMemory(hProcess, (void*)entity1_ypos, &entity1_yposInt, sizeof(entity1_yposInt), nullptr);
            ReadProcessMemory(hProcess, (void*)entity1_zpos, &entity1_zposInt, sizeof(entity1_zposInt), nullptr);
            ReadProcessMemory(hProcess, (void*)entity1_health, &entity1_healthInt, sizeof(entity1_health), nullptr);
            ReadProcessMemory(hProcess, (void*)entity1_pitch, &entity1_pitchInt, sizeof(entity1_pitchInt), 0);
            float abspos_x = entity1_xposInt - player_xposInt;
            float abspos_y = entity1_yposInt - player_yposInt;
            float abspos_z = entity1_zposInt - player_zposInt;

            float azimuth_xy = atan2f(abspos_y, abspos_x);

            float yaw = (float)(azimuth_xy * (180.0 / M_PI));
            if (abspos_y < 0) {
                abspos_y *= -1;
            }
            if (abspos_y < 5) {
                if (abspos_x < 0) {
                    abspos_x *= -1;
                }
                abspos_y = abspos_x;
            }
            if (entity1_healthInt > 100) {
                entityslot += 0x4;
            }
            yaw += 90;
            WriteProcessMemory(hProcess, (void*)player_zpos, &yaw, sizeof(yaw), 0);
            WriteProcessMemory(hProcess, (void*)player_pitch, &entity1_pitchInt, sizeof(entity1_pitchInt), 0);
        }

        ImGui::NewFrame();

        ImGui::SetNextWindowSize(ImVec2(WindowWidth, WindowHeight), ImGuiCond_Once);
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
        {
            ImGui::Begin(AppName, &open, dwFlag);
            ImGui::AlignTextToFramePadding();
            static int state;
            if (ImGui::Button("Inject")) {
                GD_window = FindWindow(0, "AssaultCube");
                if (GD_window == NULL) {
                }
                else {
                    state = 1;
                    procID = GetProcessId("ac_Client.exe");
                }
            }
            ImGui::Text("isOpened: %d", state);
            ImGui::Text("procID: %d", GetWindowThreadProcessId(GD_window, &procID));
            ImGui::Checkbox("Infinite Health", &health);
            ImGui::SameLine();
            ImGui::Checkbox("Infinite Armor", &armor);
            ImGui::Checkbox("Infinite Ammo", &ammo);
            ImGui::SameLine();
            ImGui::Checkbox("FireRate", &firerate);
            ImGui::Checkbox("Aimbot", &aimbotX);
        }
        ImGui::End();

        ImGui::EndFrame();

        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) ResetDevice();
        {
        }
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    CleanupDeviceD3D();
    DestroyWindow(hwnd);
    UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}
