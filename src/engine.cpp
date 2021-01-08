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
	for(auto model : models)
		model->meshes.clear();
	models.clear();
	int length = scene.ents.size();
	for (int i = 0; i < length; ++i)
		delete scene.ents[i];
	std::cout << "Engine off" << std::endl;
}

void Engine::init_engine(int width, int height)
{
	controls.set_camera(&cam);
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
	controls.yaw = cam.Yaw;
	controls.pitch = cam.Pitch;
	rend.init();

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
//			std::cout << "fps - " << fps << std::endl;
			fps = 0;
		}
		old_time = glfwGetTime();

        ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

		//cam. = 8.0f * delta_time;


//		if (controls.keys[GLFW_KEY_X])
//			cam.pos = cam.pos - cam.speed * cam.right;
//		if (controls.keys[GLFW_KEY_Z])
//			cam.pos = cam.pos + cam.speed * cam.right;
//		if (controls.keys[GLFW_KEY_W])
//			cam.pos = cam.pos + cam.speed * cam.front;
//		if (controls.keys[GLFW_KEY_S])
//			cam.pos = cam.pos - cam.speed * cam.front;
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cam.ProcessKeyboard(FORWARD, delta_time);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cam.ProcessKeyboard(BACKWARD, delta_time);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cam.ProcessKeyboard(LEFT, delta_time);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cam.ProcessKeyboard(RIGHT, delta_time);
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			cam.ProcessKeyboard(UP, delta_time);
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			cam.ProcessKeyboard(DOWN, delta_time);
//		cam.yaw = controls.yaw;
//		cam.pitch = controls.pitch;

		//cam.update_free();
//		rend.draw_skybox(&skybox, &cam);
		rend.draw_scene(&animator, &scene, &cam, this);
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

