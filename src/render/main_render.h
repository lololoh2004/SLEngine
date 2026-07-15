#pragma once

namespace render{
    bool init(int width, int height, const char* title);
    bool is_open();
    void update();
    void shutdown();
}