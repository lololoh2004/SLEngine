#include "render_frame.h"

#include "window_init.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "lua/lua_env.hpp"

namespace render{
    void update(){
        // Clear old frame
        glClearColor(0.12f, 0.12f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // Draw UI
        //ImGui::ShowDemoWindow();
        draw_ui();
        // Show this frame
        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glfwWindowShouldClose(window)){
            window_shutdown();
        }
    }
    void draw_ui(){
        // Starting new frame (ImGUI)
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // Buttons, texts and etc
        //ImGui::ShowDemoWindow();
        lua::call_callback("on_render_ui");
        // render ne frame (ImGUI)
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}
