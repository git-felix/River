#pragma once
#include "Scene/utils/Surface.h"
#include "utils/view/Image.h"
#include "view/Shader.h"
#include "utils/Mesh.h"

class River
{
public:
	River() :
		image("./Resources/Images/WaterDiffuse.png"),
		texture("./Resources/Images/WaterDiffuse.png"),
		surface(10, 10, 5),
		shader("./Resources/Shaders/Water/Water_Vertex.shader", "",
			   "./Resources/Shaders/Water/Water_Fragment.shader"),
		mesh(&surface.get_data().front(), surface.get_data().size())
	{
		setup_mesh();
	}

	void draw()
	{
		mesh.DrawElements();
	}

	void update_shaders(const std::string& name, const glm::mat4& mat)
	{
		shader.bind();
		shader.SetMat4(name, mat);
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
	const std::string image_path;
	Texture texture;
	Surface surface;

	Shader shader;
	const std::string fragment_shader;
	const std::string vertex_shader;

	Mesh mesh;
};