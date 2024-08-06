#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "ResourceManager.h"
#include "TextRenderer.h"
#include "HUD.h"

enum Page {
	mainPage,
	settingsPage,
};

class Program
{
public:

	Program(const int width, const int height) {
		this->width = width, this->height = height;
		projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	};

	// Initialization, Loading
	void Init();
	void LoadResources();

	// Main, GamePlay
	void ProcessInput(float dt);
	void ProcessButtons();
	void Update(float dt);

	// Render
	void Render(float dt);

	// Utility
	void SetScreenSize(unsigned int width, unsigned int height);
	~Program() {};

	// - - - - 
	bool Keys[1024], KeysProcessed[1024], mouseKeys[8], mKeysProcessed[8];
	char inputChar;
	double xMouse, yMouse, xCursor, yCursor;

private:

	Page tmPage = mainPage;

	// basics
	int width, height;
	glm::mat4 projection;
	glm::mat4 view;

	// objects
	std::vector<HUDobject> objectList;
};

#endif // !GAME_H