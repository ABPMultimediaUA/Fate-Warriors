/*
#include "Game.h"
#include "Interfaz/Motor.h"
#include "Tiempo/Time.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

const float t_min_IA=(1000/15);


// Función que da el nº de fps en el ultimo segundo
void _imprime_fps(Time* _time, uint8_t& _frames, uint32_t _tiempo_por_frame, uint32_t& _iteraciones) {
	_frames++;
	_tiempo_por_frame = _time->get_current_sin_pausas() - _iteraciones*1000;
	if(_tiempo_por_frame>=1000) {
		_tiempo_por_frame-=1000;

		std::clog << (int)_frames << " fps\n";

		_frames=0;
		_iteraciones++;
	}
}


// Main del juego
int main(){
	srand((int)time(0)); // Inicia la semilla del rand

	Game* _juego = Game::game_instancia();
	//_juego->crea_partida();
	Time* time=Time::Instance();

	double _h_ultimo_update=time->get_current_sin_pausas();
	double _interpolacion;
	Time* _time = Time::Instance();

    Motor* _motor = Motor::Motor_GetInstance();

    //uint8_t _frames = 0;
    //uint32_t _tiempo_por_frame = 0, _iteraciones = 0;

	while(_motor->getIrrlichtDevice()->run()){
		//Evento para cerrar la ventana

		// Recoge inputs
		_juego->recibir_inputs();

		time->set_tiempo_desde_ultimo_update(time->get_current_sin_pausas() - _h_ultimo_update);//actualizacion del reloj
		//std::cout << "Tiempo desde update " << time->get_tiempo_desde_ultimo_update() << std::endl;
		//update
                
		if(time->get_tiempo_desde_ultimo_update()>t_min_IA){
			_h_ultimo_update=time->get_current_sin_pausas();
            //std::cout << "pre update" << std::endl;
            //std::cout << "Tiempo update " << time->get_tiempo_desde_ultimo_update() << "\n";
            _juego->update(time->get_tiempo_desde_ultimo_update());
            time->set_tiempo_desde_ultimo_update(time->get_current_sin_pausas() - _h_ultimo_update);
            //std::cout << "post update" << std::endl;
		}


		//Render
		_interpolacion=fmin(1.f,(double)time->get_tiempo_desde_ultimo_update()/t_min_IA);
		_juego->render(_interpolacion);

		//_imprime_fps(_time, _frames, _tiempo_por_frame, _iteraciones);

		//std::cout << "Interpolaicon " << _interpolacion	 << std::endl;
		//_time->cambiar_antes_a_ahora();
	}
			
	_juego->fin_partida();

	delete _time;

	delete _juego;

	return 0;
}

*/

// ImGui - standalone example application for GLFW + OpenGL 3, using programmable pipeline
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)
// (GL3W is a helper library to access OpenGL functions since there is no standard header to access modern OpenGL functions easily. Alternatives are GLEW, Glad, etc.)

#include "gui/imgui.h"
#include "gui/imgui_impl_glfw_gl3.h"
#include <stdio.h>
#include <glad/glad.h>    // This example is using gl3w to access OpenGL functions (because it is small). You may use glew/glad/glLoadGen/etc. whatever already works for you.
#include <GLFW/glfw3.h>

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}

int main(int, char**)
{
    // Setup window
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        return 1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui OpenGL3 example", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1); // Enable vsync
    

    // Setup ImGui binding
    ImGui_ImplGlfwGL3_Init(window, true);

    // Setup style
    //ImGui::StyleColorsDark();
    ImGui::StyleColorsClassic();

    bool show_demo_window = true;
    bool show_another_window = false;
    bool algo = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();
        ImGui_ImplGlfwGL3_NewFrame();

        // 1. Show a simple window.
        // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets automatically appears in a window called "Debug".
        {
            static float f = 0.0f;
            static int counter = 0;
            ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
            ImGui::ColorEdit3("COLORINES", (float*)&clear_color); // Edit 3 floats representing a color

            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
            ImGui::Checkbox("Booleanooooo", &algo);
            ImGui::Checkbox("Another Window", &show_another_window);

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);
            ImGui::Text("pues se ve que hay texto: %d", algo);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }

        {
            ImGui::Begin("VENTANA WAPA");
            ImGui::Text("POS SA QUEDAO BUENA VENTANA");

            static float yee = 0.0f;
            ImGui::SliderFloat("lel", &yee,1.0f,0.5f);
                    
            ImGui::End();
        }

        // 2. Show another simple window. In most cases you will use an explicit Begin/End pair to name your windows.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // 3. Show the ImGui demo window. Most of the sample code is in ImGui::ShowDemoWindow(). Read its code to learn more about Dear ImGui!
        if (show_demo_window)
        {
            ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
            ImGui::ShowDemoWindow(&show_demo_window);
        }

        // Rendering
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();
        glfwSwapBuffers(window);
    }

    // Cleanup
    //ImGui_ImplGlfwGL3_Shutdown();
    glfwTerminate();

    return 0;
}

