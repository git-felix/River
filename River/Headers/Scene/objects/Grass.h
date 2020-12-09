#pragma once
#include <map>

#include "view/Shader.h"

// utils
#include "utils/view/Image.h"
#include "utils/Mesh.h"
#include "Scene/utils/Surface.h"
#include "utils/view/Camera.h"


class Grass
{
public:
	Grass(int vertical_count, int horizontal_count, float size) :
		image("./Resources/Images/GrassDiffuse.png"),
		texture("./Resources/Images/GrassDiffuse.png"),
		surface(vertical_count, horizontal_count, size, image),
		shader("./Resources/Shaders/Terrain/Terrain_Vertex.shader", "./Resources/Shaders/Grass/Grass_Geometry.shader",
			"./Resources/Shaders/Grass/Grass_Fragment.shader"),
		mesh()
	{
		set_vegetation();
	}

	void set_vegetation()
	{
		// test sample
		vegetation.push_back(glm::vec4(-0.3f, 0.0f, -2.3f, 0.0f));
		vegetation.push_back(glm::vec4(1.5f, 0.0f, 0.51f, 0.0f));
		vegetation.push_back(glm::vec4(-1.5f, 0.0f, -0.48f, 0.0f));
		vegetation.push_back(glm::vec4(0.5f, 0.0f, -0.6f, 0.0f));
		vegetation.push_back(glm::vec4(0.0f, 0.0f, 0.7f, 0.0f));
		
		for (int i = 0; i < vegetation.size(); i++)
		{
			shader.SetVec4("position", vegetation[i]);
		}
	}

	std::vector<glm::vec4> get_vegetation()
	{
		return vegetation;
	}


	void sort_vegetation(Camera camera)
	{
		for (unsigned int i = 0; i < vegetation.size(); i++)
		{
			float distance = glm::length(glm::vec4(camera.Position, 0.0f) - vegetation[i]);
			sorted[distance] = vegetation[i];
		}
	}


	void draw()
	{
		texture.Bind(3);
		mesh.Draw();
	}

	void update_shaders(const std::string& name, const glm::mat4& mat)
	{
		shader.bind();
		glm::mat4 model = mat;

		for(std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
		{
			model = glm::translate(model, it->second);
			shader.SetMat4(name, model);
		}
		//shader.unbind();
	}

	void update_shaders(const std::string& name, float value)
	{
		//shader.bind();
		shader.SetFloat(name, value);
		//shader.unbind();
	}


private:

	//void setup_mesh()
	//{
	//	mesh.BindIndexBuffer(&surface.get_index_buffer().front(), surface.get_index_buffer().size());
	//	mesh.AddLayout(4);
	//	mesh.AddLayout(2);
	//}

private:
	vector<glm::vec4> vegetation;
	std::map<float, glm::vec3> sorted;
	Image image;
	Texture texture;
	Surface surface;
	Shader shader;
	Mesh mesh;
};