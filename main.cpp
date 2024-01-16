#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

GLfloat vertices[] =	//vertices coordinates
{
	//external triangle
	-1.0f, -1.0f, 0.0f,	//bottom left corner
	1.0f, -1.0f, 0.0f,	//bottom right corner
	0.0f, 1.0f, 0.0f,	//top corner
	
	//cut out triangle
	-0.5f, 0.0f, 0.0f,	//top left corner
	0.5f, 0.0f, 0.0f,	//top right corner
	0.0f, -1.0f, 0.0f,	//bottom corner
};

GLuint indices[] =	//coordinates of each triangle
{
	0, 5, 3,	//bottom left triangle
	5, 1, 4,	//bottom right triangle
	3, 4, 2,	//top triangle
};

int main() 
{
	glfwInit();

	//-----------------------------------------------------------------------------
	// GLFW CONTEXTUALIZATION
	//-----------------------------------------------------------------------------
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);		//using version 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);		//^
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		//using core profile (only has modern functions)

	GLFWwindow* window = glfwCreateWindow(800, 800, "Game Engine", NULL, NULL);		//creates window object

	if (window == NULL)		//if window fails to create
	{
		std::cout << "Window creation failed" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);		//introduce window to context

	gladLoadGL();	//load glad configurations on OpenGL

	glViewport(0, 0, 800, 800);

	Shader shaderProgram("default.vert", "default.frag");	//generates shader object



	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));	// generates buffer object and links it
	EBO EBO1(indices, sizeof(indices));		// ^

	VAO1.LinkVBO(VBO1, 0);
	
	VAO1.Unbind();	//unbinds to prevent accidental modification
	VBO1.Unbind();	//^
	EBO1.Unbind();	//^


	//-----------------------------------------------------------------------------
	// GAME LOOP
	//-----------------------------------------------------------------------------
	bool can = true;					/////////////////////////////////////////////////

	while (!glfwWindowShouldClose(window))
	{
		int state = glfwGetKey(window, GLFW_KEY_E);
		if (state == GLFW_PRESS)		/////////////////////////////////////////////////
		{								/////////////////////////////////////////////////
			if (can)					/////////////////////////////////////////////////
			{							/////////////////////////////////////////////////
				vertices[7] -= 0.1f;	/////////////////////////////////////////////////
				VBO1.Bind();			/////////////////////////////////////////////////
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);		/////////////////////////////////////////////////
				VBO1.Unbind();			/////////////////////////////////////////////////
			}							/////////////////////////////////////////////////
			can = false;				/////////////////////////////////////////////////
		}								/////////////////////////////////////////////////
		if (state == GLFW_RELEASE)		/////////////////////////////////////////////////
		{								/////////////////////////////////////////////////
			can = true;					/////////////////////////////////////////////////
		}								/////////////////////////////////////////////////


		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);	//clears back buffer and sets it with new configurations
		shaderProgram.Activate();	//tells opengl which shader program to use
		VAO1.Bind();	//so opengl knows how to use it
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		glfwPollEvents();	//handles glfw poll events
	}

	//-----------------------------------------------------------------------------
	// END PROGRAM
	//-----------------------------------------------------------------------------
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}