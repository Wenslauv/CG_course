#include "tgaimage.h"

#include "functions.h"
#include "geometry.h"
#include "model.h"

#include <memory>


const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
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

		for(int j =0; j< 3; ++j) {
			const auto v0 = model->get_vertice(face[j]);
			const auto v1 = model->get_vertice(face[(j+1) % 3]);

			const int x0 = (v0.x + 1.0) * width / 2.0;
			const int y0 = (v0.y + 1.0) * height / 2.0;

			const int x1 = (v1.x + 1.0) * width / 2.0;
			const int y1 = (v1.y + 1.0) * height / 2.0;

			line(x0, y0, x1, y1, image, white);
		}
	}

	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}

