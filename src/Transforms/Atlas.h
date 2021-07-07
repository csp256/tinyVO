#pragma once
#include "../Actor.h"
#include "View.h"
#include "Projection.h"
#include "../Texture.h"

struct Atlas {
	    Matrix4 const world_from_model;
	    Matrix4 const camera_from_world;
	    Matrix4 const camera_from_model;

	    Matrix4 const clip_from_camera;

	    Matrix4 const viewport_from_NDC;

	Atlas(
		Actor const& actor,
		View const& view,
		Projection const& projection,
		Texture const& image);
};

inline Atlas::Atlas(
		Actor const& actor,
		View const& view,
		Projection const& projection,
		Texture const& image)
	: world_from_model{ actor._pose.matrix() }
	, camera_from_world{ view.matrix() }
	, camera_from_model{ mul(camera_from_world, world_from_model) }
	, clip_from_camera{ linalg::identity }
	, viewport_from_NDC{ linalg::identity /*viewport.matrix(image)*/ }
{}
