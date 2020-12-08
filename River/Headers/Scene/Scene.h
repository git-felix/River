#pragma once

#include "objects/River.h"
#include "utils/view/Camera.h"
#include "utils/Window.h"
#include "utils/Mesh.h"
#include "GLFW/glfw3.h"


class Scene
{
public:
	Scene() :
		window_helper(1800, 980),
		river()
	{
		window = window_helper.get_window();
		mouse_lastX = 0;
		mouse_lastY = 0;
	}

	glm::mat4 update_mvp()
	{
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 1.0f, 0.1f, 100.0f);		//perspective view
		glm::mat4 model = glm::mat4(1.0f);
		//river.update_shaders("model", model);
		glm::mat4 mvp = projection * view * model;
		return mvp;
	}

	void update_camera(float deltaTime)
	{
		keyboard_events(deltaTime);
		mouse_events();
	}



	void render()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		float lastFrame = 0.0f;
		while(!glfwWindowShouldClose(window))
		{	
			float currentFrame = glfwGetTime();
			float deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			update_camera(deltaTime);
			glm::mat4 mvp = update_mvp();
			river.update_shaders("mvp", mvp);

			river.draw();

			// Swap front and back buffers
			glfwSwapBuffers(window);
			// Poll for and process events
			glfwPollEvents();
		}
	}



private:
	// process the input from keyboard and send them to camera
	void keyboard_events(float deltaTime)
	{
		// closes the window
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		// keyboard inputs
		// "W" for going forward
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			camera.ProcessKeyboard(FORWARD, deltaTime);
		}

		// "A" for going left
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			camera.ProcessKeyboard(LEFT, deltaTime);
		}

		// "S" for going back
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			camera.ProcessKeyboard(BACKWARD, deltaTime);
		}

		// "D" for going right
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			camera.ProcessKeyboard(RIGHT, deltaTime);
		}
	}
	// process the input from the mouse and send them to camera
	void mouse_events()
	{
		double xpos;
		double ypos;

		// gets mouse x and y positions
		glfwGetCursorPos(window, &xpos, &ypos);

		float offset_X = mouse_lastX - xpos;
		float offset_Y = mouse_lastY - ypos;

		mouse_lastX = xpos;
		mouse_lastY = ypos;

		std::cout << "X: " << xpos << "\tY:" << ypos << std::endl;

		// send them to camera to update the view of the camera
		camera.ProcessMouseMovement(offset_X, offset_Y);
	}





private:
	// OPENGL
	GLFWwindow* window;
	Window window_helper;
	// objects 
	River river;
	//Terrain terrain;
	//Grass grass;

	// utils
	Camera camera;
	int mouse_lastX;
	int mouse_lastY;
	//Mesh mesh;
};

