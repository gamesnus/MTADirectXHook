#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

#include "Menu.hpp"

WNDPROC        wndProc;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProcHandler(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    ImGui_ImplWin32_WndProcHandler(window, message, wParam, lParam);

    if (message == WM_KEYDOWN && wParam == VK_INSERT)
    {
        menu->ToggleState();
    }

    const auto& io = ImGui::GetIO();
    if (menu->GetState() && (io.WantCaptureMouse || io.WantCaptureKeyboard))
    {
        return true;
    }

    return CallWindowProcA(wndProc, window, message, wParam, lParam);
}

void Menu::Init(IDirect3DDevice9* device)
{
    if (initialized == true)
    {
        return;
    }

    D3DDEVICE_CREATION_PARAMETERS deviceParameters;
    device->GetCreationParameters(&deviceParameters);

    wndProc = (WNDPROC)SetWindowLongW(deviceParameters.hFocusWindow, GWL_WNDPROC, (LONG)WndProcHandler);

    ImGui::CreateContext();
    ImGui_ImplWin32_Init(deviceParameters.hFocusWindow);
    ImGui_ImplDX9_Init(device);

    ImGui_ImplDX9_InvalidateDeviceObjects();

    initialized = true;
}

void Menu::Draw()
{
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    if (state)
    {
        ImGui::ShowDemoWindow(&state);
    }

    ImGui::GetIO().MouseDrawCursor = state;

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void Menu::Reset(bool before)
{
    if (before)
    {
        ImGui_ImplDX9_InvalidateDeviceObjects();
        return;
    }

    ImGui_ImplDX9_CreateDeviceObjects();
}