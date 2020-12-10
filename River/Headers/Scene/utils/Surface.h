#pragma once
#include <vector>
#include <iostream>

#include "Vertex.h"
#include "Texture.h"
#include "utils/view/Image.h"

class Surface
{
public:
	Surface(int vertical_vert, int horiz_vert, float s) :
		size(s),
		horizontal_vertices(horiz_vert),
		vertical_vertices(vertical_vert)
	{ 
		generate_indexed_triangle_strip_plane();
		generate_index_buffer();
	}

	Surface(int vertical_vert, int horiz_vert, float s, Image image) :
		size(s),
		horizontal_vertices(horiz_vert),
		vertical_vertices(vertical_vert)
	{
		generate_indexed_triangle_strip_plane();
		update_height(image.get_pixels());
		generate_index_buffer();
	}


	void update_height(std::vector<float> pixels)
	{
		unsigned int pixels_size = pixels.size();
		unsigned int step = pixels_size / coordinates.size();
		unsigned int pixel_position = 0;
		for (unsigned int i = 0; i < coordinates.size(); i++)
		{
			Vertex temp_vertex = coordinates[i];
			Point temp_point = temp_vertex.get_coord();
			temp_point.set_Y((((pixels[pixel_position] / 255)) * scale) - (scale / 1.75) );
			temp_vertex.set_coordinate(temp_point);
			coordinates[i] = temp_vertex;
			pixel_position += step;
		}
	}

	void generate_indexed_triangle_strip_plane()
	{
		// steps calculation
		float texture_step_S = 1.0f / (horizontal_vertices - 1.0f);
		float texture_step_T = 1.0f / (vertical_vertices - 1.0f);

		float S_pos = 0.0f;
		float T_pos = 0.0f;

		// plane coordinates generation
		float y = 0;
		for (float i = 0; i < vertical_vertices; i++)
		{
			float zRatio = i / (horizontal_vertices - 1);
			for(float j = 0; j < horizontal_vertices; j++)
			{
				float xRatio = j / (vertical_vertices - 1);
				float x = size * xRatio;
				float z = size * zRatio;

				Point point(x, y, z);

				Texture_Coordinates text_uv(S_pos, T_pos);
				S_pos += texture_step_S;

				Vertex vertex(point, text_uv);
				coordinates.push_back(vertex);
			}
			T_pos += texture_step_T;
			S_pos = 0.0f;
		}
	}

	std::vector<float> get_data() const
	{
		std::vector<float> result;
		for (unsigned int i = 0; i < coordinates.size(); i++)
		{
			std::vector<float> temp = coordinates[i].get_data();
			result.insert(result.end(), temp.begin(), temp.end());
		}
		return result;
	}


	std::vector<int> get_index_buffer() const 
	{
		return index_buffer;
	}

private:
	void generate_index_buffer()
	{
		for (unsigned int i = 0; i < vertical_vertices - 1; i++)
		{
			int index_low = i * horizontal_vertices;
			int index_high = (i + 1) * horizontal_vertices;

			for (unsigned int j = 0; j < horizontal_vertices; j++)
			{
				index_buffer.push_back(index_low + j);
				index_buffer.push_back(index_high + j);
			}
			if (i + 1 >= vertical_vertices - 1)
				continue;
			// degenerate
			index_buffer.push_back(index_high + horizontal_vertices - 1);
			index_buffer.push_back(index_low + horizontal_vertices);
		}
 }

	void print_vertices()
	{
		for (unsigned int i = 0; i < vertical_vertices; ++i)
		{
			for (unsigned int j = 0; j < horizontal_vertices; ++j)
			{
				std::cout << "<" << i * horizontal_vertices << "," << j << ">\t" << "["
					<< coordinates[i*horizontal_vertices + j].get_coord().get_X() << " "
					<< coordinates[i*horizontal_vertices + j].get_coord().get_Y() << " "
					<< coordinates[i*horizontal_vertices + j].get_coord().get_Z() << "]"
					<< std::endl;
			}
		}
	}

	void set_scale(float s)
	{
		scale = s;
	}

private:
	float scale = 7.25f;
	float size;
	unsigned int horizontal_vertices;
	unsigned int vertical_vertices;
	std::vector<Vertex> coordinates;	//array holding the vertex information.
	std::vector<int> index_buffer;	// array holding the indices of the triangle strips
};