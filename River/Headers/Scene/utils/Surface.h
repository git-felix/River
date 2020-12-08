#pragma once
#include <vector>
#include <iostream>

#include "Vertex.h"
#include "Texture.h"

class Surface
{
public:
	Surface(int horiz_vert, int vertical_vert, float s) :
		scale(1.0f),
		size(s),
		horizontal_vertices(horiz_vert),
		vertical_vertices(vertical_vert)
	{ 
		generate_indexed_triangle_strip_plane();
		generate_index_buffer();
	}


	void update_height(std::vector<unsigned short int> pixels)
	{
		unsigned int pixels_size = pixels.size();
		unsigned int step = pixels_size / coordinates.size();
		unsigned int pixel_position = 0;
		for (unsigned int i = 0; i < coordinates.size(); i++)
		{
			coordinates[i].get_coord().set_Y(pixels[pixel_position] * scale);
			pixel_position += step;
		}
	}

	void generate_indexed_triangle_strip_plane()
	{
		// steps calculation
		float step_right = size / (horizontal_vertices - 1.0f);
		float step_up = size / (vertical_vertices - 1.0f);
		float texture_step_S = 1.0f / (horizontal_vertices - 1.0f);
		float texture_step_T = 1.0f / (vertical_vertices - 1.0f);

		float S_pos = 0.0f;
		float T_pos = 0.0f;

		// plane coordinates generation
		float y = 0;
		for (float i = 0; i <= size; i += step_right)
		{
			for (float j = 0; j <= size; j += step_up)
			{
				float x = j;
				float z = i;
				Point point(x, z, y);
				// TODO: generate text_uv's later
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
	float scale;
	float size;
	unsigned int horizontal_vertices;
	unsigned int vertical_vertices;
	std::vector<Vertex> coordinates;	//array holding the vertex information.
	std::vector<int> index_buffer;	// array holding the indices of the triangle strips
};