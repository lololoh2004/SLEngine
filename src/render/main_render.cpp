#include "main_render.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "console/console_wrapper.hpp"

namespace render{
    static GLFWwindow* window = nullptr;

    bool init(int width, int height, const char* title){
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

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
        term::msg("[ImGUI] INFO : ImGUI initialized !\n");

        return true;
    }
    bool is_open(){
        if (window == nullptr)
            return false;
        return !glfwWindowShouldClose(window);
    }
    void update(){
        // Clear old frame
        glClearColor(0.12f, 0.12f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // Starting new frame (ImGUI)
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // Buttons and etc
        ImGui::ShowDemoWindow();
        // render ne frame (ImGUI)
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // Show this frame
        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glfwWindowShouldClose(window)){
            shutdown();
        }
    }
    void shutdown(){
        if (window){
            glfwDestroyWindow(window);
            glfwTerminate();
            window = nullptr;
            term::msg("[GLFW] INFO : Window closed and GLFW terminated !\n");

            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
            term::msg("[ImGUI] INFO : GUI closed and ImGUI terminated !\n");
        }
    }
}