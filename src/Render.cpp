#include "Render.h"
#include "glad.h"
#include <string>
#include <iostream>
#include "glm/glm.hpp"
#include "engine.h"
#include "World.h"
void Render::init()
{
	projection = glm::perspective(60.0 * M_PI / 180.0, 1280.0 / 720.0, 0.1, 100.0);
}

void    Render::draw_child(Entity* ent, Animator *animator, Scene *scene, Camera *cam, mat4 ani_model)
{
//    std::cout << "draw child" << std::endl;
//    Model *mod = ent->mod;
//    glUseProgram(mod->shader_id);
//    glBindVertexArray(mod->vao);
//    mat4 model = mat4(1.0f);
//    model = translate(model, ent->position);
//    model = rotate(model, ent->angle);
//    if (ent->ID == 1)
//        ani_model = animator->animations["run"][0].GetAnimationMatrix(*ent, Engine::delta_time) * ani_model;
//    model = ani_model * model;
//    mat4 tmp_model = model;
//    model = scale(model, ent->e_scale);
//
//
//    unsigned int model_loc = glGetUniformLocation(mod->shader_id, "u_M");
//    glUniformMatrix4fv(model_loc, 1, GL_FALSE, model.mat);
//    unsigned int view_loc = glGetUniformLocation(mod->shader_id, "u_V");
//    glUniformMatrix4fv(view_loc, 1, GL_FALSE, cam->view.mat);
//    unsigned int proj_loc = glGetUniformLocation(mod->shader_id, "u_P");
//    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, projection.mat);
//
//    glUniform1i(glGetUniformLocation(mod->shader_id, "lightNumb"), 3);
//    glUniform3f(glGetUniformLocation(mod->shader_id, "lightPos"), scene->point_lights[0].position.x, scene->point_lights[0].position.y, scene->point_lights[0].position.z);
//    glUniform3f(glGetUniformLocation(mod->shader_id, "viewPos"), cam->pos.x, cam->pos.y, cam->pos.z);
//    glUniform3f(glGetUniformLocation(mod->shader_id, "material.diffuse"), ent->color.x, ent->color.y, ent->color.z);
//    glUniform3f(glGetUniformLocation(mod->shader_id, "material.specular"), 0.4f, 0.4f, 0.4f);
//    glUniform1f(glGetUniformLocation(mod->shader_id, "material.shininess"), 16.0f);
//    glUniform3f(glGetUniformLocation(mod->shader_id, "light.ambient"), 0.3f, 0.3f, 0.3f);
//    glUniform3f(glGetUniformLocation(mod->shader_id, "light.diffuse"), 0.8f, 0.8f, 0.8f);
//    glUniform3f(glGetUniformLocation(mod->shader_id, "light.specular"), 0.5f, 0.5f, 0.5f);
//    glUniform1f(glGetUniformLocation(mod->shader_id, "light.constant"), 1.0f);
//    glUniform1f(glGetUniformLocation(mod->shader_id, "light.linear"), 0.045f);
//    glUniform1f(glGetUniformLocation(mod->shader_id, "light.quadratic"), 0.0075f);
//    glDrawArrays(GL_TRIANGLES, 0, mod->ind_number);
//    int child_numb = ent->childrens.size();
//    for (int j = 0; j < child_numb; ++j)
//        draw_child(ent->childrens[j], animator, scene, cam, ani_model);
}

void Render::draw_scene(Animator *animator, Scene *scene, Camera *cam, Engine *eng)
{

//	Shader shader("shaders/SimpleVertex.glsl", "shaders/SimpleFragment.glsl");
	static int j = 0;

	if (j == 0)
	{
		j = 1;
		World::instance()->player_cam = cam; //std::make_shared<Camera> cam);

		World::instance()->UpdateWorld();
		for (auto &[key, value] : World::instance()->world)
		{
			Entity *chunkE = new Entity();
			eng->add_entity(chunkE);
			chunkE->set_model(&value->model);
		}
	}
	int length = scene->ents.size();
	for (int i = 0; i < length; i++)
	{
		Entity *ent = scene->ents[i];

		Model *mod = ent->mod;
		Mesh *mesh1 = &mod->meshes[0];

		World::instance()->shader->use();
		glm::mat4 model = glm::mat4(1.0f);
		World::instance()->shader->setMat4("projMatrix", projection);
		World::instance()->shader->setMat4("viewMatrix", cam->GetViewMatrix());
		World::instance()->shader->setMat4("modelMatrix", model);
		mesh1->draw();
	}

//	int length = scene->ents.size();
//
//       Entity *ent = scene->ents[0];
//		Model *mod = ent->mod;
//		Mesh * mesh1 = &mod->meshes[0];
//
//			mesh1->shader->use();
//			glm::mat4 model = glm::mat4(1.0f);
//			mesh1->shader->setMat4("projMatrix", projection);
//
//			mesh1->shader->setMat4("viewMatrix", cam->GetViewMatrix());
////			cout << glm::to_string(cam->view) << endl;
//
//				mesh1->shader->setMat4("modelMatrix", model);
//
//				mesh1->draw();
//		for( Mesh &mesh1 : mod->meshes)
//		{
//		glGenBuffers(1, &vbo);
//		glGenVertexArrays(1, &voa);
//		glBindVertexArray(voa);
//		glBindBuffer(GL_ARRAY_BUFFER, vbo);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(a) * sizeof(float ), a, GL_STATIC_DRAW);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//		glEnableVertexAttribArray(0);
//		for (auto ent : scene->ents)
//		{
//			for (auto &mod : ent->mod)
//			{
//				mod,.shader->use();
//
//
//			glm::mat4 model = glm::mat4(1.0f);
//				mesh.shader->setMat4("projMatrix", projection);
//
//				mesh.shader->setMat4("viewMatrix", cam->GetViewMatrix());
////			cout << glm::to_string(cam->view) << endl;
//
//				mesh.shader->setMat4("modelMatrix", model);
////
//				mesh.draw();
//			}
//		}
		//}
//		}




//        Model *mod = ent->mod;
//        glUseProgram(mod->shader_id);
//        //glActiveTexture(GL_TEXTURE0);
//        //glBindTexture(GL_TEXTURE_2D, mod->texture);
//        glBindVertexArray(mod->vao);
//
////        if (i == 2)
////            ent->rotate(0.0f, 20.0f * Engine::delta_time, 0.0f);
//
//        mat4 model = mat4(1.0f);
//        model = translate(model, ent->position);
//        model = rotate(model, ent->angle);
        // model = translate(model, ent->position);
//
//
//            mat4 ani_model = mat4(1.0f); //= animator->animations[0].GetAnimationMatrix(*ent, Engine::delta_time);
//
//            model = model * ani_model;
//        model = scale(model, ent->e_scale);

//        glm::mat4 m = glm::mat4(1.0f);
//        glm::vec3 p = glm::vec3(ent->position.x, ent->position.y, ent->position.z);
//        glm::vec3 s = glm::vec3(ent->e_scale.x, ent->e_scale.y, ent->e_scale.z);
//        m = glm::translate(m, p);
//        m = glm::rotate(m, glm::radians(ent->angle.x), glm::vec3(1.0f, 0.0f, 0.0f));
//        m = glm::rotate(m, glm::radians(ent->angle.y), glm::vec3(0.0f, 1.0f, 0.0f));
//        m = glm::rotate(m, glm::radians(ent->angle.z), glm::vec3(0.0f, 0.0f, 1.0f));
//        m = glm::scale(m, s);
//        if (i == 2) {
//            for (int i = 0; i < 16; ++i)
//                std::cout << model.mat[i] << " ";
//            std::cout << "\n";
//            for (int i = 0; i < 16; ++i)
//                std::cout << glm::value_ptr(m)[i] << " ";
//            std::cout << "\n";
//        }

//		unsigned int model_loc = glGetUniformLocation(mod->shader_id, "u_M");
//		glUniformMatrix4fv(model_loc, 1, GL_FALSE, model.mat);
//		unsigned int view_loc = glGetUniformLocation(mod->shader_id, "u_V");
//		glUniformMatrix4fv(view_loc, 1, GL_FALSE, cam->view.mat);
//		unsigned int proj_loc = glGetUniformLocation(mod->shader_id, "u_P");
//		glUniformMatrix4fv(proj_loc, 1, GL_FALSE, projection.mat);
//
//        glUniform1i(glGetUniformLocation(mod->shader_id, "lightNumb"), 3);
//        glUniform3f(glGetUniformLocation(mod->shader_id, "lightPos"), scene->point_lights[0].position.x, scene->point_lights[0].position.y, scene->point_lights[0].position.z);
//        glUniform3f(glGetUniformLocation(mod->shader_id, "viewPos"), cam->pos.x, cam->pos.y, cam->pos.z);
//        glUniform3f(glGetUniformLocation(mod->shader_id, "material.diffuse"), ent->color.x, ent->color.y, ent->color.z);
//        glUniform3f(glGetUniformLocation(mod->shader_id, "material.specular"), 0.4f, 0.4f, 0.4f);
//        glUniform1f(glGetUniformLocation(mod->shader_id, "material.shininess"), 16.0f);
//        glUniform3f(glGetUniformLocation(mod->shader_id, "light.ambient"), 0.3f, 0.3f, 0.3f);
//        glUniform3f(glGetUniformLocation(mod->shader_id, "light.diffuse"), 0.8f, 0.8f, 0.8f);
//        glUniform3f(glGetUniformLocation(mod->shader_id, "light.specular"), 0.5f, 0.5f, 0.5f);
//        glUniform1f(glGetUniformLocation(mod->shader_id, "light.constant"), 1.0f);
//        glUniform1f(glGetUniformLocation(mod->shader_id, "light.linear"), 0.045f);
//        glUniform1f(glGetUniformLocation(mod->shader_id, "light.quadratic"), 0.0075f);
//        glDrawArrays(GL_TRIANGLES, 0, mod->ind_number);
//
//        int child_numb = ent->childrens.size();
//        for (int j = 0; j < child_numb; ++j)
//            draw_child(ent->childrens[j], animator, scene, cam, ani_model);
}

//void Render::draw_pbr(Scene* scene, Camera* cam)
//{
//	int length = scene->ents.size();
//	for (int i = 0; i < length; ++i)
//	{
//		Entity* ent = scene->ents[i];
//		Model* mod = ent->mod;
//		glUseProgram(mod->shader_id);
//		glBindVertexArray(mod->vao);
//
//        mat4 model = mat4(1.0f);
//        model = translate(model, ent->position);
//        model = rotate(model, ent->angle);
//        model = scale(model, ent->e_scale);
//
//		unsigned int model_loc = glGetUniformLocation(mod->shader_id, "u_M");
//		glUniformMatrix4fv(model_loc, 1, GL_FALSE, model.mat);
//		unsigned int view_loc = glGetUniformLocation(mod->shader_id, "u_V");
//		glUniformMatrix4fv(view_loc, 1, GL_FALSE, cam->view.mat);
//		unsigned int proj_loc = glGetUniformLocation(mod->shader_id, "u_P");
//		glUniformMatrix4fv(proj_loc, 1, GL_FALSE, projection.mat);
//
//		glUniform3f(glGetUniformLocation(mod->shader_id, "albedo"), 0.5f, 0.0f, 0.0f);
//		glUniform1f(glGetUniformLocation(mod->shader_id, "ao"), 1.0f);
//		glUniform3f(glGetUniformLocation(mod->shader_id, "camPos"), cam->pos.x, cam->pos.y, cam->pos.z);
//		glUniform1f(glGetUniformLocation(mod->shader_id, "metallic"), 0.9f);
//		glUniform3f(glGetUniformLocation(mod->shader_id, "roughness"), 0.9f, 0.05f, 1.0f);
//		glUniform3f(glGetUniformLocation(mod->shader_id, "lightPositions[0]"), scene->point_lights[0].position.x, scene->point_lights[0].position.y, scene->point_lights[0].position.z);
//		glUniform3f(glGetUniformLocation(mod->shader_id, "lightColors[0]"), scene->point_lights[0].color.x, scene->point_lights[0].color.y, scene->point_lights[0].color.z);
//		glUniform3f(glGetUniformLocation(mod->shader_id, "lightPositions[1]"), scene->point_lights[1].position.x, scene->point_lights[1].position.y, scene->point_lights[1].position.z);
//		glUniform3f(glGetUniformLocation(mod->shader_id, "lightColors[1]"), scene->point_lights[1].color.x, scene->point_lights[1].color.y, scene->point_lights[1].color.z);
//		glUniform3f(glGetUniformLocation(mod->shader_id, "lightPositions[2]"), scene->point_lights[2].position.x, scene->point_lights[2].position.y, scene->point_lights[2].position.z);
//		glUniform3f(glGetUniformLocation(mod->shader_id, "lightColors[2]"), scene->point_lights[2].color.x, scene->point_lights[2].color.y, scene->point_lights[2].color.z);
//		glUniform3f(glGetUniformLocation(mod->shader_id, "lightPositions[3]"), scene->point_lights[3].position.x, scene->point_lights[3].position.y, scene->point_lights[3].position.z);
//		glUniform3f(glGetUniformLocation(mod->shader_id, "lightColors[3]"), scene->point_lights[3].color.x, scene->point_lights[3].color.y, scene->point_lights[3].color.z);
////		for (int j = 0; j < scene->point_lights.size(); ++j)
////		{
////			glUniform3f(glGetUniformLocation(mod->shader_id, ("lightPositions[" + std::to_string(j) + " ]").c_str()), scene->point_lights[j].position.x, scene->point_lights[j].position.y, scene->point_lights[j].position.z);
////			glUniform3f(glGetUniformLocation(mod->shader_id, ("lightColors[" + std::to_string(j) + " ]").c_str()), scene->point_lights[j].color.x, scene->point_lights[j].color.y, scene->point_lights[j].color.z);
////		}
//		glDrawArrays(GL_TRIANGLES, 0, mod->ind_number);
//	}
//}
//
//void	Render::draw_skybox(Skybox *skybox, Camera* cam)
//{
//	glDepthMask(GL_FALSE);
//	glUseProgram(skybox->shader_id);
//	mat3 tmp = mat3(cam->view);
//	mat4 view = mat4(tmp);
////    for (int i = 0; i < 16; ++i)
////        std::cout << cam->view.mat[i] << " ";
////    std::cout << "\n";
////	for (int i = 0; i < 16; ++i)
////	    std::cout << view.mat[i] << " ";
////    std::cout << "\n";
//    unsigned int view_loc = glGetUniformLocation(skybox->shader_id, "u_V");
//	glUniformMatrix4fv(view_loc, 1, GL_FALSE, view.mat);
//	unsigned int proj_loc = glGetUniformLocation(skybox->shader_id, "u_P");
//	glUniformMatrix4fv(proj_loc, 1, GL_FALSE, projection.mat);
//	glBindVertexArray(skybox->vao);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->texture);
//	glDrawArrays(GL_TRIANGLES, 0, 36);
//	glDepthMask(GL_TRUE);
//}
