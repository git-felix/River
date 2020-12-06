#pragma once

#include <vector>

#include "Point.h"
#include "Texture_Coordinates.h"


class Vertex
{
public:
	// default constructor
	Vertex() :
		coordinate(),
		texture_uv()
	{

	}

	Vertex(Point p, Texture_Coordinates tex_uv ) :
		coordinate(p),
		texture_uv(tex_uv)
	{

	}

	// setters
	void set_coordinate(Point coord)
	{
		coordinate = coord;
	}
	void set_Texture_Coordinates(Texture_Coordinates tex)
	{
		texture_uv = tex;
	}

	// getters
	Point get_coord() const
	{
		return coordinate;
	}
	Texture_Coordinates get_texture() const
	{
		return texture_uv;
	}
	const std::vector<float> get_data()
	{
		// coordiantes
		std::vector<float> data = coordinate.get_data();
		// texture coordinates
		std::vector<float> tex = texture_uv.get_data();
		
		data.insert(data.end(), tex.begin(), tex.end());
		return data;
	}


	friend std::ostream& operator<<(std::ostream& os, Vertex vertex)
	{
		os << "[" << vertex.get_coord() << vertex.get_texture() << "]";
		return os;
	}

private:
	Point coordinate;
	Texture_Coordinates texture_uv;
};
