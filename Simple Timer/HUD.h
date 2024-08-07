#ifndef HUD_H
#define HUD_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <functional>

#include "ResourceManager.h"

class HUDobject
{
public:

	HUDobject(unsigned int width, unsigned int height, Texture2D texture);

	void DrawHUD(glm::vec2 pos);

	void AddTexture(Texture2D texture) { this->textures.push_back(texture); }

	void SetPosition(glm::vec2 position) { this->position = position; }
	void SetSize(glm::vec2 size) { this->size = size; }
	void SetColour(glm::vec3 colour) { this->colour = colour; }

	glm::vec2 GetPosition() { return position; }
	glm::vec2 GetSize() { return size; }

	void SetNewScreenSize(unsigned int width, unsigned int height);

	~HUDobject() { glDeleteVertexArrays(1, &this->VAO); }

protected:

	int width, height;
	unsigned int VAO, VBO;
	size_t activeTexture = 0;

	std::vector<Texture2D> textures;

	glm::mat4 projection;
	glm::vec2 position, size;
	glm::vec3 colour = glm::vec3(1.0f);
};

class Button : public HUDobject 
{
public:

	Button(unsigned int width, unsigned int height, Texture2D texture) : HUDobject(width, height, texture) {};
	
	bool ButtonCollision(glm::vec2 clickPos);
	void SetFunction(std::function<void()> func) { this->function = func; }

private:

	std::function<void()> function;

};

#endif // !HUD_H