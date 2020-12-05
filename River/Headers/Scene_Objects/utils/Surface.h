#pragma once
#include <vector>

#include "Vertex.h"

class Surface
{
public:
	Surface(int horiz_vert, int vertical_vert, float s, const std::string& path) :
		size(s),
		horizontal_vertices(horiz_vert),
		vertical_vertices(vertical_vert),
		texture(path)
	{ 
		
	}


	Surface generate_indexed_triangle_strip_plane()
	{
		// steps calculation
		float step_right = size / horizontal_vertices;
		float step_up = size / vertical_vertices;
		
		// plane coordinates generation

		float y = 0;

		for (int i = 0; i < horizontal_vertices; i += step_right)
		{
			for (int j = 0; j < vertical_vertices; j += step_up)
			{
				float x = i;
				float z = j;
				Point point(x, y, z);
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