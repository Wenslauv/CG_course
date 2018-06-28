#include "tgaimage.h"

#include <cmath>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);


void line(int x0, int y0, int x1, int y1, TGAImage& image, const TGAColor& color) {
    
    bool transpose = false;
    if (std::abs(x0-x1) < std::abs(y0-y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        transpose = true;
    }
    
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    
    int dx = x0 - x1;
    int dy = y0 - y1;
    int delta_e = std::abs(dy) * 2;
    int error = 0;
    int y = y0;
    for (int x = x0; x <= x1; ++x) {
        image.set(transpose ? y : x,
                  transpose ? x : y,
                  color);
        
        error += delta_e;
        
        if (error > dx ){
            y += (y1 > y0 ? 1 : -1);
            error -= dx*2;
        }
    }
    
}


int main(int argc, char** argv) {
	TGAImage image(100, 100, TGAImage::RGB);
	image.set(52, 41, red);
    line(13, 20, 80, 40, image, white);
    line(20, 13, 40, 80, image, red);
    line(80, 40, 13, 20, image, red);
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}

