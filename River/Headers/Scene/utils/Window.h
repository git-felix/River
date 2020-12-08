#pragma once

#include "GLFW/glfw3.h"
#include "GL/glew.h"

#include <fstream>

class Window
{
public:
	Window(int wid, int hei) :
		width(wid),
		height(hei)
	{
		initialize_window(wid, hei);
	}

	GLFWwindow* get_window() const 
	{
		return window;
	}

	float get_width() const
	{
		return width;
	}

	float get_height() const
	{
		return height;
	}

private:
	void initialize_window(int width, int height)
	{
		/* Initialize the library */
		if (!glfwInit()) { return; }
		/* Create a windowed mode window and its OpenGL context */
		//window = glfwCreateWindow(width, height, "River", glfwGetPrimaryMonitor(), NULL);
		window = glfwCreateWindow(width, height, "River", NULL, NULL);

		if (!window)
		{
			glfwTerminate();
			return;
		}

		glfwSwapInterval(1);
		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		// call glewInit after creating the context...
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			/* Problem: glewInit failed, something is seriously wrong. */
			fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		}
	}

private:
	float width;
	float height;
	GLFWwindow* window;
};