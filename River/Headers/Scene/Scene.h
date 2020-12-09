#pragma once

// objects
#include "objects/River.h"
#include "objects/Terrain.h"
#include "objects/Grass.h"

// utils
#include "utils/view/Camera.h"
#include "utils/Window.h"
#include "utils/Mesh.h"

// opengl
#include "GLFW/glfw3.h"


class Scene
{
public:
	Scene() :
		window_helper(1980, 1020),
		river(40, 40, 25),
		terrain(20, 20, 25)
		//grass(20, 20, 25)
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



	void render()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);


		float lastFrame = 0.0f;
		while(!glfwWindowShouldClose(window))
		{	
			float currentFrame = glfwGetTime();
			float deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			update_camera(deltaTime);
			glm::mat4 mvp = update_mvp();

			update_objects(mvp, currentFrame);

			// Swap front and back buffers
			glfwSwapBuffers(window);
			// Poll for and process events
			glfwPollEvents();
		}
	}



private:

	void update_objects(glm::mat4 mvp, float time)
	{
		update_terrain(mvp);
		update_river(mvp, time);
		//update_grass();
	}

	void update_terrain(glm::mat4 mvp)
	{
		terrain.update_shaders("mvp", mvp);
		terrain.draw();
	}

	void update_river(glm::mat4 mvp, float time)
	{
		river.update_shaders("mvp", mvp);
		river.update_shaders("deltaTime", time / flow_speed);
		river.draw();
	}

	void update_grass()
	{
		//glm::mat4 model = glm::mat4(1.0f);
		//grass.update_shaders("model", model);
		//grass.draw();
	}

	void update_camera(float deltaTime)
	{
		keyboard_events(deltaTime);
		mouse_events();
	}
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

		// "space" for going up
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			camera.Position[1] += 0.01f;
		}

		// "left ctrl" for going down
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			camera.Position[1] -= 0.01f;
		}


		// switch polygon mode to LINE
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		// switch polygon mode to FILL
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		// switch cursor mode
		if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		{
			change_cursor_mode();
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

		// send them to camera to update the view of the camera
		camera.ProcessMouseMovement(offset_X, offset_Y);
	}

	void change_cursor_mode()
	{
		cursor_enabled = !cursor_enabled;
		if (cursor_enabled)
		{
			//glfwSetCursorPos(window, window_helper.get_width() / 2, window_helper.get_height() / 2);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}



private:
	// OPENGL
	GLFWwindow* window;
	Window window_helper;
	// objects 
	River river;
	Terrain terrain;
	//Grass grass;
	//Grass grass;

	// utils
	Camera camera;
	int mouse_lastX;
	int mouse_lastY;
	bool cursor_enabled = false;

	float flow_speed = 15.0f;

};

