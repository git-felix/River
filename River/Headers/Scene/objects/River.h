#pragma once
#include "Scene/utils/Surface.h"
#include "utils/view/Image.h"

class River
{
public:
	River() :
		image(image_path.c_str()),
		texture(image_path),
		surface(3, 3, 10)
	{
		
	}

	void generate_river()
	{

	}

private:
	Image image;
	std::string image_path = "./Resources/Images/WaterDiffuse.png";
	Texture texture;
	Surface surface;
};