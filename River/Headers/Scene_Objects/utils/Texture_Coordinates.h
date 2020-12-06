#pragma once
#include <vector>

class Texture_Coordinates
{
public:
	
	//default constructor
	Texture_Coordinates() :
		S_axis(0.0f),
		T_axis(0.0f)
	{

	}

	Texture_Coordinates(float s, float t) :
		S_axis(s),
		T_axis(t)
	{

	}
	// copy constructor
	Texture_Coordinates(const Texture_Coordinates &tex)
	{
		S_axis = tex.get_S();
		T_axis = tex.get_T();
	}

	// setter
	void set_S(float s)
	{
		S_axis = s;
	}
	void set_T(float t)
	{
		T_axis = t;
	}

	// getter
	float get_S() const
	{
		return S_axis;
	}
	float get_T() const
	{
		return T_axis;
	}
	std::vector<float> get_data() const
	{
		std::vector<float> data;
		data.push_back(S_axis);
		data.push_back(T_axis);
		return data;
	}

	// additional
	void operator=(const Texture_Coordinates& tex)
	{
		this->S_axis = tex.get_S();
		this->T_axis = tex.get_T();
	}

	friend std::ostream& operator<<(std::ostream& os, Texture_Coordinates text_uv)
	{
		os << "[" << "S:" << text_uv.get_S() <<
					 " T:" << text_uv.get_T() << "]";
		return os;
	}

private:
	float S_axis;
	float T_axis;
};