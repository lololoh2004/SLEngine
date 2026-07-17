#include "window_init.h"
#include "ui_init.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "console/console_wrapper.hpp"

namespace render{
    GLFWwindow* window = nullptr;

    bool window_init( const char* title, int width, int height){
        if (!glfwInit()){
            term::msg("[GLFW] ERROR : GLFW cannot initialize (STEP_1)\n");
            return false;
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!window){
            glfwTerminate();
            term::msg("[GLFW] ERROR : GLFW cant create window (STEP_2)\n");
            return false;
        }
        glfwMakeContextCurrent(window);
        if (!gladLoadGL()){
            glfwDestroyWindow(window);
            glfwTerminate();
            term::msg("[GLFW] ERROR : GLFW could not set up the context (STEP_3)\n");
            return false;
        }
        term::msg("[GLFW] INFO : GLFW initialized !\n");
        if (ui_init(window)){
            term::msg("[ImGUI] INFO : ImGUI initialized !\n");
        }
        return true;
    }
    bool is_open(){
        if (window == nullptr)
            return false;
        return !glfwWindowShouldClose(window);
    }
    void window_shutdown(){
        if (window){
            glfwDestroyWindow(window);
            glfwTerminate();
            window = nullptr;
            term::msg("[GLFW] INFO : Window closed and GLFW terminated !\n");
            ui_shutdown(window);
            term::msg("[ImGUI] INFO : GUI closed and ImGUI terminated !\n");
        }
    }
}
