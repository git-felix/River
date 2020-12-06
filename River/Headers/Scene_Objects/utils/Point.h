#pragma once
#include <vector>

class Point
{
public:
	// default constructor
	Point() : X(0), Y(0), Z(0)
	{

	}

	Point(float x, float y, float z) : 
		X(x), Y(y), Z(z)
	{

	}
	// copy constructor
	Point(const Point &point)
	{
		X = point.get_X();
		Y = point.get_Y();
		Z = point.get_Z();
	}

	// setter
	void set_X(float x)
	{
		X = x;
	}
	void set_Y(float y)
	{
		Y = y;
	}
	void set_Z(float z)
	{
		Z = z;
	}

	// getter
	float get_X() const
	{
		return X;
	}
	float get_Y() const
	{
		return Y;
	}
	float get_Z() const
	{
		return Z;
	}
	std::vector<float> get_data() const
	{
		std::vector<float> data;
		data.push_back(X);
		data.push_back(Y);
		data.push_back(Z);
		return data;
	}

	void operator=(const Point& p)
	{
		this->X = p.get_X();
		this->Y = p.get_Y();
		this->Z = p.get_Z();
	}

	// cross product
	Point operator*( const Point& point )
	{
		const float x = (Y * point.get_Z()) - (Z * point.get_Y());
		const float y = (Z * point.get_X()) - (X * point.get_Z());
		const float z = (X * point.get_Y()) - (Y * point.get_X());
		return Point(x, y, z);
	}

	Point operator-(const Point& point)
	{
		const float x = X - point.get_X();
		const float y = Y - point.get_Y();
		const float z = Z - point.get_Z();
		return Point(x, y, z);
	}

	friend std::ostream& operator<<(std::ostream& os, Point point)
	{
		os << "[" << "X:" << point.get_X() <<
			" Y:" << point.get_Y() <<
			" Z:" << point.get_Z() << "]";
		return os;
	}

private:
	float X;
	float Y;
	float Z;
};