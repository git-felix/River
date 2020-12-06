#include <iostream>

#include "utils/view/Image.h"
#include "Scene_Objects/utils/Vertex.h"
#include "Scene_objects/utils/Surface.h"

int main()
{
	std::string path_terrain_height_map = "./Resources/Images/TerrainHeightMap.png";
	std::string path_terrain = "./Resources/Images/TerrainDiffuse.png";
	std::string path_pic01 = "./Resources/Images/Pic01.jpg";


	Image image("./Resources/Images/Pic01.jpg");
	image.save("./local_repo/output/img01.jpg");


	Surface plane(3, 3, 5, path_pic01);
	//std::cout << vertex_test << std::endl;
	return 0;
};