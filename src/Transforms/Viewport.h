#pragma once
#include "lib/linalg.h"
#include "../Texture.h"

struct Viewport {
	
	inline Matrix4 matrix(Texture const& image) const
	{
		Matrix4 out = linalg::identity;
		// translating
		out[3][0] = image.width() / 2.0;
		out[3][1] = image.height() / 2.0;
		// scaling
		out[0][0] = image.width() / 2.0;
		out[1][1] = image.height() / 2.0;
		return out;
	}
};