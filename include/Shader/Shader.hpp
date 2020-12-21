#ifndef SHADER_HPP
#define SHADER_HPP
#include "vox.hpp"
#include <string>

namespace Shader
{
    class ShaderProgram
    {
        public:
            ShaderProgram(const std::string& vertexShaderFile,
                           const std::string& fragmentShaderFile);
            ~ShaderProgram();
            void bind();
			  void unbind();
		void loadFloat(GLuint location, float value);
		void loadVector2(GLuint location, const glm::vec2& value);
		void loadMatrix4(GLuint location, const glm::mat4 & matrix);
        protected:
      		virtual  void getUniformLocations() = 0;
      		GLuint getID() const;
            void     bindAttribute(GLuint location, const  GLchar * name); 
            virtual  void bindAttributes() = 0;


        private:
            GLuint m_programID;
    };
}
#endif