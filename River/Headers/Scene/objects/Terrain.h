#pragma once
#include "Scene/utils/Surface.h"
#include "utils/view/Image.h"
#include "view/Shader.h"
#include "utils/Mesh.h"

class Terrain
{
public:
	Terrain(int vertical_count, int horizontal_count, float size) :
		image("./Resources/Images/TerrainHeightMap.png"),
		texture("./Resources/Images/TerrainDiffuse.png"),
		surface(vertical_count, horizontal_count, size, image),
		shader("./Resources/Shaders/Terrain/Terrain_Vertex.shader", "",
			"./Resources/Shaders/Terrain/Terrain_Fragment.shader"),
		mesh(&surface.get_data().front(), surface.get_data().size())
	{
		setup_mesh();
	}

	void draw()
	{
		texture.Bind(1);
		mesh.DrawElements();
	}

	void update_shaders(const std::string& name, const glm::mat4& mat)
	{
		shader.bind();
		shader.SetMat4(name, mat);
		//shader.unbind();
	}

	void update_shaders(const std::string& name, float value)
	{
		//shader.bind();
		shader.SetFloat(name, value);
		//shader.unbind();
	}

	Surface get_surface() const
	{
		return surface;
	}

private:

	void setup_mesh()
	{
		mesh.BindIndexBuffer(&surface.get_index_buffer().front(), surface.get_index_buffer().size());
		mesh.AddLayout(3);
		mesh.AddLayout(2);
	}

private:
	Image image;
	Texture texture;
	Surface surface;
	Shader shader;
	Mesh mesh;
};