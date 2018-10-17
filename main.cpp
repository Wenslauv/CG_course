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
	// if (argc==2) 
	// {
	// 	model = std::make_shared<Model>(argv[1]);
	// }
	// else {
	// 	model = std::make_shared<Model>("wire/default_model.sample");
	// }


	TGAImage image(width, height, TGAImage::RGB);

	Vector2i t0[3] = {Vector2i(10, 70),   Vector2i(50, 160),  Vector2i(70, 80)};
    Vector2i t1[3] = {Vector2i(180, 50),  Vector2i(150, 1),   Vector2i(70, 180)};
    Vector2i t2[3] = {Vector2i(180, 150), Vector2i(120, 160), Vector2i(130, 180)};


    draw_triangle(t0[0], t0[1], t0[2], image, red);
    draw_triangle(t1[0], t1[1], t1[2], image, white);
    draw_triangle(t2[0], t2[1], t2[2], image, green);


	// const int count = model->faces_count();
	// for(int i = 0; i < count; ++i) {
	// 	const auto face = model->get_face(i);

	// 	for(int j =0; j< 3; ++j) {
	// 		const auto v0 = model->get_vertice(face[j]);
	// 		const auto v1 = model->get_vertice(face[(j+1) % 3]);

	// 		const int x0 = (v0.x + 1.0) * width / 2.0;
	// 		const int y0 = (v0.y + 1.0) * height / 2.0;

	// 		const int x1 = (v1.x + 1.0) * width / 2.0;
	// 		const int y1 = (v1.y + 1.0) * height / 2.0;

	// 		line(x0, y0, x1, y1, image, white);
	// 	}
	// }

	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}

