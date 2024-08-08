#include "Program.h"

#include <irrklang/irrKlang.h>
using namespace irrklang;
ISoundEngine* sound = irrklang::createIrrKlangDevice();

TextRenderer* numbers;
TextRenderer* text;

void Program::Init()
{
	LoadResources();

	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	numbers = new TextRenderer(this->width, this->height);
	numbers->Load("../fonts/Jacques.ttf", 64);
}

void Program::LoadResources()
{
	// sounds
	sound->addSoundSourceFromFile("../sounds/name.mp3");

	// shaders
	ResourceManager::LoadShader("../shaders/vShader.vx", "../shaders/fShader.ft", "objectShader");

	// textures
	for (size_t i = 0; i < 2; i++)
	{
		ResourceManager::LoadTexture(("../textures/background" + std::to_string(i) + ".jpg").c_str(), false, "background" + std::to_string(i));
		std::shared_ptr<HUDobject> background = std::make_shared<HUDobject>(width, height, ResourceManager::GetTexture("background" + std::to_string(i)));

		background->SetPosition(glm::vec2(0.0f));
		background->SetSize(glm::vec2(width, height));
		background->wColour = false;

		backgroundList.push_back(background);
	}

	// clock text
	ResourceManager::LoadTexture("../textures/clock.png", true, "clockIcon");
	std::shared_ptr<HUDobject> clock = std::make_shared<HUDobject>(width, height, ResourceManager::GetTexture("clockIcon"));
	clock->SetPosition(glm::vec2(width / 2.0f - clock->GetSize().x / 2, 150.0f));

	hudList.push_back(clock);
	mainHudList.push_back(clock);

	// play button
	ResourceManager::LoadTexture("../textures/play.png", true, "playIcon");
	ResourceManager::LoadTexture("../textures/pause.png", true, "pauseIcon");
	std::shared_ptr<Button> play = std::make_shared<Button>(width, height, ResourceManager::GetTexture("playIcon"));

	play->AddTexture(ResourceManager::GetTexture("pauseIcon"));
	play->SetPosition(glm::vec2(clock->GetPosition().x + clock->GetSize().x - play->GetSize().x * 1.5f, 150.0f + clock->GetSize().y / 2.0f - play->GetSize().y / 2.0f));

	hudList.push_back(play);
	mainHudList.push_back(play);

	buttonList.push_back(play);
	mainButtonList.push_back(play);

	// stop button
	ResourceManager::LoadTexture("../textures/stop.png", true, "stopIcon");
	std::shared_ptr<Button> stop = std::make_shared<Button>(width, height, ResourceManager::GetTexture("stopIcon"));

	stop->SetPosition(glm::vec2(clock->GetPosition().x + stop->GetSize().x / 2.0f, 150.0f + clock->GetSize().y / 2.0f - stop->GetSize().y / 2.0f));
	
	hudList.push_back(stop);
	mainHudList.push_back(stop);

	buttonList.push_back(stop);
	mainButtonList.push_back(stop);

	// theme button
	ResourceManager::LoadTexture("../textures/theme.png", true, "themeIcon");
	std::shared_ptr<Button> theme = std::make_shared<Button>(width, height, ResourceManager::GetTexture("themeIcon"));

	theme->SetPosition(glm::vec2(50.0f));
	theme->SetSize(glm::vec2(30.0f));
	theme->SetFunction(&Program::ToggleTheme, this);

	hudList.push_back(theme);
	mainHudList.push_back(theme);

	buttonList.push_back(theme);
	mainButtonList.push_back(theme);

	// settings page button
	ResourceManager::LoadTexture("../textures/settings.png", true, "settingsIcon");
	std::shared_ptr<Button> settings = std::make_shared<Button>(width, height, ResourceManager::GetTexture("settingsIcon"));

	settings->SetSize(glm::vec2(30.0f));
	settings->SetPosition(glm::vec2(width - (50.0f + settings->GetSize().x), 50.0f));
	settings->SetFunction(&Program::ChangePage, this, settingsPage);

	hudList.push_back(settings);
	mainHudList.push_back(settings);

	buttonList.push_back(settings);
	mainButtonList.push_back(settings);

	// exit page button
	ResourceManager::LoadTexture("../textures/cross.png", true, "crossIcon");
	std::shared_ptr<Button> exit = std::make_shared<Button>(width, height, ResourceManager::GetTexture("crossIcon"));

	exit->SetSize(glm::vec2(30.0f));
	exit->SetPosition(glm::vec2(width - (50.0f + exit->GetSize().x), 50.0f));
	exit->SetFunction(&Program::ChangePage, this, mainPage);

	hudList.push_back(exit);
	settingsHudList.push_back(exit);

	buttonList.push_back(exit);
	settingsButtonList.push_back(exit);
}

void Program::ProcessInput(float dt)
{
	// mouse click
	if (this->mouseKeys[GLFW_MOUSE_BUTTON_LEFT] && !mKeysProcessed[GLFW_MOUSE_BUTTON_LEFT]) {
		ProcessButtons();
		mKeysProcessed[GLFW_MOUSE_BUTTON_LEFT] = true;
	}
	
	// mouse hover
	for (auto& button : buttonList)
	{
		if (button->ButtonCollision(glm::vec2(xCursor, yCursor))) {
			if (appTheme == darkTheme) button->SetColour(glm::vec3(0.8f, 0.0f, 0.85f));
			else button->SetColour(glm::vec3(1.0f));
		}
		else {
			if (appTheme == darkTheme) button->SetColour(glm::vec3(1.0f));
			else button->SetColour(glm::vec3(0.0f));
		}
	}
}

void Program::ProcessButtons()
{
	if (tmPage == mainPage) {
		for (auto button : mainButtonList)
		{
			if (button->ButtonCollision(glm::vec2(xMouse, yMouse))) button->CallFunction();
		}
	}
	else if (tmPage == settingsPage) {
		for (auto button : settingsButtonList)
		{
			if (button->ButtonCollision(glm::vec2(xMouse, yMouse))) button->CallFunction();
		}
	}

}

void Program::Update(float dt)
{

}

void Program::Render(float dt)
{
	backgroundList[0]->DrawHUD(backgroundList[0]->GetPosition());

	if (tmPage == mainPage) {
		numbers->RenderText("25:00", glm::vec2(width / 2.0f - 33.0f * 2.5f, 35.0f));

		for (auto& object : mainHudList)
		{
			object->DrawHUD(object->GetPosition());
		}
	}
	else if (tmPage == settingsPage) {
		for (auto& object : settingsHudList)
		{
			object->DrawHUD(object->GetPosition());
		}
	}
}

void Program::ToggleTheme()
{
	std::shared_ptr<HUDobject> temp = backgroundList[0];
	backgroundList[0] = backgroundList[1];
	backgroundList[1] = temp;

	if (appTheme == darkTheme) {
		for (auto& object : hudList)
		{
			object->SetColour(glm::vec3(0.0f));
		}

		numbers->colour = glm::vec3(0.0f);

		appTheme = lightTheme;
	}
	else {
		for (auto& object : hudList)
		{
			object->SetColour(glm::vec3(1.0f));
		}

		numbers->colour = glm::vec3(1.0f);

		appTheme = darkTheme;
	}
}

void Program::ChangePage(Page page)
{
	tmPage = page;
}

void Program::SetScreenSize(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;

	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
}
