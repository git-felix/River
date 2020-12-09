#pragma once

// utils
#include "utils/view/Camera.h"
#include "Window.h"

// openGL
#include "GLFW/glfw3.h"

#include <glm/vec3.hpp> 
#include <glm/vec4.hpp> 
#include <glm/mat4x4.hpp> 
#include <glm/gtc/matrix_transform.hpp>

#define PI 3.14159265

class RayCaster
{
	RayCaster(const Camera& cam, const Window window) :
		width(window.get_width()),
		height(window.get_height()),
		aspectRatio(width / height)
	{
		origin = cam.Position;
		direction = glm::vec3(1.0f, 1.0f, 1.0f);
	}

	void constructRay_throughPixel(unsigned int cursorX, unsigned int cursorY )
	{
		float FOV = 90.0f;
		const float camera_x = (float)((2 * ((cursorX + 0.5) / width) - 1) * tanf((FOV) / 2 * PI / 180) * aspectRatio);
		const float camera_y = (float)((1 - 2 * ((cursorY + 0.5) / height)) * tanf((FOV) / 2 * PI / 180));
		const float length = (float)(sqrt((camera_x * camera_x) + (camera_y * camera_y) + 1));
		direction[0] = camera_x / length;
		direction[1] = camera_y / length;
		direction[2] = (-1) / length;
		// TODO: multiply by the camera matrix
	}


private:
	glm::vec3 origin;
	glm::vec3 direction;

	float width;
	float height;
	float aspectRatio;
};