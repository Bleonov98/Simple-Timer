#include "HUD.h"

HUDobject::HUDobject(unsigned int width, unsigned int height, Texture2D texture)
{
    this->width = width;
    this->height = height;

    projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f);

    float vertices[] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    this->textures.push_back(texture);
    this->size = texture.GetSize() * 0.5f;
    position = glm::vec2(0.0f);
}

void HUDobject::DrawHUD(glm::vec2 pos)
{
    ResourceManager::GetShader("objectShader").Use();
    ResourceManager::GetShader("objectShader").SetMatrix4("projection", projection);
    ResourceManager::GetShader("objectShader").SetVector3f("objectColour", colour);

    float vertices[] = {
        pos.x,          pos.y + size.y, 0.0f, 1.0f,
        pos.x + size.x, pos.y,          1.0f, 0.0f,
        pos.x,          pos.y,          0.0f, 0.0f,

        pos.x,          pos.y + size.y, 0.0f, 1.0f,
        pos.x + size.x, pos.y + size.y, 1.0f, 1.0f,
        pos.x + size.x, pos.y,          1.0f, 0.0f
    };

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);


    glActiveTexture(GL_TEXTURE0);
    textures[activeTexture].Bind();

    // draw mesh
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}

void HUDobject::SetNewScreenSize(unsigned int width, unsigned int height)
{
    this->width = width;
    this->height = height;

    projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f);
}

bool Button::ButtonCollision(glm::vec2 clickPos)
{
    glm::vec2 minPoint, maxPoint;

    minPoint = position;
    maxPoint = position + size;

    if (clickPos.x >= minPoint.x && clickPos.x <= maxPoint.x &&
        clickPos.y >= minPoint.y && clickPos.y <= maxPoint.y) return true;

    return false;
}
