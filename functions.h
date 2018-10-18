#pragma once

#include "tgaimage.h"
#include "geometry.h"

#include <vector>


void line(int x0, int y0, int x1, int y1, TGAImage& image, const TGAColor& color); 


void draw_triangle( const Vector2i& v0, 
                    const Vector2i& v1, 
                    const Vector2i& v2, 
                    TGAImage& image, 
                    const TGAColor& color);


void triangle(  Vector3i p0, 
                Vector3i p1, 
                Vector3i p2, 
                TGAImage& image, 
                const TGAColor& color,
                std::vector<int>& zbuff,
                int width);


void rasterize( Vector2i v0,
                Vector2i v1, 
                TGAImage& image,
                const TGAColor& color,
                std::vector<int>& ybuffer);