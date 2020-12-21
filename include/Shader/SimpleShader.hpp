#ifndef SIMPLESHADER_HPP
#define SIMPLESHADER_HPP
#include "glmCombine.hpp"
#include "Shader/Shader.hpp"
#include "Matrix.hpp"
namespace Shader {
class SimpleShader : public ShaderProgram {
 public:
  SimpleShader(/* args */);
  ~SimpleShader();
  void getUniformLocations() override ;
  void setViewMatrix(const glm::mat4  &matrix);
  void setModelMatrix(const glm::mat4  &matrix);
  void setProjMatrix(const glm::mat4  &matrix);
 private:
  /* data */
  void bindAttributes() override;
  GLuint m_locationViewMatrix     = 0;
  GLuint m_locationModelMatrix    = 0;
  GLuint m_locationProjMatrix     = 0;
};
}

#endif