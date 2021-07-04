#include "Image.h"

#include <lib/stb_image_write.h>
#include <lib/stb_image.h>

#include <iostream>
#include <fstream>

#include <cstring>

std::vector<RGBA> Image::get_flipped() const
{
	std::vector<RGBA> out;
	out.resize(_data.size());
	for (int i = 0, j = _height - 1; i < _height; i++, j--) {
		std::memcpy(out.data() + j*_width, // to
					_data.data() + i*_width, // from
					row_stride());
	}
	return out;
}

void Image::write_ppm(std::string const& filename) const
{
	auto data = get_flipped();

	std::ofstream output(filename, std::ios::binary);

	output << "P3\n";
	output << std::to_string(_width) << " " << std::to_string(_height) << "\n";
	output << "255\n";

	int k = 0;
	for (int y = 0; y < _height; y++) {
		for (int x = 0; x < _width; x++) {
			RGBA const& px = data[k++];
			output << px.r << " ";
			output << px.g << " ";
			output << px.b << " ";
			output << px.a << " ";
		}
		output << "\n";
	}
}

void Image::write_png(std::string const& filename) const
{
	auto data = get_flipped();
	constexpr int channels = 4;
	const int row_stride = _width * channels;
	stbi_write_png(filename.c_str(), _width, _height, channels, (const void *) data.data(), row_stride);
}

ImageInitializer read_png(std::string const& filename) 
{
	ImageInitializer out;
	int channels_in_file; // unused

	uint8_t* u8_ptr = stbi_load(filename.c_str(), &out.width, &out.height, &channels_in_file, STBI_rgb_alpha);
	if (u8_ptr == nullptr) {
		throw std::runtime_error("Failed to load: " + filename);
	} 

	auto rgba_ptr = reinterpret_cast<RGBA*>(u8_ptr);
	// sadly, we have to do this copy or not use a std::vector for Image's data
	out.data.assign(rgba_ptr, rgba_ptr + out.width * out.height);

	stbi_image_free(u8_ptr);
	return out;
}