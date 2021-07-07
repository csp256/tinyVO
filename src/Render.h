#include "Scene.h"
#include "Transforms/View.h"
#include "Transforms/Projection.h"
#include "Transforms/Viewport.h"
#include "Texture.h"

class Render {
public:
	Scene const * _scene;

	View const _view;
	Projection const _projection;
	// Viewport _viewport;

	Texture _image;

	Render() = delete;
	Render(JSON const& j);

	void draw();
};

void perform_all_renders(JSON const& j);