#include <iostream>

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

//Included our shader file
#include "Shader.h"

//size of the window
const GLint width = 800, height = 600;



int main()
{
	//initialize GLFW
	glfwInit();

	//Set required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//Create the window
	GLFWwindow *window = glfwCreateWindow(width, height, "Advanced Programming", nullptr, nullptr);

	//set the frame buffer to the screen size
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Did creating the window fail?
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	// Set this to true so GLEW knows to use a modern function pointers and extensions
	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to Initialize GLEW" << std::endl;

		return EXIT_FAILURE;
	}

	glViewport(0, 0, screenHeight, screenHeight);

	Shader ourShader("Resources/Shaders/core.vs", "Resources/Shaders/core.frag");

	GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		0.5, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f 
	};

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);


	float frameCount = 0.0f;

	//Game loop
	while (!glfwWindowShouldClose(window))
	{
		frameCount++;
		std::cout << "Frame: " << frameCount << std::endl;
		system("CLS");
		glfwPollEvents();

		//0 - 1
		//RGBA color of the clear to background
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//draw
		ourShader.Use();

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);


		glfwSwapBuffers(window);
	}

	//Wipe buffers
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	//terminate the program
	glfwTerminate();

	return EXIT_SUCCESS;
}