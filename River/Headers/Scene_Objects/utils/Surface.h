#pragma once
#include <vector>

#include "Vertex.h"
#include "Texture.h"

class Surface
{
public:
	Surface(int horiz_vert, int vertical_vert, float s, const std::string& path) :
		size(s),
		horizontal_vertices(horiz_vert),
		vertical_vertices(vertical_vert),
		texture(path)
	{ 
		generate_indexed_triangle_strip_plane();
	}


	void generate_indexed_triangle_strip_plane()
	{
		// steps calculation
		float step_right = size / (horizontal_vertices - 1);
		float step_up = size / (vertical_vertices - 1);

		// plane coordinates generation
		float y = 0;
		for (float i = 0; i <= size; i += step_right)
		{
			for (float j = 0; j <= size; j += step_up)
			{
				Point point(j, y, i);
				// TODO: generate text_uv's later
				Texture_Coordinates text_uv;
				Vertex vertex(point, text_uv);
				coordinates.push_back(vertex);
			}
		}

		// plane indices generation
		int index = 0;
		for (unsigned int i = 0; i < vertical_vertices - 1; ++i)
		{
			for (unsigned int j = 0; j < horizontal_vertices; ++j, ++index)
			{
				index_buffer.push_back(index);
				index_buffer.push_back(index + horizontal_vertices);
			}
			index_buffer.push_back(index_buffer.back());
			index_buffer.push_back(index_buffer.at(index_buffer.size() - (2 * horizontal_vertices)));
		}
	}

	void print_vertices()
	{
		for (int i = 0; i < horizontal_vertices; ++i)
		{
			for (int j = 0; j < horizontal_vertices; ++j)
			{
				std::cout << "<" << i * horizontal_vertices << "," << j << ">\t" << "["
					<< coordinates[i*horizontal_vertices + j].get_coord().get_X() << " "
					<< coordinates[i*horizontal_vertices + j].get_coord().get_Y() << " "
					<< coordinates[i*horizontal_vertices + j].get_coord().get_Z() << "]"
					<< std::endl;
			}
		}
	}

private:
	float size;
	unsigned int horizontal_vertices;
	unsigned int vertical_vertices;
	std::vector<Vertex> coordinates;	//array holding the vertex information.
	std::vector<int> index_buffer;	// array holding the indices of the triangle strips


	Texture texture;
};