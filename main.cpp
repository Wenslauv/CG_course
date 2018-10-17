#include "tgaimage.h"

#include "functions.h"
#include "geometry.h"
#include "model.h"

#include <memory>


const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green = TGAColor(0,   255, 0,   255);
const int width = 800;
const int height = 800;

std::shared_ptr<Model> model;




int main(int argc, char** argv) {
	if (argc==2) 
	{
		model = std::make_shared<Model>(argv[1]);
	}
	else {
		model = std::make_shared<Model>("wire/default_model.sample");
	}


	TGAImage image(width, height, TGAImage::RGB);


	const int count = model->faces_count();
	const Vector3f light(0,0,-1);

	for(int i = 0; i < count; ++i) {
		const auto face = model->get_face(i);
		std::vector<Vector2i> screen_coords(3);
		std::vector<Vector3f> world_coords(3);

		for(int j =0; j < 3; ++j) {
			const auto wc = model->get_vertice(face[j]);
			screen_coords[j] = Vector2i( (wc.x + 1.0) * width / 2.0, 
										 (wc.y + 1.0) * height / 2.0);
			world_coords[j] = wc;
		}

		auto normal = (world_coords[2] - world_coords[1]) ^ (world_coords[1] - world_coords[0]);
		normal.normalize();

		const float intensity = normal * light;
		if (intensity > 0) {
			draw_triangle(	screen_coords[0], 
							screen_coords[1], 
							screen_coords[2], 
							image, 
							TGAColor(255*intensity, 255*intensity, 255*intensity, 255)
			);
		}
	}

	image.flip_vertically();
	image.write_tga_file("output.tga");
	return 0;
}

