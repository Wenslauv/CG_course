#include "functions.h"

#include <cmath>


void line(int x0, int y0, int x1, int y1, TGAImage& image, const TGAColor& color)
{
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
    
    const int dx = x1 - x0;
    const int dy = y1 - y0;
    const int delta_e = std::abs(dy) * 2;
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

void line( const Vector2i& v0, const Vector2i& v1, TGAImage& image, const TGAColor& color ) 
{
    line(v0.x, v0.y, v1.x, v1.y, image, color);
}



void draw_triangle( const Vector2i& v0, 
                    const Vector2i& v1, 
                    const Vector2i& v2, 
                    TGAImage& image, 
                    const TGAColor& color) 
{
    line(v0, v1, image, color);
    line(v1, v2, image, color);
    line(v0, v2, image, color);
}