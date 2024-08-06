#ifndef RESOURCE_H
#define RESOURCE_H

#include "Shader.h"
#include "Texture2D.h"

#include <string>
#include <map>

class ResourceManager
{
public:

	// shaders
	static Shader LoadShader(const char* vShader, const char* fShader, std::string name);
	static Shader GetShader(std::string name);

	// Textures
	static Texture2D LoadTexture(const char* fileName, bool alpha, std::string name);
	static Texture2D GetTexture(std::string name);

private:

	ResourceManager() {};

	inline static std::map<std::string, Shader> shaders;
	inline static std::map<std::string, Texture2D> textures;

	static Texture2D LoadTextureFromFile(const char* fileName, bool alpha);
	static Shader LoadShaderFromFile(const char* vShader, const char* fShader);

};


#endif // !RESOURCE_H