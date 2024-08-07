#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "stb_image.h"

class Texture2D
{
public:

    Texture2D();

    void Generate(unsigned int width, unsigned int height, unsigned char* data);
    void Bind() const;

    //
    bool IsAlpha() { return alpha; }
    void SetAlpha(bool alpha) { this->alpha = alpha; }
    void SetFormatAlpha() { imgFormat = intFormat = GL_RGBA; }

    glm::vec2 GetSize() { return glm::vec2(width, height); }

private:

    bool alpha = false;
    unsigned int ID, width, height;
    // texture Format
    unsigned int imgFormat, intFormat;
    // texture configuration
    unsigned int wrapS, wrapT, filterMin, filterMax;
};

#endif