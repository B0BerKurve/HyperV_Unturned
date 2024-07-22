#pragma once

//#include "../c_features.h"
#include "../includes.h"
#include "keybind.h"

class c_menu
{

public:

	void render();
	bool initalize();

    ImFont* combo_arrow;
    ImFont* medium_bigger;
    ImFont* weapons;
    ImFont* medium;
    ImFont* bold;

    color AccentColor = color{ 52.f, 195.f, 235.f, 255.f };//52, 195, 235
    //color SecondAccentColor = color{ 69 / 255.f, 140 / 255.f, 247 / 255.f, 1.f };

    float anim_speed = 0.05f, m_alpha = 1.f;

    bool opened = true;
    ImVec2 screen_res{ 000, 000 };
    ImVec2 window_size{ 600, 500 };

    ImVec2 window_pos{ (GetSystemMetrics(SM_CXSCREEN) / 2) - window_size.x, (GetSystemMetrics(SM_CYSCREEN) / 2) - window_size.y };
    //ImVec2 window_pos{ (1920 / 2)-window_size.x, (1080 / 2)-window_size.y };
    DWORD  window_flags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollWithMouse;

}; inline c_menu menu;