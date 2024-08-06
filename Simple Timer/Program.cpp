#include "Program.h"

#include <irrklang/irrKlang.h>
using namespace irrklang;
ISoundEngine* sound = irrklang::createIrrKlangDevice();

TextRenderer* text;

void Program::Init()
{
	LoadResources();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	text = new TextRenderer(this->width, this->height);
	text->Load("../fonts/CutiveMono.ttf", 48);
}

void Program::LoadResources()
{
	// sounds
	sound->addSoundSourceFromFile("../sounds/name.mp3");
}

void Program::ProcessInput(float dt)
{

}

void Program::ProcessButtons()
{
}

void Program::Update(float dt)
{
}

void Program::Render(float dt)
{
	text->RenderText("25:00", glm::vec2(width / 2.0f - 9.0f, height / 2.0f - 9.0f));
}

void Program::SetScreenSize(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;

	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
}
