#pragma once

#define  IMGUI_DEFINE_MATH_OPERATORS
//#include "imgui.h"
#include "..//../ImGui/imgui.h"
#include "..//../ImGui/imgui_internal.h"
#include <windows.h>
#include <ios>
#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

struct laner_custom {
    bool tab(const char* label, bool selected);

    int active_tab;
};
inline laner_custom l_custom;
