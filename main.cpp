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
	for(int i = 0; i < count; ++i) {
		const auto face = model->get_face(i);
		std::vector<Vector2i> screen_coords(3);

		for(int j =0; j < 3; ++j) {
			const auto world_coords = model->get_vertice(face[j]);
			screen_coords[j] = Vector2i( (world_coords.x + 1.0) * width / 2.0, 
										 (world_coords.y + 1.0) * height / 2.0);
		}

		draw_triangle(	screen_coords[0], 
						screen_coords[1], 
						screen_coords[2], 
						image, 
						TGAColor(rand()%255, rand()%255, rand()%255, 255)
		);
	}

	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}

