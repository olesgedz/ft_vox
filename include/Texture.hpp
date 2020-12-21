#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include "vox.hpp"
#include <string>

class BasicTexture
{
    public:
        void load(const std::string &fileName);
        void bind();
        void unbind();
    private:
        GLuint m_textureID;
};

#endif