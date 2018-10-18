#include "tgaimage.h"

#include "functions.h"
#include "geometry.h"
#include "model.h"

#include <memory>
#include <limits>


const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green = TGAColor(0,   255, 0,   255);
const TGAColor blue  = TGAColor(0,   0,   255, 255); 

const int width = 800;
const int height = 800;
const int depth = 255;

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
	std::vector<int> z_buffer(width * height, std::numeric_limits<int>::min());

	const int count = model->faces_count();
	const Vector3f light(0,0,-1);

	for(int i = 0; i < count; ++i) {
		const auto face = model->get_face(i);
		std::vector<Vector3i> screen_coords(3);
		std::vector<Vector3f> world_coords(3);

		for(int j =0; j < 3; ++j) {
			const auto wc = model->get_vertice(face[j]);
			screen_coords[j] = Vector3i( (wc.x + 1.0) * width / 2.0, 
										 (wc.y + 1.0) * height / 2.0,
										 (wc.z + 1.0) * depth / 2.0 );
			world_coords[j] = wc;
		}

		auto normal = (world_coords[2] - world_coords[1]) ^ (world_coords[1] - world_coords[0]);
		normal.normalize();

		const float intensity = normal * light;
		if (intensity > 0) {
			triangle(	screen_coords[0], 
							screen_coords[1], 
							screen_coords[2], 
							image, 
							TGAColor(255*intensity, 255*intensity, 255*intensity, 255),
							z_buffer,
							width
			);
		}
	}

	// {
	// 	TGAImage y_buffer_image(width, 16, TGAImage::RGB);

	// 	std::vector<int> y_buffer(width, std::numeric_limits<int>::min());


	// 	rasterize(Vector2i(20, 34),   Vector2i(744, 400), y_buffer_image, red,   y_buffer);
    //     rasterize(Vector2i(120, 434), Vector2i(444, 400), y_buffer_image, green, y_buffer);
    //     rasterize(Vector2i(330, 463), Vector2i(594, 200), y_buffer_image, blue,  y_buffer);

	// 	y_buffer_image.write_tga_file("y_buffer.tga");
	// }

	image.flip_vertically();
	image.write_tga_file("output.tga");
	return 0;
}

