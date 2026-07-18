#include "ui_el_logic.h"

#include "imgui.h"

namespace render{
    void begin_window(std::string_view title) {
        ImGui::Begin(title.data());
    }
    void add_text(std::string_view text){
        ImGui::Text("%s", text.data());
    }
    bool add_button(std::string_view text){
        return ImGui::Button(text.data());
    }
    void end_window() {
        ImGui::End();
    }
}
