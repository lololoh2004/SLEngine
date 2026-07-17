#pragma once

struct GLFWwindow;

namespace render{
    bool ui_init(GLFWwindow* window);
    void ui_shutdown(GLFWwindow* window);
}
