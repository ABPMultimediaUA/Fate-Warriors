#include "UI.h"
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include <stdio.h>
#include <glad/glad.h>    // This example is using gl3w to access OpenGL functions (because it is small). You may use glew/glad/glLoadGen/etc. whatever already works for you.
#include <GLFW/glfw3.h>
#include <cstdint>



UI::UI(uint16_t ancho_ventana, uint16_t alto_ventana){
    // Setup window
    //glfwSetErrorCallback(error_callback);
    //if (!glfwInit())
    //    return 1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    _window = glfwCreateWindow(1280, 720, "ImGui OpenGL3 example", NULL, NULL);
    glfwMakeContextCurrent(_window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1); // Enable vsync
    

    // Setup ImGui binding
    ImGui_ImplGlfwGL3_Init(_window, true);
    // Setup style
    //ImGui::StyleColorsDark();
    ImGui::StyleColorsClassic();
    _show_demo_window = true;
    _clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
}

void UI::update(){

    glfwPollEvents();
    ImGui_ImplGlfwGL3_NewFrame();
    // 1. Show a simple window.
    // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets automatically appears in a window called "Debug".
    {
        static float f = 0.0f;
        static int counter = 0;
        ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
        ImGui::ColorEdit3("COLORINES", (float*)&_clear_color); // Edit 3 floats representing a color
        ImGui::Checkbox("Demo Window", &_show_demo_window);      // Edit bools storing our windows open/close state
        if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
    {
        ImGui::Begin("VENTANA WAPA");
        ImGui::Text("POS SA QUEDAO BUENA VENTANA");
        static float yee = 0.0f;
        ImGui::SliderFloat("lel", &yee,1.0f,0.5f);
                
        ImGui::End();
    }
    // 3. Show the ImGui demo window. Most of the sample code is in ImGui::ShowDemoWindow(). Read its code to learn more about Dear ImGui!
    if (_show_demo_window)
    {
        ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
        ImGui::ShowDemoWindow(&_show_demo_window);
    }
}

void UI::render(){
    // Rendering
    int display_w, display_h;
    glfwGetFramebufferSize(_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(_clear_color.x, _clear_color.y, _clear_color.z, _clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui::Render();
    glfwSwapBuffers(_window);
}
