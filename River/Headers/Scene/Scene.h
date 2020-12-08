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
	}

	glm::mat4 update_mvp()
	{
		glm::mat4 view = glm::lookAt(camera.Position, camera.Position + camera.Front, camera.Up);
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)(1), 0.1f, 100.0f);		//perspective view
		glm::mat4 model = glm::mat4(1.0f);
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
		while(!glfwWindowShouldClose(window))
		{
			float lastFrame = 0;
			float currentFrame = glfwGetTime();
			float deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

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

		std::cout << "X: " << xpos << "\tY:" << ypos << std::endl;

		// send them to camera to update the view of the camera
		camera.ProcessMouseMovement(xpos, ypos);
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
	//Mesh mesh;
};

