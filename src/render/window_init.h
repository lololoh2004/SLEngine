#pragma once

struct GLFWwindow;

namespace render{
    extern GLFWwindow* window;
    bool window_init( const char* title, int width, int height);
    bool is_open();
    void window_shutdown();
}
