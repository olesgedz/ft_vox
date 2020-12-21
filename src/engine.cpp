#include "engine.h"
#include "glad.h"
#include <iostream>
#include "glm/glm.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

double Engine::delta_time = 0.0f;
Engine::~Engine()
{
	int length = models.size();
	for (int i = 0; i < length; ++i)
	{
		models[i]->vertices.clear();
		models.clear();
	}
	length = scene.ents.size();
	for (int i = 0; i < length; ++i)
		delete scene.ents[i];
	std::cout << "Engine off" << std::endl;
}

void Engine::init_engine(int width, int height)
{
	if (!glfwInit())
		exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(width, height, "42 run", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGL())
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetKeyCallback(window, key_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetWindowUserPointer(window, &controls);
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	controls.yaw = cam.yaw;
	controls.pitch = cam.pitch;
	rend.init();
	std::vector<std::string> faces;
	faces.push_back("res/cubemaps/right.jpg");
	faces.push_back("res/cubemaps/left.jpg");
	faces.push_back("res/cubemaps/top.jpg");
	faces.push_back("res/cubemaps/bottom.jpg");
	faces.push_back("res/cubemaps/front.jpg");
	faces.push_back("res/cubemaps/back.jpg");
	skybox.init(faces);
	skybox.set_shader("res/shaders/skybox_vert.glsl", "res/shaders/skybox_frag.glsl");

    IMGUI_CHECKVERSION();
	ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
   // (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

}

void Engine::run_engine()
{
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	old_time = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);

		delta_time = glfwGetTime() - old_time;
		timer += delta_time;
		fps++;
		if (timer >= 1.0)
		{
			timer -= 1.0;
			std::cout << "fps - " << fps << std::endl;
			fps = 0;
		}
		old_time = glfwGetTime();

        ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

		cam.speed = 8.0f * delta_time;
		if (controls.keys[GLFW_KEY_W])
			cam.pos = cam.pos + cam.speed * cam.front;
		if (controls.keys[GLFW_KEY_S])
			cam.pos = cam.pos - cam.speed * cam.front;
		if (controls.keys[GLFW_KEY_A])
			cam.pos = cam.pos - cam.speed * normalize(cross(cam.front, cam.up));
		if (controls.keys[GLFW_KEY_D])
			cam.pos = cam.pos + cam.speed * normalize(cross(cam.front, cam.up));
		cam.yaw = controls.yaw;
		cam.pitch = controls.pitch;

		cam.update_free();
		rend.draw_skybox(&skybox, &cam);
		rend.draw_scene(&animator, &scene, &cam);
		//rend.draw_pbr(&scene, &cam);


        ImGui::Text("Use buttons to change animation"); // Display some text (you can use a format strings too)
        if (ImGui::Button("Idle"))
            std::cout << "Idle anim" << std::endl;
        ImGui::Button("Run");
        ImGui::Button("Jump");
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
		if(close_eng)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
}

void Engine::add_model(Model *mod)
{
	models.push_back(mod);
}

void Engine::add_entity(Entity *ent)
{
	scene.add_entity(ent);
}

void Engine::set_player(Entity *ent)
{
	player = ent;
	rend.player = ent;
}

void Engine::add_light_source(glm::vec3 l_pos, glm::vec3 color)
{
	scene.add_light_source(l_pos, color);
}

