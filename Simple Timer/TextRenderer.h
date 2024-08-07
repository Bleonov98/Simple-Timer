#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "ResourceManager.h"

struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // size of glyph
    glm::ivec2   Bearing;   // offset from baseline to left/top of glyph
    unsigned int Advance;   // horizontal offset to advance to next glyph
};

class TextRenderer
{
public:

    TextRenderer(unsigned int width, unsigned int height);

    void Load(std::string font, unsigned int fontSize);

    void RenderText(std::string text, glm::vec2 position, float scale = 1.0f);

    glm::vec3 colour = glm::vec3(1.0f);
private:

    std::map<char, Character> Characters;

    unsigned int VAO, VBO;

};

#endif // TEXT_RENDERER_H