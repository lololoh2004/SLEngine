#include "render_main.h"
#include "bgfx/bgfx.h"
#include "GLFW/glfw3.h"

namespace render{
    uint32_t width = 1600;
    uint32_t height = 900;

    int init(){
        if (!glfwInit()){
            return -1;
        }
        glfwInit();
        GLFWwindow* window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
        if (!window) {
            glfwTerminate();
            return -1;
        }
        bgfx:init();
        return 0;
    }
}