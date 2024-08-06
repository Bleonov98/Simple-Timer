#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Program.h"

// settings
const unsigned int SCR_WIDTH = 1600, SCR_HEIGHT = 900;
unsigned int newWidth = 0, newHeight = 0;
bool screenSizesChanged = false;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// input
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void char_callback(GLFWwindow* window, unsigned int codepoint);
void mouse_callback(GLFWwindow* window, int button, int action, int mods);
void processCursor(GLFWwindow* window);

Program timer(SCR_WIDTH, SCR_HEIGHT);

int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Simple Timer", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);
	glfwSetCharCallback(window, char_callback);
	glfwSetMouseButtonCallback(window, mouse_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	gladLoadGL();
	glEnable(GL_DEPTH_TEST);

	timer.Init();

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.05f, 0.11f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processCursor(window);
		timer.ProcessInput(deltaTime);

		timer.Update(deltaTime);
		
		timer.Render(deltaTime);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);

	newWidth = width;
	newHeight = height;

	timer.SetScreenSize(newWidth, newHeight);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_F4 && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			timer.Keys[key] = true;
		else if (action == GLFW_RELEASE) {
			timer.Keys[key] = false;
			timer.KeysProcessed[key] = false;
		}
	}
}

void char_callback(GLFWwindow* window, unsigned int codepoint)
{
	timer.inputChar = codepoint;
}

void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button >= 0 && button < 8)
	{
		if (action == GLFW_PRESS) timer.mouseKeys[button] = true;
		else if (action == GLFW_RELEASE) {
			timer.mouseKeys[button] = false;
			timer.mKeysProcessed[button] = false;
		}


		double xpos, ypos;

		// getting cursor position
		glfwGetCursorPos(window, &xpos, &ypos);

		timer.xMouse = xpos;
		timer.yMouse = ypos;
	}
}

void processCursor(GLFWwindow* window)
{
	double xpos, ypos;

	// getting cursor position for hover feature
	glfwGetCursorPos(window, &xpos, &ypos);
	
	timer.xCursor = xpos;
	timer.yCursor = ypos;
}
