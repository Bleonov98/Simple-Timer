#include "Program.h"

#include <irrklang/irrKlang.h>
using namespace irrklang;
ISoundEngine* sound = irrklang::createIrrKlangDevice();

TextRenderer* text;

void Program::Init()
{
	LoadResources();

	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	text = new TextRenderer(this->width, this->height);
	text->Load("../fonts/Jacques.ttf", 64);
}

void Program::LoadResources()
{
	// sounds
	sound->addSoundSourceFromFile("../sounds/name.mp3");

	// shaders
	ResourceManager::LoadShader("../shaders/vShader.vx", "../shaders/fShader.ft", "objectShader");

	// textures

	// clock text
	ResourceManager::LoadTexture("../textures/clock.png", true, "clockIcon");
	std::shared_ptr<HUDobject> clock = std::make_shared<HUDobject>(width, height, ResourceManager::GetTexture("clockIcon"));
	clock->SetPosition(glm::vec2(width / 2.0f - clock->GetSize().x / 2, 150.0f));
	hudList.push_back(clock);

	// play button
	ResourceManager::LoadTexture("../textures/play.png", true, "playIcon");
	ResourceManager::LoadTexture("../textures/pause.png", true, "pauseIcon");

	std::shared_ptr<Button> play = std::make_shared<Button>(width, height, ResourceManager::GetTexture("playIcon"));

	play->AddTexture(ResourceManager::GetTexture("pauseIcon"));
	play->SetPosition(glm::vec2(clock->GetPosition().x + clock->GetSize().x - play->GetSize().x * 1.5f, 150.0f + clock->GetSize().y / 2.0f - play->GetSize().y / 2.0f));
	play->SetFunction([]() {
		
	});

	hudList.push_back(play);
	buttonList.push_back(play);

	// stop button
	ResourceManager::LoadTexture("../textures/stop.png", true, "stopIcon");
	std::shared_ptr<Button> stop = std::make_shared<Button>(width, height, ResourceManager::GetTexture("stopIcon"));
	stop->SetPosition(glm::vec2(clock->GetPosition().x + stop->GetSize().x / 2.0f, 150.0f + clock->GetSize().y / 2.0f - stop->GetSize().y / 2.0f));
	hudList.push_back(stop);
	buttonList.push_back(stop);
}

void Program::ProcessInput(float dt)
{
	if (this->Keys[GLFW_KEY_T] && !KeysProcessed[GLFW_KEY_T]) {
		ToggleTheme();
		KeysProcessed[GLFW_KEY_T] = true;
	}
}

void Program::ProcessButtons()
{
}

void Program::Update(float dt)
{
}

void Program::Render(float dt)
{
	text->RenderText("25:00", glm::vec2(width / 2.0f - 33.0f * 2.5f, 35.0f));

	for (auto& object : hudList)
	{
		object->DrawHUD(object->GetPosition());
	}
}

void Program::ToggleTheme()
{
	if (appTheme == darkTheme) {
		for (auto& object : hudList)
		{
			object->SetColour(glm::vec3(0.0f));
		}

		text->colour = glm::vec3(0.0f);

		appTheme = lightTheme;
	}
	else {
		for (auto& object : hudList)
		{
			object->SetColour(glm::vec3(1.0f));
		}

		text->colour = glm::vec3(1.0f);

		appTheme = darkTheme;
	}
}

void Program::SetScreenSize(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;

	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
}
