#pragma once

#include <iostream>
#include <vector>

// image read
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
// image write
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

struct Image {
public:
	// default constructor
	Image() :
		width(0),
		height(0),
		channel(-1),
		size(0),
		pixels(nullptr)
	{ }
	// contructor with given filepath
	Image(const char* filepath) :
		width(0),
		height(0),
		channel(-1),
		size(width * height * 3),
		pixels(nullptr)
	{
		load(filepath);
	}
	// destructor
	~Image()
	{ }

	// getters
	inline int get_width() const
	{
		return width;
	}
	inline int get_height() const
	{
		return height;
	}
	inline int get_channel() const
	{
		return channel;
	}
	inline int get_size() const
	{
		return size;
	}
	std::vector<float> get_pixels() const
	{
		std::vector<float> pixels_to_process;
		for (int i = 0; i < size; i += 3)
		{
			pixels_to_process.push_back(static_cast<float>(pixels[i]));
		}
		return pixels_to_process;
	}
	/* customization functions */

	// image read and write
	void load(const char* filepath)
	{
		pixels = stbi_load(filepath, &width, &height, &channel, 0);
		size = width * height * 3;
		if (pixels == nullptr)
		{
			printf("Error in loading the image\n");
			exit(1);
		}
		printf("Loaded image %d : width - %dpx, height - %dpx, channels - %d\n", width, height, channel);
	}
	void save(const char* filepath)
	{
		stbi_write_jpg(filepath, width, height, 3, pixels, size);
	}

	void print_pixel(const unsigned int index)
	{
		std::cout << index << "["
			<< static_cast<int>(pixels[index]) << " "
			<< static_cast<int>(pixels[index + 1]) << " "
			<< static_cast<int>(pixels[index + 2]) << "]"
		<< std::endl;
	}

private:
	int width;
	int height;
	int channel;
	int size;
	unsigned char* pixels;
};