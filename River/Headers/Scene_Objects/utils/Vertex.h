#pragma once

#include <vector>

#include "Point.h"
#include "Texture.h"


class Vertex
{
public:
	// default constructor
	Vertex() :
		coordinate(),
		texture(nullptr)
	{

	}

	Vertex(Point p, const std::string& path) :
		coordinate(p),
		texture(path)
	{

	}

	// setters
	void set_coordinate(Point coord)
	{
		coordinate = coord;
	}
	void set_texture(Texture tex)
	{
		texture = tex;
	}

	// getters
	Point get_coord() const
	{
		return coordinate;
	}
	Texture get_texture() const
	{
		return texture;
	}
	const std::vector<float> get_data()
	{
		// coordiante
		std::vector<float> data = coordinate.get_data();
		
		//std::vector<float> tex = texture.get_data();
		
		// Texture axis
		//data.insert(data.end(), tex.begin(), tex.end());
		return data;
	}

private:
	Point coordinate;
	Texture texture;
};
