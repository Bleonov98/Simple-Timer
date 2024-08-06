#ifndef HUD_H
#define HUD_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

#include "ResourceManager.h"

class HUDobject
{
public:

	HUDobject(unsigned int width, unsigned int height);

	void DrawHUD(glm::vec2 pos, glm::vec2 size, bool menu);

	void AddTexture(Texture2D texture) { this->textures.push_back(texture); }

	void SetNewScreenSize(unsigned int width, unsigned int height);

	~HUDobject() { glDeleteVertexArrays(1, &this->VAO); }

protected:

	int width, height;
	unsigned int VAO, VBO;

	std::vector<Texture2D> textures;

	glm::mat4 projection;
	glm::vec2 position;
};

#endif // !HUD_H