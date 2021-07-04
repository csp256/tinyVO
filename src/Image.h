#pragma once

#include "types.h"
#include <lib/linalg.h>

#include <vector>
#include <string>

// Proxy object for delegated construction.
// Necessary to let you load a PNG like:
//     auto img = Grid("file.png");
// with constant member variables 
struct ImageInitializer {
	std::vector<RGBA> data;
	int width, height;
};
ImageInitializer read_png(std::string const& filename);

/**
 * Primary class for storing RGBA images.
 */
class Image {
	std::vector<RGBA> _data;
	int const _width;
	int const _height;
	RGBA _garbage;

	std::vector<Float> _depth;
	Float _depth_garbage;

	/**
	 * This constructor can not be directly called by the user.
	 * It will be called by the Image(std::string) constructor.
	 * 
	 * This is necessary for initializing constant member 
	 * variables when loading from a file.
	 */
	Image(ImageInitializer file_data)
		: _width{file_data.width}
		, _height{file_data.height}
	{
		_data = std::move(file_data.data);
		_depth.resize(_data.size(), std::numeric_limits<Float>::max());
	}

public:
	/**
	 * Constructs an Image from a file.
	 */
	Image(std::string const& filename) : Image(read_png(filename)) {}

	/**
	 * Constructs image with a single color.
	 */
	Image(int width, int height, RGBA px = {0,0,0,255})
		: _width{width}
		, _height{height}
	{
		_data.resize(_width * _height, px);
		_depth.resize(_data.size(), std::numeric_limits<Float>::max());
	}

	inline int width() const { return _width; }
	inline int height() const { return _height; }
	inline Lattice2 extent() const { return Lattice2{_width, _height}; }

	/**
	 * Returns a pointer to the first element.
	 */
	inline RGBA * data() { return _data.data(); }
	inline RGBA const * data() const { return _data.data(); }

	/**
	 * Returns a pointer to the first element of row y.
	 */
	inline RGBA * row(int y) { return &_data[y * _width]; }
	inline RGBA const * row(int y) const { return &_data[y * _width]; }

	/**
	 * Tests if this point is contained within the Image.
	 */
	inline bool contains(Lattice2 const& p) const
	{
		return 0 <= p.x and p.x < _width 
			and 0 <= p.y and p.y < _height;
	}

	/**
	 * Computes the index of this lattice point.
	 */
	inline int index(Lattice2 const& p) const { return p.x + p.y * _width; }

	/**
	 * img({x, y}) will return a reference to the RGBA pixel
	 * at that position if it is contained within the image.
	 * 
	 * If you try to access a pixel outside the image, it will
	 * silently return a reference to a "garbage" pixel.
	 * 
	 * This method of accessing the image is not very fast, but
	 * it is convenient and simplifies some algorithms.
	 */
	inline RGBA & operator()(Lattice2 const& p) 
	{
		return contains(p)
			? _data[index(p)]
			: _garbage;
	}
	inline RGBA const& operator()(Lattice2 const& p) const
	{
		return contains(p)
			? _data[index(p)]
			: _garbage;
	}

	/**
	 * Main accessor for depth data
	 */
	inline Float & depth(Lattice2 const& p)
	{
		return contains(p)
			? _depth[index(p)]
			: _depth_garbage;
	}
	inline Float const& depth(Lattice2 const& p) const
	{
		return contains(p)
			? _depth[index(p)]
			: _depth_garbage;
	}

	/**
	 * Set every pixel to a single color.
	 */
	inline void fill(RGBA const& input) 
	{
		for (auto& px : _data) {
			px = input;
		}
	}

	/**
	 * Set the opacity of every pixel to a single value.
	 */
	inline void fill_opacity(uint8_t const& alpha)
	{
		for (auto& px : _data) {
			px.a = alpha;
		}
	}

	/**
	 * Bytes per row
	 */
	inline size_t row_stride() const
	{
		constexpr size_t channels = 4;
		return _width * channels;
	}

	std::vector<RGBA> get_flipped() const;

	void write_ppm(std::string const& filename) const;

	void write_png(std::string const& filename) const;
};