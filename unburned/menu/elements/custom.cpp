#include "custom.hpp"
using namespace ImGui;

ImColor FastColorLerp(ImColor start, ImColor end, float stage)
{
    ImVec4 lerp = ImLerp(
        ImVec4(start.Value.x, start.Value.y, start.Value.z, start.Value.w),
        ImVec4(end.Value.x, end.Value.y, end.Value.z, end.Value.w),
        stage);

    return ImGui::ColorConvertFloat4ToU32(lerp);
}
float FastFloatLerp(std::string identifier, bool state, float min, float max, float speed) {

    static std::unordered_map<std::string, float> valuesMapFloat;
    auto value = valuesMapFloat.find(identifier);

    if (value == valuesMapFloat.end()) {
        valuesMapFloat.insert({ identifier, min });
        value = valuesMapFloat.find(identifier);
    }

    const float frameRateSpeed = speed * (1.f - ImGui::GetIO().DeltaTime);

    if (state) {
        if (value->second < max)
            value->second += frameRateSpeed;
    }
    else {
        if (value->second > min)
            value->second -= frameRateSpeed;
    }

    value->second = std::clamp(value->second, min, max);

    return value->second;
}

bool laner_custom::tab(const char* label, bool selected) {
    ImGuiWindow* window = GetCurrentWindow();
    ImGuiID id = window->GetID(label);

    ImVec2 label_size = CalcTextSize(label, 0, 1);
    ImVec2 pos = window->DC.CursorPos;

    auto draw = window->DrawList;

    ImRect rect(pos, pos + ImVec2(100, 30));
    ItemAdd(rect, id);
    ItemSize(rect, GetStyle().FramePadding.y);

    bool hovered, held;
    bool pressed = ButtonBehavior(rect, id, &hovered, &held, NULL);

    //draw->AddRectFilled(rect.Min, rect.Max - ImVec2(0,5), ImColor(255, 255, 255));
    float anim = FastFloatLerp(std::string(label).append("tab.anim"), selected, 0.f, 1.f, 0.04f);
    auto text_color = FastColorLerp(GetColorU32(ImGuiCol_TextDisabled), GetColorU32(ImGuiCol_Text), anim);
    draw->AddText(ImVec2(rect.GetCenter().x - label_size.x / 2, rect.GetCenter().y - label_size.y / 2), text_color, label);

    static float line_pos = 0.f;
    line_pos = ImLerp(line_pos, selected ? rect.Min.x - window->Pos.x : line_pos, 0.05f);
    draw->AddRectFilled({ window->Pos.x + line_pos , rect.Max.y - 5 }, { window->Pos.x + line_pos + 100 , rect.Max.y }, ImColor(52, 195, 235), 5);

    SameLine(0, 1);
    return pressed;
}
